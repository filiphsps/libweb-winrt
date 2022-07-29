#pragma once

#include "./AK/Array.h"
#include "./AK/Assertions.h"
#include "./AK/Iterator.h"
#include "./AK/TypedTransfer.h"
#include "./AK/Types.h"

namespace AK {

namespace Detail {

template<typename T>
class Span {
public:
    inline constexpr Span() = default;

    inline constexpr Span(T* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }

    template<size_t size>
    inline constexpr Span(T(&values)[size])
        : m_values(values)
        , m_size(size)
    {
    }

    /*template<size_t size>
    inline constexpr Span(Array<T, size>& array)
        : m_values(array.data())
        , m_size(size)
    {
    }*/

protected:
    T* m_values{ nullptr };
    size_t m_size{ 0 };
};

template<>
class Span<u8> {
public:
    inline constexpr Span() = default;

    inline constexpr Span(u8* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }
    inline Span(void* values, size_t size)
        : m_values(reinterpret_cast<u8*>(values))
        , m_size(size)
    {
    }

protected:
    u8* m_values{ nullptr };
    size_t m_size{ 0 };
};

template<>
class Span<u8 const> {
public:
    inline constexpr Span() = default;

    inline constexpr Span(u8 const* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }
    inline Span(void const* values, size_t size)
        : m_values(reinterpret_cast<u8 const*>(values))
        , m_size(size)
    {
    }
    inline Span(char const* values, size_t size)
        : m_values(reinterpret_cast<u8 const*>(values))
        , m_size(size)
    {
    }

protected:
    u8 const* m_values{ nullptr };
    size_t m_size{ 0 };
};

}

template<typename T>
class Span : public Detail::Span<T> {
public:
    using Detail::Span<T>::Span;

    constexpr Span() = default;

    inline constexpr T* data() { return this->m_values; }

    inline constexpr size_t size() const { return this->m_size; }
    inline constexpr bool is_null() const { return this->m_values == nullptr; }
    inline constexpr bool is_empty() const { return this->m_size == 0; }

    inline constexpr size_t copy_to(Span<RemoveConst<T>> other) const;

    inline constexpr T& at(size_t index);

    inline constexpr T& operator[](size_t index);

    constexpr bool operator==(Span const& other) const;

    constexpr operator Span<T const>() const;
};

using ReadonlyBytes = Span<u8 const>;
using Bytes = Span<u8>;

}

using AK::Bytes;
using AK::ReadonlyBytes;
using AK::Span;
