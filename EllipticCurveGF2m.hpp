#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdexcept>
#include <algorithm>
#include "BigInteger.hpp"

template<typename __FieldType>
class EllipticCurveGF2m {
private:
    // y^2 + xy = x^3 + Ax^2 + B

    __FieldType _A;
    __FieldType _B;

    void _VerifyParameters() const {
        if (_B.IsZero()) {
            throw std::invalid_argument("B cannot be zero.");
        }
    }
public:

    class Point {
        friend EllipticCurveGF2m<__FieldType>;
    private:
        const EllipticCurveGF2m<__FieldType>& _Curve;
        __FieldType _X;
        __FieldType _Y;

        void _VerifyParameters() const {
            auto Left = _Y.SquareValue() + _X * _Y;
            auto Right = (_X + _Curve._A) * _X.SquareValue() + _Curve._B;
            if (Left != Right) {
                throw std::invalid_argument("New point is not on the curve specified.");
            }
        }
    public:

        Point(const EllipticCurveGF2m<__FieldType>& Curve) noexcept : 
            _Curve(Curve) {}

        Point(const EllipticCurveGF2m<__FieldType>& Curve, const void* pbX, size_t cbX, const void* pbY, size_t cbY) : 
            _Curve(Curve), 
            _X(pbX, cbX), 
            _Y(pbY, cbY) 
        {
            _VerifyParameters();
        }

        Point(const EllipticCurveGF2m<__FieldType>& Curve, const __FieldType& X, const __FieldType& Y) : 
            _Curve(Curve), _X(X), _Y(Y) 
        {
            _VerifyParameters();
        }

        Point operator-() const noexcept {
            return Point(_X, _X + _Y);
        }

        Point& operator=(const Point& Other) {
            if (&_Curve == &Other._Curve || _Curve == Other._Curve) {
                _X = Other._X;
                _Y = Other._Y;
                return *this;
            } else {
                throw std::invalid_argument("Not on the same curve.");
            }
        }

        bool operator==(const Point& Other) const noexcept {
            if (&_Curve == &Other._Curve || _Curve == Other._Curve) {
                return _X == Other._X && _Y == Other._Y;
            } else {
                return false;
            }
        }

        bool operator!=(const Point& Other) const noexcept {
            if (&_Curve == &Other._Curve || _Curve == Other._Curve) {
                return _X != Other._X || _Y != Other._Y;
            } else {
                return true;
            }
        }

        const __FieldType& GetX() const noexcept {
            return _X;
        }

        const __FieldType& GetY() const noexcept {
            return _Y;
        }

        bool IsAtInfinity() const noexcept {
            return _X.IsZero() && _Y.IsZero();
        }

        Point& Double() noexcept {
            if (IsAtInfinity() == false) {
                auto m = _Y / _X + _X;
                
                // NewX = m ^ 2 + m + a
                __FieldType NewX = m.SquareValue();
                NewX += m;
                NewX += _Curve._A;

                // NewY = X ^ 2 + (m + 1) * NewX
                _Y = m.AddOne();
                _Y *= NewX;
                _Y += _X.Square();
                
                _X = NewX;
            }
            return *this;
        }

        Point ValueOfDouble() const noexcept {
            Point Result(_Curve);

            if (IsAtInfinity() == false) {
                // m = X + Y / X
                auto m = _Y / _X + _X;

                // NewX = m ^ 2 + m + a
                Result._X = m.SquareValue();
                Result._X += m;
                Result._X += _Curve._A;

                // NewY = X ^ 2 + (m + 1) * NewX
                Result._Y = m.AddOne();
                Result._Y *= Result._X;
                Result._Y += _X.SquareValue();
            }

            return Result;
        }

        Point operator+(const Point& Other) const {
            if (&_Curve == &Other._Curve || _Curve == Other._Curve) {
                if (IsAtInfinity()) {
                    return Other;
                } else {
                    if (this == &Other || _X == Other._X) {
                        return ValueOfDouble();
                    } else {
                        Point Result(_Curve);

                        // m = (Y0 + Y1) / (X0 + X1)
                        auto m = (_Y + Other._Y) / (_X + Other._X);

                        // NewX = m ^ 2 + m + X0 + X1 + a
                        Result._X = m.SquareValue();
                        Result._X += m;
                        Result._X += _X;
                        Result._X += Other._X;
                        Result._X += _Curve._A;

                        // NewY = m * (X0 + NewX) + NewX + Y0
                        Result._Y = _X + Result._X;
                        Result._Y *= m;
                        Result._Y += Result._X;
                        Result._Y += _Y;

                        return Result;
                    }
                }
            } else {
                throw std::invalid_argument("Not on the same curve.");
            }
        }

