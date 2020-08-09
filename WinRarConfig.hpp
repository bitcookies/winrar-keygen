#pragma once
#include "GaloisField.hpp"
#include "EllipticCurveGF2m.hpp"
#include "BigInteger.hpp"

struct WinRarConfig {
public:
    // Irreducible polynomial of ground field = x^15 + x + 1
    // Irreducible polynomial of extension field = y^17 + y^3 + 1;
    struct GF2p15p17Traits {
        struct ElementType {
            uint16_t Items[17];
        };
        
        static constexpr size_t BitSizeValue = 15 * 17;
        static constexpr size_t DumpSizeValue = (BitSizeValue + 7) / 8;

        using GF2p15LogExpTableType = uint16_t[0x8000];

        static const GF2p15LogExpTableType& InitializeGF2p15Table(bool ReturnLogTable) noexcept {
            static GF2p15LogExpTableType LogTable;
            static GF2p15LogExpTableType ExpTable;
            constexpr size_t Order = 0x7fff;

            if (ExpTable[Order] == 0) {

                ExpTable[0] = 1;
                for (size_t i = 1; i < Order; ++i) {
                    uint32_t temp = ExpTable[i - 1] * 2;
                    if (temp & 0x8000) {
                        temp ^= 0x8003;
                    }
                    ExpTable[i] = temp;
                }

                // mark as initialized
                ExpTable[Order] = ~ExpTable[Order];

                for (size_t i = 0; i < Order; ++i) {
// #if defined(_MSC_VER)
//                     __assume(ExpTable[i] <= Order);
// #endif
                    LogTable[ExpTable[i]] = static_cast<uint16_t>(i);
                }
            }

            if (ReturnLogTable) {
                return LogTable;
            } else {
                return ExpTable;
            }
        }

        static inline const GF2p15LogExpTableType& GF2p15LogTable = InitializeGF2p15Table(true);
        static inline const GF2p15LogExpTableType& GF2p15ExpTable = InitializeGF2p15Table(false);
        static inline const ElementType ZeroValue = {};
        static inline const ElementType OneValue = { 1 };

        static void Verify(const ElementType& Val) {
            for (size_t i = 0; i < 17; ++i) {
                if (Val.Items[i] >= 0x8000) {
                    throw std::invalid_argument("Val is not in GF((2 ^ 15) ^ 17).");
                }
            }
        }

        static size_t Dump(const ElementType& Val, void* lpBuffer, size_t cbBuffer) {
            if (cbBuffer < DumpSizeValue) {
                throw std::length_error("Insufficient buffer.");
            } else {
                uint8_t* pbWritePtr = reinterpret_cast<uint8_t*>(lpBuffer);
                unsigned left_bits = 8;

                for (size_t i = 0; i < 17; ++i) {
                    uint8_t low8 = static_cast<uint8_t>(Val.Items[i]);
                    uint8_t high7 = static_cast<uint8_t>(Val.Items[i] >> 8);

                    if (left_bits == 8) {
                        *pbWritePtr = low8;
                        ++pbWritePtr;
                    } else {
                        *pbWritePtr |= low8 << (8 - left_bits);
                        ++pbWritePtr;
                        *pbWritePtr = low8 >> left_bits;
                    }

                    if (left_bits == 8) {
                        *pbWritePtr = high7;
                        left_bits = 1;
                    } else if (left_bits == 7) {
                        *pbWritePtr |= high7 << 1;
                        ++pbWritePtr;
                        left_bits = 8;
                    } else {
                        *pbWritePtr |= high7 << (8 - left_bits);
                        ++pbWritePtr;
                        *pbWritePtr = high7 >> left_bits;
                        left_bits = 8 - (7 - left_bits);
                    }
                }

                return DumpSizeValue;
            }
        }

        static std::vector<uint8_t> Dump(const ElementType& Val) noexcept {
            std::vector<uint8_t> bytes(DumpSizeValue);
            Dump(Val, bytes.data(), bytes.size());
            return bytes;
        }

