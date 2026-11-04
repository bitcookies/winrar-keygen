#pragma once
#include "BigInteger.hpp"
#include "Hasher.hpp"
#include "HasherSha1Traits.hpp"
#include "HasherCrc32Traits.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

#if defined(_WIN32)
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#elif defined(__linux__)
#include <sys/random.h>
#include <errno.h>
#endif

#ifdef _MSC_VER
#define BSWAP32(x) _byteswap_ulong(x)
#else
#define BSWAP32(x) __builtin_bswap32(x)
#endif

template<typename __ConfigType>
class WinRarKeygen {
public:

    struct RegisterInfo {
        std::string UserName;
        std::string LicenseType;
        std::string UID;
        std::string Items[4];
        uint32_t Checksum;
        std::string HexData;
    };

private:

    struct ECCSignature {
        BigInteger r;
        BigInteger s;
    };

    // Read four big-endian bytes as a uint32_t without violating strict aliasing
    // or alignment requirements (the digest buffer is not guaranteed aligned).
    static uint32_t LoadBigEndianU32(const void* lpBytes) noexcept {
        uint32_t Raw;
        std::memcpy(&Raw, lpBytes, sizeof(Raw));
        return BSWAP32(Raw);
    }

    static BigInteger GeneratePrivateKey(const void* lpSeed, size_t cbSeed) {
        uint32_t Generator[6];
        uint16_t RawPrivateKey[15] = {};

        if (cbSeed) {
            Hasher Sha1(HasherSha1Traits{}, lpSeed, cbSeed);
            HasherSha1Traits::DigestType Sha1Digest;

            Sha1Digest = Sha1.Evaluate();

            for (unsigned i = 0; i < 5; ++i) {
                Generator[i + 1] = LoadBigEndianU32(Sha1Digest.Bytes + i * 4);
            }
        } else {
            Generator[1] = 0xeb3eb781;
            Generator[2] = 0x50265329;
            Generator[3] = 0xdc5ef4a3;
            Generator[4] = 0x6847b9d5;
            Generator[5] = 0xcde43b4c;
        }
        
        for (uint32_t i = 0; i < 15; ++i) {
            Hasher Sha1(HasherSha1Traits{});
            HasherSha1Traits::DigestType Sha1Digest;

            Generator[0] = i + 1;
            Sha1.Update(Generator, sizeof(Generator));
            Sha1Digest = Sha1.Evaluate();

            RawPrivateKey[i] = static_cast<uint16_t>(
                LoadBigEndianU32(Sha1Digest.Bytes)
            );
        }

        // `Order` has 241 bits, while `RawPrivateKey` has (15 * 16 = 240) bits at most
        // So `RawPrivateKey` must be less than `Order` which means `RawPrivateKey` must be valid private key.
        return BigInteger(false, RawPrivateKey, sizeof(RawPrivateKey), true);
    }

    static auto GeneratePublicKey(const BigInteger& PrivateKey) {
        return __ConfigType::G * PrivateKey;
    }

    static std::string GeneratePublicKeySM2CompressedFormat(const char* lpszMessage) {
        auto PrivateKey = GeneratePrivateKey(lpszMessage, strlen(lpszMessage));
        auto PublicKey = GeneratePublicKey(PrivateKey);
        auto PublicKeyCompressed = PublicKey.DumpCompressed();
        auto PublicKeyXInteger = BigInteger(false, PublicKeyCompressed.data() + 1, PublicKeyCompressed.size() - 1, false);  // 255 bits at most
        
        PublicKeyXInteger *= 2;     // 256 bits at most
        if (PublicKeyCompressed[0] == 0x03) {   // when LSB(PublicKeyY / PublicKeyX) == 1
            PublicKeyXInteger.SetBit(0);
        }

        auto PublicKeyCompressedSM2Format = PublicKeyXInteger.ToString(16, true);
        if (PublicKeyCompressedSM2Format.length() < 32 * 2) {
            PublicKeyCompressedSM2Format.insert(PublicKeyCompressedSM2Format.begin(), 32 * 2 - PublicKeyCompressedSM2Format.size(), '0');
        }

        return PublicKeyCompressedSM2Format;
    }

