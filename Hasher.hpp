#pragma once
#include <utility>

template<typename __HashTraits>
class Hasher {
public:
    static constexpr size_t BlockSizeValue = __HashTraits::BlockSize;
    static constexpr size_t DigestSizeValue = __HashTraits::DigestSize;
    using DigestType = typename __HashTraits::DigestType;
private:
    using ContextType = typename __HashTraits::ContextType;
    ContextType _Ctx;
public:

    Hasher(__HashTraits) :
        _Ctx(__HashTraits::ContextCreate()) {}

    template<typename... __Ts>
    Hasher(__HashTraits, __Ts&&... Args) :
        _Ctx(__HashTraits::ContextCreate(std::forward<__Ts>(Args)...)) {}

    Hasher(const Hasher<__HashTraits>& Other) :
        _Ctx(__HashTraits::ContextCopy(Other._Ctx)) {}

    Hasher(Hasher<__HashTraits>&& Other) noexcept :
        _Ctx(std::move(Other._Ctx)) {}

    Hasher<__HashTraits>& operator=(const Hasher<__HashTraits>& Other) {
        ContextType t = __HashTraits::ContextCopy(Other._Ctx);
        __HashTraits::ContextDestroy(_Ctx);
        _Ctx = std::move(t);
        return *this;
    }

    Hasher<__HashTraits>& operator=(Hasher<__HashTraits>&& Other) noexcept {
        _Ctx = std::move(Other._Ctx);
        return *this;
    }

    constexpr size_t BlockSize() const noexcept {
        return BlockSizeValue;
    }

    constexpr size_t DigestSize() const noexcept {
        return DigestSizeValue;
    }

    void Update(const void* lpBuffer, size_t cbBuffer) noexcept {
        __HashTraits::ContextUpdate(_Ctx, lpBuffer, cbBuffer);
    }

    DigestType Evaluate() const noexcept {
        DigestType Digest;
        __HashTraits::ContextEvaluate(_Ctx, Digest);
        return Digest;
    }

    ~Hasher() {
        __HashTraits::ContextDestroy(_Ctx);
    }
};

