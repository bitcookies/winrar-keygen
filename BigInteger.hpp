#pragma once
#include <stddef.h>
#include <stdint.h>
#include <gmp.h>
#include <vector>
#include <string>
#include <type_traits>
#include <stdexcept>

class BigInteger {
private:
    mpz_t _Value;
public:

    BigInteger() noexcept {
        mpz_init(_Value);
    }

    template<typename __IntegerType>
    BigInteger(__IntegerType SmallInteger) noexcept {
        // __IntegerType must be a integer type, i.e. char, int, unsigned long...
        static_assert(std::is_integral<__IntegerType>::value);

        if constexpr (std::is_signed<__IntegerType>::value) {
            mpz_init_set_sx(_Value, SmallInteger);
        } else {
            mpz_init_set_ux(_Value, SmallInteger);
        }
    }

    BigInteger(bool IsNegative, const void* lpBuffer, size_t cbBuffer, bool UseLittleEndian) noexcept {
        mpz_init(_Value);
        mpz_import(_Value, cbBuffer, UseLittleEndian ? -1 : 1, sizeof(unsigned char), 0, 0, lpBuffer);
        if (IsNegative)
            mpz_neg(_Value, _Value);
    }

    BigInteger(bool IsNegative, const std::vector<uint8_t>& Buffer, bool UseLittleEndian) noexcept {
        mpz_init(_Value);
        mpz_import(_Value, Buffer.size(), UseLittleEndian ? -1 : 1, sizeof(unsigned char), 0, 0, Buffer.data());
        if (IsNegative)
            mpz_neg(_Value, _Value);
    }

    BigInteger(const char* lpszValue) noexcept {
        mpz_init_set_str(_Value, lpszValue, 0);
    }

    BigInteger(const std::string& szValue) noexcept {
        mpz_init_set_str(_Value, szValue.c_str(), 0);
    }

    BigInteger(const BigInteger& Other) noexcept {
        mpz_init(_Value);
        mpz_set(_Value, Other._Value);
    }

    BigInteger(BigInteger&& Other) noexcept {
        mpz_init(_Value);
        mpz_swap(_Value, Other._Value);
    }

    BigInteger& operator=(const BigInteger& Other) noexcept {
        if (this != &Other) {
            mpz_set(_Value, Other._Value);
        }
        return *this;
    }

    BigInteger& operator=(BigInteger&& Other) noexcept {
        if (this != &Other) {
            mpz_swap(_Value, Other._Value);
            mpz_clear(Other._Value);
        }
        return *this;
    }

    template<typename __IntegerType>
    BigInteger& operator=(__IntegerType SmallInteger) noexcept {
        // __IntegerType must be a integer type, i.e. char, int, unsigned long...
        static_assert(std::is_integral<__IntegerType>::value);

        if constexpr (std::is_signed<__IntegerType>::value) {
            mpz_set_sx(_Value, SmallInteger);
        } else {
            mpz_set_ux(_Value, SmallInteger);
        }

        return *this;
    }

    BigInteger& operator=(const char* lpszValue) noexcept {
        mpz_init_set_str(_Value, lpszValue, 0);
        return *this;
    }

    bool operator==(const BigInteger& Other) const noexcept {
        return mpz_cmp(_Value, Other._Value) == 0;
    }

    bool operator!=(const BigInteger& Other) const noexcept {
        return mpz_cmp(_Value, Other._Value) != 0;
    }

    bool operator<(const BigInteger& Other) const noexcept {
        return mpz_cmp(_Value, Other._Value) < 0;
    }

    bool operator<=(const BigInteger& Other) const noexcept {
        auto d = mpz_cmp(_Value, Other._Value);
        return d < 0 || d == 0;
    }

    bool operator>(const BigInteger& Other) const noexcept {
        return mpz_cmp(_Value, Other._Value) > 0;
    }

    bool operator>=(const BigInteger& Other) const noexcept {
        auto d = mpz_cmp(_Value, Other._Value);
        return d > 0 || d == 0;
    }

    BigInteger operator-() const noexcept {
        BigInteger Result;
        mpz_neg(Result._Value, _Value);
        return Result;
    }

