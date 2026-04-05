#pragma once

#ifdef _MSC_VER
#include <windows.h>
#include <wincrypt.h>
#include <system_error>

struct HasherSha1Traits {
public:
    static constexpr size_t BlockSize = 512 / 8;
    static constexpr size_t DigestSize = 160 / 8;

    struct DigestType {
        BYTE Bytes[DigestSize];
    };

    struct ContextType {
        HCRYPTHASH hHash;

        ContextType() noexcept : 
            hHash(NULL) {}

        ContextType(HCRYPTHASH HashHandle) noexcept :
            hHash(HashHandle) {}

        ContextType(const ContextType& Other) noexcept = default;

        ContextType(ContextType&& Other) noexcept : hHash(Other.hHash) {
            Other.hHash = NULL;
        }

        ContextType& operator=(const ContextType& Other) noexcept = default;

        ContextType& operator=(ContextType&& Other) noexcept {
            hHash = Other.hHash;
            Other.hHash = NULL;
            return *this;
        }
    };

private:

    static inline struct ContextProvider {
        HCRYPTPROV Handle;

        ~ContextProvider() {
            if (Handle) {
                CryptReleaseContext(Handle, 0);
                Handle = NULL;
            }
        }
    } CryptProvider;

public:
    static inline ContextType ContextCreate() {
        ContextType Ctx;

        if (CryptProvider.Handle == NULL) {
            if (!CryptAcquireContext(&CryptProvider.Handle, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) {
                auto err = GetLastError();
                if (err == NTE_BAD_KEYSET) {
                    if (!CryptAcquireContext(&CryptProvider.Handle, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET)) {
                        err = GetLastError();
                        throw std::system_error(err, std::system_category());
                    }
                } else {
                    throw std::system_error(err, std::system_category());
                }
            }
        }

        if (!CryptCreateHash(CryptProvider.Handle, CALG_SHA1, NULL, 0, &Ctx.hHash)) {
            auto err = GetLastError();
            throw std::system_error(err, std::system_category());
        }

        return Ctx;
    }

    static inline ContextType ContextCreate(const void* lpBuffer, size_t cbBuffer) {
        ContextType Ctx;

        if (CryptProvider.Handle == NULL) {
            if (!CryptAcquireContext(&CryptProvider.Handle, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) {
                auto err = GetLastError();
                if (err == NTE_BAD_KEYSET) {
                    if (!CryptAcquireContext(&CryptProvider.Handle, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET)) {
                        err = GetLastError();
                        throw std::system_error(err, std::system_category());
                    }
                } else {
                    throw std::system_error(err, std::system_category());
                }
            }
        }

        if (!CryptCreateHash(CryptProvider.Handle, CALG_SHA1, NULL, 0, &Ctx.hHash)) {
            auto err = GetLastError();
            throw std::system_error(err, std::system_category());
        }

        ContextUpdate(Ctx, lpBuffer, cbBuffer);

        return Ctx;
    }

    static inline ContextType ContextCopy(const ContextType& Ctx) {
        ContextType NewCtx;
        if (!CryptDuplicateHash(Ctx.hHash, NULL, 0, &NewCtx.hHash)) {
            auto err = GetLastError();
            throw std::system_error(err, std::system_category());
        }
        return NewCtx;
    }

    static inline void ContextUpdate(ContextType& Ctx, const void* lpBuffer, size_t cbBuffer) {
        if constexpr (sizeof(size_t) <= sizeof(DWORD)) {
            if (!CryptHashData(Ctx.hHash, reinterpret_cast<const BYTE*>(lpBuffer), static_cast<DWORD>(cbBuffer), 0)) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        } else {
            size_t BytesRead = 0;
            DWORD BytesToRead = cbBuffer - BytesRead > MAXDWORD ? MAXDWORD : static_cast<DWORD>(cbBuffer - BytesRead);
            
            do {
                if (!CryptHashData(Ctx.hHash, reinterpret_cast<const BYTE*>(lpBuffer) + BytesRead, BytesToRead, 0)) {
                    auto err = GetLastError();
                    throw std::system_error(err, std::system_category());
                }
                BytesRead += BytesToRead;
                BytesToRead = cbBuffer - BytesRead > MAXDWORD ? MAXDWORD : static_cast<DWORD>(cbBuffer - BytesRead);
            } while (BytesToRead);
        }
    }

    static inline void ContextEvaluate(const ContextType& Ctx, DigestType& Digest) {
        DWORD SizeOfDigest = sizeof(Digest.Bytes);
        if (!CryptGetHashParam(Ctx.hHash, HP_HASHVAL, Digest.Bytes, &SizeOfDigest, 0)) {
            auto err = GetLastError();
            throw std::system_error(err, std::system_category());
        }
    }

    static inline void ContextDestroy(ContextType& Ctx) noexcept {
        if (Ctx.hHash) {
            CryptDestroyHash(Ctx.hHash);
            Ctx.hHash = NULL;
        }
    }
};
#else

#include <cstring>
#include <stdexcept>

struct HasherSha1Traits {
public:
    static constexpr size_t BlockSize = 512 / 8;
    static constexpr size_t DigestSize = 160 / 8;

    struct DigestType {
        uint8_t Bytes[DigestSize];
    };

    struct ContextType {
        uint32_t State[5];
        uint64_t Count;
        uint8_t Buffer[64];

        ContextType() noexcept : State{}, Count(0), Buffer{} {}
        ContextType(const ContextType&) noexcept = default;
        ContextType& operator=(const ContextType&) noexcept = default;
        ContextType(ContextType&& Other) noexcept = default;
        ContextType& operator=(ContextType&& Other) noexcept = default;
    };

private:
    static inline uint32_t RotateLeft(uint32_t x, int n) noexcept {
        return (x << n) | (x >> (32 - n));
    }

    static void ProcessBlock(uint32_t state[5], const uint8_t block[64]) noexcept {
        uint32_t w[80];
        for (int i = 0; i < 16; ++i) {
            w[i] = (static_cast<uint32_t>(block[i * 4]) << 24) |
                   (static_cast<uint32_t>(block[i * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(block[i * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(block[i * 4 + 3]));
        }
        for (int i = 16; i < 80; ++i) {
            w[i] = RotateLeft(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];
        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i < 20) { f = (b & c) | (~b & d); k = 0x5A827999; }
            else if (i < 40) { f = b ^ c ^ d; k = 0x6ED9EBA1; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else { f = b ^ c ^ d; k = 0xCA62C1D6; }
            uint32_t temp = RotateLeft(a, 5) + f + e + k + w[i];
            e = d; d = c; c = RotateLeft(b, 30); b = a; a = temp;
        }
        state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
    }

public:
    static inline ContextType ContextCreate() {
        ContextType Ctx;
        Ctx.State[0] = 0x67452301;
        Ctx.State[1] = 0xEFCDAB89;
        Ctx.State[2] = 0x98BADCFE;
        Ctx.State[3] = 0x10325476;
        Ctx.State[4] = 0xC3D2E1F0;
        Ctx.Count = 0;
        return Ctx;
    }

    static inline ContextType ContextCreate(const void* lpBuffer, size_t cbBuffer) {
        ContextType Ctx = ContextCreate();
        ContextUpdate(Ctx, lpBuffer, cbBuffer);
        return Ctx;
    }

    static inline ContextType ContextCopy(const ContextType& Ctx) {
        return Ctx;
    }

    static inline void ContextUpdate(ContextType& Ctx, const void* lpBuffer, size_t cbBuffer) {
        auto data = reinterpret_cast<const uint8_t*>(lpBuffer);
        size_t bufferOffset = static_cast<size_t>(Ctx.Count % 64);
        Ctx.Count += cbBuffer;

        if (bufferOffset > 0) {
            size_t toCopy = 64 - bufferOffset;
            if (toCopy > cbBuffer) toCopy = cbBuffer;
            std::memcpy(Ctx.Buffer + bufferOffset, data, toCopy);
            data += toCopy;
            cbBuffer -= toCopy;
            bufferOffset += toCopy;
            if (bufferOffset == 64) {
                ProcessBlock(Ctx.State, Ctx.Buffer);
                bufferOffset = 0;
            }
        }

        while (cbBuffer >= 64) {
            ProcessBlock(Ctx.State, data);
            data += 64;
            cbBuffer -= 64;
        }

        if (cbBuffer > 0) {
            std::memcpy(Ctx.Buffer, data, cbBuffer);
        }
    }

    static inline void ContextEvaluate(const ContextType& Ctx, DigestType& Digest) {
        ContextType tmp = Ctx;
        uint64_t totalBits = tmp.Count * 8;
        uint8_t pad = 0x80;
        ContextUpdate(tmp, &pad, 1);
        uint8_t zero = 0;
        while (tmp.Count % 64 != 56) {
            ContextUpdate(tmp, &zero, 1);
        }
        uint8_t lenBytes[8];
        for (int i = 7; i >= 0; --i) {
            lenBytes[i] = static_cast<uint8_t>(totalBits);
            totalBits >>= 8;
        }
        ContextUpdate(tmp, lenBytes, 8);
        for (int i = 0; i < 5; ++i) {
            Digest.Bytes[i * 4] = static_cast<uint8_t>(tmp.State[i] >> 24);
            Digest.Bytes[i * 4 + 1] = static_cast<uint8_t>(tmp.State[i] >> 16);
            Digest.Bytes[i * 4 + 2] = static_cast<uint8_t>(tmp.State[i] >> 8);
            Digest.Bytes[i * 4 + 3] = static_cast<uint8_t>(tmp.State[i]);
        }
    }

    static inline void ContextDestroy(ContextType& Ctx) noexcept {
        std::memset(&Ctx, 0, sizeof(Ctx));
    }
};

#endif