    // Fill the buffer with cryptographically secure random bytes from the
    // operating system CSPRNG. The per-signature nonce `k` MUST be unpredictable,
    // otherwise the private key can be recovered from the signatures.
    static void FillSecureRandom(void* lpBuffer, size_t cbBuffer) {
        if (cbBuffer == 0) {
            return;
        }
#if defined(_WIN32)
        if (BCryptGenRandom(nullptr, static_cast<PUCHAR>(lpBuffer),
                            static_cast<ULONG>(cbBuffer),
                            BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
            throw std::runtime_error("Failed to acquire cryptographically secure random bytes.");
        }
#elif defined(__APPLE__)
        arc4random_buf(lpBuffer, cbBuffer);
#else
        uint8_t* p = static_cast<uint8_t*>(lpBuffer);
        size_t remaining = cbBuffer;
#if defined(__linux__)
        while (remaining > 0) {
            ssize_t n = getrandom(p, remaining, 0);
            if (n < 0) {
                if (errno == EINTR) {
                    continue;
                }
                if (errno == ENOSYS) {
                    break;      // getrandom() unavailable, fall back to /dev/urandom
                }
                throw std::runtime_error("Failed to acquire cryptographically secure random bytes.");
            }
            p += n;
            remaining -= static_cast<size_t>(n);
        }
        if (remaining == 0) {
            return;
        }
#endif
        FILE* fp = fopen("/dev/urandom", "rb");
        if (!fp) {
            throw std::runtime_error("Failed to open /dev/urandom.");
        }
        size_t got = fread(p, 1, remaining, fp);
        fclose(fp);
        if (got != remaining) {
            throw std::runtime_error("Failed to read cryptographically secure random bytes.");
        }
#endif
    }

    static BigInteger GenerateRandomInteger() {
        // A 256-bit candidate reduced modulo `Order` yields a nonce that is
        // uniformly distributed in [1, Order - 1], matching the SM2 requirement.
        uint8_t RawRandomInteger[32] = {};
        BigInteger Random;

        do {
            FillSecureRandom(RawRandomInteger, sizeof(RawRandomInteger));
            Random.Load(false, RawRandomInteger, sizeof(RawRandomInteger), true);
            Random %= __ConfigType::Order;
        } while (Random.IsZero());

        return Random;
    }

    static BigInteger GenerateHashInteger(const void* lpMessage, size_t cbMessage) {
        uint32_t RawHash[10];
        Hasher Sha1(HasherSha1Traits{}, lpMessage, cbMessage);
        HasherSha1Traits::DigestType Sha1Digest = Sha1.Evaluate();

        for (size_t i = 0; i < 5; ++i) {
            RawHash[i] = LoadBigEndianU32(Sha1Digest.Bytes + i * 4);
        }

        // SHA1("") with all-zeroed initial value
        RawHash[5] = 0x0ffd8d43;
        RawHash[6] = 0xb4e33c7c;
        RawHash[7] = 0x53461bd1;
        RawHash[8] = 0x0f27a546;
        RawHash[9] = 0x1050d90d;

        return BigInteger(false, RawHash, 15 * sizeof(uint16_t), true);     // take first 240 bits
    }

    static ECCSignature Sign(const void* lpData, size_t cbData) {
        ECCSignature Signature;
        BigInteger Hash = GenerateHashInteger(lpData, cbData);

        while (true) {
            BigInteger Random = GenerateRandomInteger();

            //
            // Calculate Signature.r
            //
            Signature.r.Load(false, (__ConfigType::G * Random).GetX().Dump(), true);
            Signature.r += Hash;
            Signature.r %= __ConfigType::Order;
            if (Signature.r.IsZero() || Signature.r + Random == __ConfigType::Order) {
                continue;
            }

            //
            // Calculate Signature.s
            //
            Signature.s = Random - __ConfigType::PrivateKey * Signature.r;
            Signature.s %= __ConfigType::Order;
            if (Signature.s.IsZero()) {
                continue;
            }

            break;
        }

        return Signature;
    }

    static void CalculateChecksum(RegisterInfo& Info) {
        Hasher Crc32(HasherCrc32Traits<0xEDB88320>{});
        Crc32.Update(Info.LicenseType.c_str(), Info.LicenseType.length());
        Crc32.Update(Info.UserName.c_str(), Info.UserName.length());
        Crc32.Update(Info.Items[0].c_str(), Info.Items[0].length());
        Crc32.Update(Info.Items[1].c_str(), Info.Items[1].length());
        Crc32.Update(Info.Items[2].c_str(), Info.Items[2].length());
        Crc32.Update(Info.Items[3].c_str(), Info.Items[3].length());
        Info.Checksum = ~Crc32.Evaluate();
    }
public:

    template<typename... ArgTypes>
    static inline std::string HelperStringFormat(const char* lpszFormat, ArgTypes&& ... Args) {
        std::string s(snprintf(nullptr, 0, lpszFormat, std::forward<ArgTypes>(Args)...) + 1, '\x00');

        snprintf(s.data(), s.size(), lpszFormat, std::forward<ArgTypes>(Args)...);
        while (s.back() == '\x00') {
            s.pop_back();
        }

        return s;
    }

    static RegisterInfo GenerateRegisterInfo(const char* lpszUserName, const char* lpszLicenseType) {
        RegisterInfo RegInfo;
        std::string temp;

        RegInfo.UserName = lpszUserName;
        RegInfo.LicenseType = lpszLicenseType;

        temp = GeneratePublicKeySM2CompressedFormat(lpszUserName);
        RegInfo.Items[3] = HelperStringFormat("60%.48s", temp.c_str());
        RegInfo.Items[0] = GeneratePublicKeySM2CompressedFormat(RegInfo.Items[3].c_str());
        RegInfo.UID = HelperStringFormat("%.16s%.4s", temp.c_str() + 48, RegInfo.Items[0].c_str());

        while (true) {
            auto LicenseTypeSignature = Sign(RegInfo.LicenseType.c_str(), RegInfo.LicenseType.length());
            auto LicenseTypeSignatureR = LicenseTypeSignature.r.ToString(16, true);
            auto LicenseTypeSignatureS = LicenseTypeSignature.s.ToString(16, true);
            if (LicenseTypeSignatureR.length() < 60) {
                LicenseTypeSignatureR.insert(LicenseTypeSignatureR.begin(), 60 - LicenseTypeSignatureR.size(), '0');
            }
            if (LicenseTypeSignatureS.length() < 60) {
                LicenseTypeSignatureS.insert(LicenseTypeSignatureS.begin(), 60 - LicenseTypeSignatureS.size(), '0');
            }
            if (LicenseTypeSignatureR.length() == 60 && LicenseTypeSignatureS.length() == 60) {
                RegInfo.Items[1] = HelperStringFormat("60%s%s", LicenseTypeSignatureS.c_str(), LicenseTypeSignatureR.c_str());
                break;
            }
        }

        temp = RegInfo.UserName + RegInfo.Items[0];

        while (true) {
            auto UserNameSignature = Sign(temp.c_str(), temp.length());
            auto UserNameSignatureR = UserNameSignature.r.ToString(16, true);
            auto UserNameSignatureS = UserNameSignature.s.ToString(16, true);
            if (UserNameSignatureR.length() < 60) {
                UserNameSignatureR.insert(UserNameSignatureR.begin(), 60 - UserNameSignatureR.size(), '0');
            }
            if (UserNameSignatureS.length() < 60) {
                UserNameSignatureS.insert(UserNameSignatureS.begin(), 60 - UserNameSignatureS.size(), '0');
            }
            if (UserNameSignatureR.length() == 60 && UserNameSignatureS.length() == 60) {
                RegInfo.Items[2] = HelperStringFormat("60%s%s", UserNameSignatureS.c_str(), UserNameSignatureR.c_str());
                break;
            }
        }

        CalculateChecksum(RegInfo);

        RegInfo.HexData = HelperStringFormat(
            "%zu%zu%zu%zu%s%s%s%s%010u",
            RegInfo.Items[0].length(),
            RegInfo.Items[1].length(),
            RegInfo.Items[2].length(),
            RegInfo.Items[3].length(),
            RegInfo.Items[0].c_str(),
            RegInfo.Items[1].c_str(),
            RegInfo.Items[2].c_str(),
            RegInfo.Items[3].c_str(),
            static_cast<unsigned>(RegInfo.Checksum)
        );

        // The length has been limited to 60 (issues #6)
        // This problem has been fixed, this prompt should no longer appear
        if (RegInfo.HexData.length() % 54 != 0) {
            throw std::runtime_error("InternalError: The length of register data is not correct.");
        }

        return RegInfo;
    }
};
