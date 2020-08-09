#pragma once
#include <stddef.h>
#include <stdint.h>

template<uint32_t __Polynomial>
struct HasherCrc32Traits {
    static constexpr size_t BlockSize = 0;
    static constexpr size_t DigestSize = 32 / 8;

    using DigestType = uint32_t;
    using LookupTableType = uint32_t[256];

    struct ContextType {
        uint32_t Value;

        ContextType() noexcept :
            Value(0) {}

        ContextType(uint32_t InitialValue) noexcept :
            Value(InitialValue) {}

        ContextType(const ContextType& Other) noexcept = default;

        ContextType(ContextType&& Other) noexcept : Value(Other.Value) {
            Other.Value = 0;
        }

        ContextType& operator=(const ContextType& Other) noexcept = default;

        ContextType& operator=(ContextType&& Other) noexcept {
            Value = Other.Value;
            Other.Value = 0;
            return *this;
        }
    };

    static const LookupTableType& InitializeLookupTable() noexcept {
        static LookupTableType LookupTable = {};

        if (LookupTable[1] == 0) {
            for (unsigned i = 0; i < 256; ++i) {
                uint32_t result = i;
                for (unsigned j = 0; j < 8; ++j) {
                    if (result % 2) {
                        result /= 2;
                        result ^= __Polynomial;
                    } else {
                        result /= 2;
                    }
                }
                LookupTable[i] = result;
            }
        }

        return LookupTable;
    }

    static inline const LookupTableType& LookupTable = InitializeLookupTable();

    static inline ContextType ContextCreate() noexcept {
        ContextType Ctx;
        return Ctx;
    }

    static inline ContextType ContextCreate(const void* lpBuffer, size_t cbBuffer) noexcept {
        ContextType Ctx;
        ContextUpdate(Ctx, lpBuffer, cbBuffer);
        return Ctx;
    }

    static inline ContextType ContextCreate(uint32_t InitialValue) noexcept {
        ContextType Ctx(InitialValue);
        return Ctx;
    }

    static inline ContextType ContextCreate(uint32_t InitialValue, const void* lpBuffer, size_t cbBuffer) noexcept {
        ContextType Ctx;
        ContextUpdate(Ctx, lpBuffer, cbBuffer);
        return Ctx;
    }

    static inline ContextType ContextCopy(const ContextType& Ctx) noexcept {
        return Ctx;
    }

    static inline void ContextUpdate(ContextType& Ctx, const void* lpBuffer, size_t cbBuffer) noexcept {
        auto pbBuffer = reinterpret_cast<const uint8_t*>(lpBuffer);
        Ctx.Value = ~Ctx.Value;
        for (size_t i = 0; i < cbBuffer; ++i) {
            Ctx.Value = (Ctx.Value >> 8) ^ LookupTable[static_cast<uint8_t>(Ctx.Value) ^ pbBuffer[i]];
        }
        Ctx.Value = ~Ctx.Value;
    }

    static inline void ContextEvaluate(const ContextType& Ctx, DigestType& Digest) noexcept {
        Digest = Ctx.Value;
    }

    static inline void ContextDestroy(ContextType& Ctx) noexcept {
        Ctx.Value = 0;
    }
};

#ifdef _MSC_VER
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma comment(lib, "ntdll")

    // available on WindowsXP and above
    NTSYSAPI
    DWORD
    NTAPI
    RtlComputeCrc32(
        _In_ DWORD InitialCrc,
        _In_reads_bytes_(Size) const void* Buffer,
        _In_ size_t Size
    );

#ifdef __cplusplus
}
#endif

template<>
struct HasherCrc32Traits<0xEDB88320> {
    static constexpr size_t BlockSize = 0;
    static constexpr size_t DigestSize = 32 / 8;

    using DigestType = uint32_t;

    struct ContextType {
        uint32_t Value;

        ContextType() noexcept :
            Value(0) {}

        ContextType(uint32_t InitialValue) noexcept :
            Value(InitialValue) {}

        ContextType(const ContextType& Other) noexcept = default;

        ContextType(ContextType&& Other) noexcept : Value(Other.Value) {
            Other.Value = 0;
        }

        ContextType& operator=(const ContextType& Other) noexcept = default;

        ContextType& operator=(ContextType&& Other) noexcept {
            Value = Other.Value;
            Other.Value = 0;
            return *this;
        }
    };

    static inline ContextType ContextCreate() noexcept {
        ContextType Ctx;
        return Ctx;
    }

    static inline ContextType ContextCreate(const void* lpBuffer, size_t cbBuffer) noexcept {
        ContextType Ctx;
        ContextUpdate(Ctx, lpBuffer, cbBuffer);
        return Ctx;
    }

    static inline ContextType ContextCreate(uint32_t InitialValue) noexcept {
        ContextType Ctx(InitialValue);
        return Ctx;
    }

    static inline ContextType ContextCreate(uint32_t InitialValue, const void* lpBuffer, size_t cbBuffer) noexcept {
        ContextType Ctx;
        ContextUpdate(Ctx, lpBuffer, cbBuffer);
        return Ctx;
    }

    static inline ContextType ContextCopy(const ContextType& Ctx) noexcept {
        return Ctx;
    }

    static inline void ContextUpdate(ContextType& Ctx, const void* lpBuffer, size_t cbBuffer) noexcept {
        Ctx.Value = RtlComputeCrc32(Ctx.Value, lpBuffer, cbBuffer);
    }

    static inline void ContextEvaluate(const ContextType& Ctx, DigestType& Digest) noexcept {
        Digest = Ctx.Value;
    }

    static inline void ContextDestroy(ContextType& Ctx) noexcept {
        Ctx.Value = 0;
    }
};

#endif  // #ifdef _MSC_VER