        static void Load(ElementType& Val, const void* lpBuffer, size_t cbBuffer) {
            if (cbBuffer != DumpSizeValue) {
                throw std::length_error("The length of buffer is not correct.");
            } else {
                const uint8_t* pbBuffer = reinterpret_cast<const uint8_t*>(lpBuffer);

                if (pbBuffer[DumpSizeValue - 1] & 0x80) {
                    throw std::invalid_argument("Not in GF((2 ^ 15) ^ 17).");
                }

                uint16_t* pbWritePtr = Val.Items;
                unsigned left_bits = 15;

                for (size_t i = 0; i < DumpSizeValue; ++i) {
                    uint16_t v;
                    if (left_bits == 15) {
                        v = pbBuffer[i];
                        left_bits = 15 - 8;
                    } else if (left_bits > 8) {
                        v |= pbBuffer[i] << (15 - left_bits);
                        left_bits -= 8;
                    } else {
                        v |= (pbBuffer[i] << (15 - left_bits)) & 0x7fff;
                        *pbWritePtr = v;
                        ++pbWritePtr;
                        v = pbBuffer[i] >> left_bits;
                        left_bits = 15 - (8 - left_bits);
                    }
                }
            }
        }

        static void Load(ElementType& Val, const std::vector<uint8_t>& Buffer) {
            Load(Val, Buffer.data(), Buffer.size());
        }

        static inline void Swap(ElementType& A, ElementType& B) noexcept {
            for (size_t i = 0; i < 17; ++i) {
                std::swap(A.Items[i], B.Items[i]);
            }
        }

        static inline void SetZero(ElementType& Val) noexcept {
            memset(Val.Items, 0, sizeof(Val.Items));
        }

        static inline void SetOne(ElementType& Val) noexcept {
            Val.Items[0] = 1;
            memset(Val.Items + 1, 0, sizeof(Val.Items) - sizeof(Val.Items[0]));
        }

        static inline bool IsEqual(const ElementType& A, const ElementType& B) noexcept {
            return memcmp(A.Items, B.Items, sizeof(ElementType::Items)) == 0;
        }

        static inline bool IsZero(const ElementType& Val) noexcept {
            return memcmp(Val.Items, ZeroValue.Items, sizeof(ElementType::Items)) == 0;
        }

        static inline bool IsOne(const ElementType& Val) noexcept {
            return memcmp(Val.Items, OneValue.Items, sizeof(ElementType::Items)) == 0;
        }

        // Result = A + B
        static inline void Add(ElementType& Result, const ElementType& A, const ElementType& B) noexcept {
            for (size_t i = 0; i < 17; ++i) {
                Result.Items[i] = A.Items[i] ^ B.Items[i];
            }
        }

        // A += B
        static inline void AddAssign(ElementType& A, const ElementType& B) noexcept {
            for (size_t i = 0; i < 17; ++i) {
                A.Items[i] ^= B.Items[i];
            }
        }

        // Result = A + 1
        static inline void AddOne(ElementType& Result, const ElementType& A) noexcept {
            Result.Items[0] = A.Items[0] ^ 0x0001;
            memcpy(Result.Items + 1, A.Items + 1, sizeof(ElementType::Items) - sizeof(uint16_t));
        }

        // A += 1
        static inline void AddOneAssign(ElementType& A) noexcept {
            A.Items[0] ^= 0x0001;
        }

        // Result = A - B
        static inline void Substract(ElementType& Result, const ElementType& A, const ElementType& B) noexcept {
            for (size_t i = 0; i < 17; ++i) {
                Result.Items[i] = A.Items[i] ^ B.Items[i];
            }
        }

        // A -= B
        static inline void SubstractAssign(ElementType& A, const ElementType& B) noexcept {
            for (size_t i = 0; i < 17; ++i) {
                A.Items[i] ^= B.Items[i];
            }
        }

        // Result = A - 1
        static inline void SubstractOne(ElementType& Result, const ElementType& A) noexcept {
            Result.Items[0] = A.Items[0] ^ 0x0001;
            memcpy(Result.Items + 1, A.Items + 1, sizeof(ElementType::Items) - sizeof(uint16_t));
        }

        // A -= 1
        static inline void SubstractOneAssign(ElementType& A) noexcept {
            A.Items[0] ^= 0x0001;
        }

