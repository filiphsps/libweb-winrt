#pragma once

#include "Array.h"
#include "Assertions.h"
#include "Iterator.h"
#include "TypedTransfer.h"
#include "Types.h"

namespace AK {

namespace Detail {

template<typename T>
class Span {
public:
    ALWAYS_INLINE constexpr Span() = default;

    ALWAYS_INLINE constexpr Span(T* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }

    template<size_t size>
    ALWAYS_INLINE constexpr Span(T(&values)[size])
        : m_values(values)
        , m_size(size)
    {
    }

    template<size_t size>
    ALWAYS_INLINE constexpr Span(Array<T, size>& array)
        : m_values(array.data())
        , m_size(size)
    {
    }

    template<size_t size>
    requires(IsConst<T>)
    ALWAYS_INLINE constexpr Span(Array<T, size> const& array)
        : m_values(array.data())
        , m_size(size)
    {
    }

protected:
    T* m_values{ nullptr };
    size_t m_size{ 0 };
};

template<>
class Span<u8> {
public:
    ALWAYS_INLINE constexpr Span() = default;

    ALWAYS_INLINE constexpr Span(u8* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }
    ALWAYS_INLINE Span(void* values, size_t size)
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
    ALWAYS_INLINE constexpr Span() = default;

    ALWAYS_INLINE constexpr Span(u8 const* values, size_t size)
        : m_values(values)
        , m_size(size)
    {
    }
    ALWAYS_INLINE Span(void const* values, size_t size)
        : m_values(reinterpret_cast<u8 const*>(values))
        , m_size(size)
    {
    }
    ALWAYS_INLINE Span(char const* values, size_t size)
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

    ALWAYS_INLINE constexpr T const* data() const { return this->m_values; }
    ALWAYS_INLINE constexpr T* data() { return this->m_values; }

    ALWAYS_INLINE constexpr T* offset_pointer(size_t offset);

    using ConstIterator = SimpleIterator<Span const, T const>;
    using Iterator = SimpleIterator<Span, T>;

    constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    constexpr Iterator begin() { return Iterator::begin(*this); }

    constexpr ConstIterator end() const { return ConstIterator::end(*this); }
    constexpr Iterator end() { return Iterator::end(*this); }

    ALWAYS_INLINE constexpr size_t size() const { return this->m_size; }
    ALWAYS_INLINE constexpr bool is_null() const { return this->m_values == nullptr; }
    ALWAYS_INLINE constexpr bool is_empty() const { return this->m_size == 0; }

    ALWAYS_INLINE constexpr Span slice(size_t start, size_t length) const;
    ALWAYS_INLINE constexpr Span slice(size_t start) const;
    ALWAYS_INLINE constexpr Span slice_from_end(size_t count) const;

    ALWAYS_INLINE constexpr Span trim(size_t length) const;

    ALWAYS_INLINE constexpr T* offset(size_t start) const;

    ALWAYS_INLINE constexpr void overwrite(size_t offset, void const* data, size_t data_size);

    ALWAYS_INLINE constexpr size_t copy_to(Span<RemoveConst<T>> other) const;

    ALWAYS_INLINE constexpr size_t copy_trimmed_to(Span<RemoveConst<T>> other) const;

    ALWAYS_INLINE constexpr size_t fill(T const& value);

    bool constexpr contains_slow(T const& value) const;

    bool constexpr starts_with(Span<T const> other) const;

    ALWAYS_INLINE constexpr T& at(size_t index);

    ALWAYS_INLINE constexpr T& last();

    ALWAYS_INLINE constexpr T& operator[](size_t index);

    constexpr bool operator==(Span const& other) const;

    constexpr operator Span<T const>() const;
};

/*template<typename T>
struct Traits<Span<T>> : public GenericTraits<Span<T>> {
    static unsigned hash(Span<T> const& span);
};*/

using ReadonlyBytes = Span<u8 const>;
using Bytes = Span<u8>;

}

using AK::Bytes;
using AK::ReadonlyBytes;
using AK::Span;