    BigInteger operator+(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_add(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator+=(const BigInteger& Other) noexcept {
        mpz_add(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator-(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_sub(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator-=(const BigInteger& Other) noexcept {
        mpz_sub(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator*(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_mul(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator*=(const BigInteger& Other) noexcept {
        mpz_mul(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator/(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_fdiv_q(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator/=(const BigInteger& Other) noexcept {
        mpz_fdiv_q(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator%(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_fdiv_r(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator%=(const BigInteger& Other) noexcept {
        mpz_fdiv_r(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator~() const noexcept {
        BigInteger Result;
        mpz_com(Result._Value, _Value);
        return Result;
    }

    BigInteger operator&(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_and(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator&=(const BigInteger& Other) noexcept {
        mpz_and(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator|(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_ior(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator|=(const BigInteger& Other) noexcept {
        mpz_ior(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger operator^(const BigInteger& Other) const noexcept {
        BigInteger Result;
        mpz_xor(Result._Value, _Value, Other._Value);
        return Result;
    }

    BigInteger& operator^=(const BigInteger& Other) noexcept {
        mpz_xor(_Value, _Value, Other._Value);
        return *this;
    }

    BigInteger& operator++() noexcept {
        mpz_add_ui(_Value, _Value, 1);
        return *this;
    }

    BigInteger operator++(int) noexcept {
        BigInteger Result(*this);
        mpz_add_ui(_Value, _Value, 1);
        return Result;
    }

    BigInteger& operator--() noexcept {
        mpz_sub_ui(_Value, _Value, 1);
        return *this;
    }

    BigInteger operator--(int) noexcept {
        BigInteger Result(*this);
        mpz_sub_ui(_Value, _Value, 1);
        return Result;
    }

    bool IsZero() const noexcept {
        return mpz_sgn(_Value) == 0;
    }

    bool IsPositive() const noexcept {
        return mpz_sgn(_Value) > 0;
    }

    bool IsNegative() const noexcept {
        return mpz_sgn(_Value) < 0;
    }

    bool IsOne() const noexcept {
        return mpz_cmp_si(_Value, 1) == 0;
    }

    BigInteger& Load(bool IsNegative, const void* lpBuffer, size_t cbBuffer, bool UseLittleEndian) noexcept {
        mpz_import(_Value, cbBuffer, UseLittleEndian ? -1 : 1, sizeof(uint8_t), 0, 0, lpBuffer);
        if (IsNegative)
            mpz_neg(_Value, _Value);
        return *this;
    }

    BigInteger& Load(bool IsNegative, const std::vector<uint8_t> Buffer, bool UseLittleEndian) noexcept {
        mpz_import(_Value, Buffer.size(), UseLittleEndian ? -1 : 1, sizeof(uint8_t), 0, 0, Buffer.data());
        if (IsNegative)
            mpz_neg(_Value, _Value);
        return *this;
    }

    void DumpAbs(void* lpBuffer, size_t cbBuffer, bool UseLittleEndian) const {
        size_t bit_size = mpz_sizeinbase(_Value, 2);
        size_t storage_size = (bit_size + 7) / 8;
        if (cbBuffer >= storage_size) {
            size_t bytes_written;
            mpz_export(lpBuffer, &bytes_written, UseLittleEndian ? -1 : 1, sizeof(uint8_t), 0, 0, _Value);
            memset(reinterpret_cast<unsigned char*>(lpBuffer) + bytes_written, 0, cbBuffer - bytes_written);
        } else {
            throw std::length_error("Insufficient buffer.");
        }
    }

    std::vector<uint8_t> DumpAbs(bool UseLittleEndian) const noexcept {
        size_t bit_size = mpz_sizeinbase(_Value, 2);
        size_t storage_size = (bit_size + 7) / 8;
        std::vector<uint8_t> bytes(storage_size);
        mpz_export(bytes.data(), nullptr, UseLittleEndian ? -1 : 1, sizeof(uint8_t), 0, 0, _Value);
        return bytes;
    }

    size_t BitLength() const noexcept {
        return mpz_sizeinbase(_Value, 2);
    }

    bool TestBit(size_t i) const noexcept {
        return mpz_tstbit(_Value, i) != 0;
    }

    void SetBit(size_t i) noexcept {
        mpz_setbit(_Value, i);
    }

    std::string ToString(size_t Base, bool LowerCase) const {
        if (2 <= Base && Base <= 10 + 26) {
            int base = LowerCase ? static_cast<int>(Base) : -static_cast<int>(Base);
            std::string s(mpz_sizeinbase(_Value, base) + 2, '\x00');
            
            mpz_get_str(s.data(), base, _Value);

            while (s.back() == '\x00') {
                s.pop_back();
            }

            return s;
        } else {
            throw std::invalid_argument("Invalid base value.");
        }
    }
};

