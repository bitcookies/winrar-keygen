#pragma once
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <type_traits>

struct GaloisFieldInitByZero {};
struct GaloisFieldInitByOne {};
struct GaloisFieldInitByElement {};
struct GaloisFieldInitByDump {};

template<typename __FieldTraits>
class GaloisField {
public:
    static constexpr size_t BitSizeValue = __FieldTraits::BitSizeValue;
    static constexpr size_t DumpSizeValue = __FieldTraits::DumpSizeValue;
private:
    static_assert(std::is_pod<typename __FieldTraits::ElementType>::value == true);

    typename __FieldTraits::ElementType _Val;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26495)  // disable uninitialized warning
#endif
    struct NoInitialization {};
    GaloisField(NoInitialization) noexcept {};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
    GaloisField() noexcept {
        __FieldTraits::SetZero(_Val);
    }

    GaloisField(GaloisFieldInitByZero) noexcept {
        __FieldTraits::SetZero(_Val);
    }

    GaloisField(GaloisFieldInitByOne) noexcept {
        __FieldTraits::SetOne(_Val);
    }

    GaloisField(GaloisFieldInitByElement, const typename __FieldTraits::ElementType& Element) {
        __FieldTraits::Verify(Element);
        _Val = Element;
    }

    GaloisField(GaloisFieldInitByDump, const void* pbBuffer, size_t cbBuffer) {
        __FieldTraits::Load(_Val, pbBuffer, cbBuffer);
    }

    template<typename __Dummy = std::enable_if<BitSizeValue <= sizeof(uintptr_t) * 8>::type>
    GaloisField(GaloisFieldInitByDump, uintptr_t SerializedValue) {
        __FieldTraits::Load(_Val, SerializedValue);
    }

    GaloisField<__FieldTraits>& operator=(const typename __FieldTraits::ElementType& Element) {
        __FieldTraits::Verify(Element);
        _Val = Element;
        return *this;
    }

    template<typename __Dummy = std::enable_if<BitSizeValue <= sizeof(uintptr_t) * 8>::type>
    GaloisField<__FieldTraits>& operator=(uintptr_t SerializedValue) {
        __FieldTraits::Load(_Val, SerializedValue);
        return *this;
    }

    bool IsZero() const noexcept {
        return __FieldTraits::IsZero(_Val);
    }

    bool IsOne() const noexcept {
        return __FieldTraits::IsOne(_Val);
    }

    bool operator==(const GaloisField<__FieldTraits>& Other) const noexcept {
        return __FieldTraits::IsEqual(_Val, Other._Val);
    }

    bool operator!=(const GaloisField<__FieldTraits>& Other) const noexcept {
        return __FieldTraits::IsEqual(_Val, Other._Val) == false;
    }

    GaloisField<__FieldTraits> operator+(const GaloisField<__FieldTraits>& Other) const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Add(Result._Val, _Val, Other._Val);
        return Result;
    }

    GaloisField<__FieldTraits>& operator+=(const GaloisField<__FieldTraits>& Other) noexcept {
        __FieldTraits::AddAssign(_Val, Other._Val);
        return *this;
    }

    GaloisField<__FieldTraits> operator-(const GaloisField<__FieldTraits>& Other) const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Substract(Result._Val, _Val, Other._Val);
        return Result;
    }

    GaloisField<__FieldTraits>& operator-=(const GaloisField<__FieldTraits>& Other) noexcept {
        __FieldTraits::SubstractAssign(_Val, Other._Val);
        return *this;
    }

    GaloisField<__FieldTraits> operator*(const GaloisField<__FieldTraits>& Other) const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Multiply(Result._Val, _Val, Other._Val);
        return Result;
    }

    GaloisField<__FieldTraits>& operator*=(const GaloisField<__FieldTraits>& Other) noexcept {
        __FieldTraits::MultiplyAssign(_Val, Other._Val);
        return *this;
    }

    GaloisField<__FieldTraits> operator/(const GaloisField<__FieldTraits>& Other) const {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Divide(Result._Val, _Val, Other._Val);
        return Result;
    }

    GaloisField<__FieldTraits>& operator/=(const GaloisField<__FieldTraits>& Other) {
        __FieldTraits::DivideAssign(_Val, Other._Val);
        return *this;
    }

    GaloisField<__FieldTraits>& operator++() noexcept {  // prefix ++
        __FieldTraits::AddOneAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> operator++(int) noexcept { // postfix ++
        GaloisField<__FieldTraits> Prev(*this);
        __FieldTraits::AddOneAssign(_Val);
        return Prev;
    }

    GaloisField<__FieldTraits>& operator--() noexcept {  // prefix --
        __FieldTraits::SubstractOneAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> operator--(int) noexcept { // postfix --
        GaloisField<__FieldTraits> Prev(*this);
        __FieldTraits::SubstractOneAssign(_Val);
        return Prev;
    }

    GaloisField<__FieldTraits>& Inverse() {
        __FieldTraits::InverseAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> InverseValue() const {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Inverse(Result, _Val);
        return Result;
    }

    GaloisField<__FieldTraits>& AddOne() noexcept {
        __FieldTraits::AddOneAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> AddOneValue() const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::AddOne(Result._Val, _Val);
        return Result;
    }

    GaloisField<__FieldTraits>& SubstractOne() noexcept {
        __FieldTraits::SubstractOneAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> SubstractOneValue() const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::SubstractOne(Result._Val, _Val);
        return Result;
    }

    GaloisField<__FieldTraits>& Square() noexcept {
        __FieldTraits::SquareAssign(_Val);
        return *this;
    }

    GaloisField<__FieldTraits> SquareValue() const noexcept {
        GaloisField<__FieldTraits> Result(NoInitialization{});
        __FieldTraits::Square(Result._Val, _Val);
        return Result;
    }

    template<typename __Dummy = std::enable_if<BitSizeValue <= sizeof(uintptr_t) * 8>::type>
    uintptr_t Dump() const noexcept {
        return __FieldTraits::Dump(_Val);
    }

    size_t Dump(void* lpBuffer, size_t cbBuffer) const {
        return __FieldTraits::Dump(_Val, lpBuffer, cbBuffer);
    }

    std::vector<uint8_t> Dump() const noexcept {
        return __FieldTraits::Dump(_Val);
    }

    template<typename __Dummy = std::enable_if<BitSizeValue <= sizeof(uintptr_t) * 8>::type>
    GaloisField<__FieldTraits>& Load(uintptr_t SerializedValue) {
        __FieldTraits::Load(_Val, SerializedValue);
        return *this;
    }

    GaloisField<__FieldTraits>& Load(const void* lpBuffer, size_t cbBuffer) {
        __FieldTraits::Load(_Val, lpBuffer, cbBuffer);
        return *this;
    }

    GaloisField<__FieldTraits>& Load(const std::vector<uint8_t>& Buffer) {
        __FieldTraits::Load(_Val, Buffer);
        return *this;
    }
};