        // Result = A * B
        // Require: len(Result) == M + N - 1
        static inline void FullMultiplySchoolBook(size_t M, size_t N, uint16_t Result[], const uint16_t A[], const uint16_t B[]) noexcept {
            memset(Result, 0, (M + N - 1) * sizeof(uint16_t));

            for (size_t i = 0; i < M; ++i) {
                if (A[i]) {
                    for (size_t j = 0; j < N; ++j) {
                        if (B[j]) {
                            auto g = GF2p15LogTable[A[i]] + GF2p15LogTable[B[j]];

                            if (g >= 0x7fff) {
                                g -= 0x7fff;
                            }

                            Result[i + j] ^= GF2p15ExpTable[g];
                        }
                    }
                }
            }
        }

        static inline void ModularReduction(size_t N, uint16_t A[]) noexcept {
            // Irreducible polynomial of extension field = y^17 + y^3 + 1;
            for (size_t i = N - 1; i > 16; --i) {
                if (A[i] != 0) {
                    A[i - 17 + 0] ^= A[i];
                    A[i - 17 + 3] ^= A[i];
                    A[i] = 0;
                }
            }
        }

        // Result = A * B mod (x^15 + x + 1, y^17 + y^3 + 1)
        static inline void Multiply(ElementType& Result, const ElementType& A, const ElementType& B) noexcept {
            uint16_t temp[16 + 16 + 1];
            FullMultiplySchoolBook(17, 17, temp, A.Items, B.Items);
            ModularReduction(16 + 16 + 1, temp);
            memcpy(Result.Items, temp, sizeof(ElementType::Items));
        }

        static inline void MultiplyAssign(ElementType& A, const ElementType& B) noexcept {
            Multiply(A, A, B);
        }

        static inline void Divide(ElementType& Result, const ElementType& A, const ElementType& B) {
            ElementType InverseOfB;
            Inverse(InverseOfB, B);
            Multiply(Result, A, InverseOfB);
        }

        static inline void DivideAssign(ElementType& A, const ElementType& B) {
            ElementType InverseOfB;
            Inverse(InverseOfB, B);
            MultiplyAssign(A, InverseOfB);
        }

        static inline void Inverse(ElementType& Result, const ElementType& A) {
            // lpA += (Alpha * x ^ j) * B
            auto AddScale = [](uint16_t A[], size_t& degA, uint16_t Alpha, size_t j, const uint16_t B[], size_t degB) {
                auto logAlpha = GF2p15LogTable[Alpha];
                auto Aj = A + j;

                for (size_t i = 0; i <= degB; ++i) {
                    if (B[i]) {
                        auto g = logAlpha + GF2p15LogTable[B[i]];

                        if (g >= 0x7fff) {
                            g -= 0x7fff;
                        }

                        Aj[i] ^= GF2p15ExpTable[g];
                        if (Aj[i] && i + j > degA) {
                            degA = i + j;
                        }
                    }
                }

                while (A[degA] == 0) {
                    --degA;
                }
            };

            size_t degB;
            size_t degC;
            size_t degF;
            size_t degG;
            uint16_t B[2 * 17];
            uint16_t C[2 * 17];
            uint16_t F[2 * 17];
            uint16_t G[2 * 17];

            // Initialize B
            degB = 0;
            B[0] = 1;
            memset(B + 1, 0, sizeof(B) - sizeof(uint16_t));

            // Initialize C
            degC = 0;
            memset(C, 0, sizeof(C));

            // Initialize F
            bool isZero = true;
            for (unsigned i = 0; i < 17; ++i) {
                if (A.Items[i] != 0) {
                    isZero = false;
                }

                F[i] = A.Items[i];

                if (F[i]) {
                    degF = i;
                }
            }
            memset(F + 17, 0, 17 * sizeof(uint16_t));

            if (isZero) {
                throw std::domain_error("Zero doesn't have inverse.");
            }

            // initialize G = x^17 + x^3 + 1;
            degG = 17;
            memset(G, 0, sizeof(G));
            G[0] = 1;
            G[3] = 1;
            G[17] = 1;

            for (uint16_t *lpF = F, *lpG = G, *lpB = B, *lpC = C;;) {
                if (degF == 0) {
                    for (size_t i = 0; i <= degB; ++i) {
                        if (lpB[i]) {
                            auto g = GF2p15LogTable[lpB[i]] - GF2p15LogTable[lpF[0]];

                            if (g < 0) {
                                g += 0x7fff;
                            }

                            Result.Items[i] = GF2p15ExpTable[g];
                        } else {
                            Result.Items[i] = 0;
                        }
                    }

                    for (size_t i = degB + 1; i < 17; ++i) {
                        Result.Items[i] = 0;
                    }

                    break;
                }

                if (degF < degG) {
                    std::swap(lpF, lpG);
                    std::swap(degF, degG);
                    std::swap(lpB, lpC);
                    std::swap(degB, degC);
                }

                auto j = degF - degG;

                auto g = GF2p15LogTable[lpF[degF]] - GF2p15LogTable[lpG[degG]];
                if (g < 0) {
                    g += 0x7fff;
                }
                auto Alpha = GF2p15ExpTable[g];

                AddScale(lpF, degF, Alpha, j, lpG, degG);
                AddScale(lpB, degB, Alpha, j, lpC, degC);
            }
        }

