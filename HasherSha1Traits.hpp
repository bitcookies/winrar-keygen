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
#endif