        Point& operator+=(const Point& Other) {
            if (&_Curve == &Other._Curve || _Curve == Other._Curve) {
                if (IsAtInfinity()) {
                    _X = Other._X;
                    _Y = Other._Y;
                } else {
                    if (this == &Other || _X == Other._X) {
                        Double();
                    } else {
                        Point Result(_Curve);

                        // m = (Y0 + Y1) / (X0 + X1)
                        auto m = (_Y + Other._Y) / (_X + Other._X);

                        // NewX = m ^ 2 + m + X0 + X1 + a
                        __FieldType NewX = m.SquareValue();
                        NewX += m;
                        NewX += _X;
                        NewX += Other._X;
                        NewX += _Curve._A;

                        // NewY = m * (X0 + NewX) + NewX + Y0
                        _X += NewX;
                        _X *= m;
                        _X += NewX;
                        _Y += _X;

                        _X = NewX;
                    }
                }
                return *this;
            } else {
                throw std::invalid_argument("Not on the same curve.");
            }
        }

        Point operator-(const Point& Other) const {
            Point Result = -Other;
            Result += *this;
            return Result;
        }

        Point& operator-=(const Point& Other) {
            return *this += -Other;
        }

        Point operator*(const BigInteger N) const noexcept {
            Point Result(_Curve);
            Point temp(*this);
            size_t bit_length = N.BitLength();

            for (size_t i = 0; i < bit_length; ++i) {
                if (N.TestBit(i) == true)
                    Result += temp;
                temp.Double();
            }

            return Result;
        }

        Point operator*=(const BigInteger N) noexcept {
            Point Result(_Curve);
            size_t bit_length = N.BitLength();

            for (size_t i = 0; i < bit_length; ++i) {
                if (N.TestBit(i) == true)
                    Result += *this;
                Double();
            }

            *this = Result;
        }

        // SEC 1: Elliptic Curve Cryptography
        //     2.3.3 Elliptic-Curve-Point-to-Octet-String Conversion
        std::vector<uint8_t> Dump() const noexcept {
            if (IsAtInfinity()) {
                std::vector<uint8_t> bytes = { 0x00 };
                return bytes;
            } else {
                std::vector<uint8_t> bytes = { 0x04 };
                std::vector<uint8_t> xbytes = _X.Dump();
                std::vector<uint8_t> ybytes = _Y.Dump();
                std::reverse(xbytes.begin(), xbytes.end());     // to big endian
                std::reverse(ybytes.begin(), ybytes.end());     // to big endian
                bytes.insert(bytes.end(), xbytes.begin(), xbytes.end());
                bytes.insert(bytes.end(), ybytes.begin(), ybytes.end());
                return bytes;
            }
        }

        // SEC 1: Elliptic Curve Cryptography
        //     2.3.3 Elliptic-Curve-Point-to-Octet-String Conversion
        std::vector<uint8_t> DumpCompressed() const noexcept {
            if (IsAtInfinity()) {
                std::vector<uint8_t> bytes = { 0x00 };
                return bytes;
            } else {
                std::vector<uint8_t> bytes(1);
                std::vector<uint8_t> xbytes = _X.Dump();
                std::vector<uint8_t> zbytes = (_Y / _X).Dump();

                if (zbytes[0] & 1) {
                    bytes[0] = 0x03;
                } else {
                    bytes[0] = 0x02;
                }

                std::reverse(xbytes.begin(), xbytes.end());     // to big endian
                bytes.insert(bytes.end(), xbytes.begin(), xbytes.end());
                return bytes;
            }
        }
    };

    EllipticCurveGF2m(const __FieldType& A, const __FieldType& B) : _A(A), _B(B) {
        _VerifyParameters();
    }

    EllipticCurveGF2m(const void* pbA, size_t cbA, const void* pbB, size_t cbB) : _A(pbA, cbA), _B(pbB, cbB) {
        _VerifyParameters();
    }

    bool operator==(const EllipticCurveGF2m<__FieldType>& Other) const noexcept {
        return _A == Other._A && _B == Other._B;
    }

    bool operator!=(const EllipticCurveGF2m<__FieldType>& Other) const noexcept {
        return _A != Other._A || _B != Other._B;
    }

    Point GetInfinityPoint() const noexcept {
        return Point(*this);
    }

    Point GetPoint(const __FieldType& X, const __FieldType& Y) const {
        return Point(*this, X, Y);
    }

    Point GetPoint(const void* pbX, size_t cbX, const void* pbY, size_t cbY) const {
        return Point(*this, pbX, cbX, pbY, cbY);
    }
};