        static inline void InverseAssign(ElementType& Result) {
            Inverse(Result, Result);
        }

        static inline void Square(ElementType& Result, const ElementType& A) noexcept {
            uint16_t temp[16 + 16 + 1];

            for (size_t i = 0; i < 17; ++i) {
                if (A.Items[i]) {
                    auto g = GF2p15LogTable[A.Items[i]] * 2;

                    if (g >= 0x7fff) {
                        g -= 0x7fff;
                    }

                    temp[2 * i] = GF2p15ExpTable[g];
                } else {
                    temp[2 * i] = 0;
                }
            }

            for (size_t i = 1; i < 16 + 16 + 1; i += 2) {
                temp[i] = 0;
            }

            ModularReduction(16 + 16 + 1, temp);

            memcpy(Result.Items, temp, sizeof(ElementType::Items));
        }

        static inline void SquareAssign(ElementType& A) noexcept {
            Square(A, A);
        }
    };

    static inline const EllipticCurveGF2m<GaloisField<GF2p15p17Traits>> Curve{
        { GaloisFieldInitByZero{} },                // A
        { GaloisFieldInitByElement{}, { 161 } }     // B
    };

    static inline const EllipticCurveGF2m<GaloisField<GF2p15p17Traits>>::Point G = Curve.GetPoint(
        {
            GaloisFieldInitByElement{},
            {
                0x38CC, 0x052F, 0x2510, 0x45AA,
                0x1B89, 0x4468, 0x4882, 0x0D67,
                0x4FEB, 0x55CE, 0x0025, 0x4CB7,
                0x0CC2, 0x59DC, 0x289E, 0x65E3,
                0x56FD
            }
        },
        {
            GaloisFieldInitByElement{},
            {
                0x31A7, 0x65F2, 0x18C4, 0x3412,
                0x7388, 0x54C1, 0x539B, 0x4A02,
                0x4D07, 0x12D6, 0x7911, 0x3B5E,
                0x4F0E, 0x216F, 0x2BF2, 0x1974,
                0x20DA
            }
        }
    );

    static inline const BigInteger Order = "0x1026dd85081b82314691ced9bbec30547840e4bf72d8b5e0d258442bbcd31";

    // Generated by `WinRarKeygen<WinRarConfig>::GeneratePrivateKey(nullptr, 0);`
    static inline const BigInteger PrivateKey = "0x59fe6abcca90bdb95f0105271fa85fb9f11f467450c1ae9044b7fd61d65e";

    static inline const EllipticCurveGF2m<GaloisField<GF2p15p17Traits>>::Point PublicKey = Curve.GetPoint(
        {
            GaloisFieldInitByElement{},
            {
                0x3A1A, 0x1109, 0x268A, 0x12F7,
                0x3734, 0x75F0, 0x576C, 0x2EA4,
                0x4813, 0x3F62, 0x0567, 0x784D,
                0x753D, 0x6D92, 0x366C, 0x1107,
                0x3861
            }
        },
        {
            GaloisFieldInitByElement{},
            {
                0x6C20, 0x6027, 0x1B22, 0x7A87,
                0x43C4, 0x1908, 0x2449, 0x4675,
                0x7933, 0x2E66, 0x32F5, 0x2A58,
                0x1145, 0x74AC, 0x36D0, 0x2731,
                0x12B6
            }
        }
    );
};

