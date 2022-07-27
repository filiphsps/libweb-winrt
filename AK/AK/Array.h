#pragma once

#include <array>
#include "./AK/Span.h"

namespace AK {

template<typename T, size_t Size>
struct Array {
    using ValueType = T;

    constexpr T const* data() const { return __data; }
    constexpr T* data() { return __data; }

    constexpr size_t size() const { return Size; }

    constexpr Span<T> span() { return { __data, Size }; }

    constexpr T const& at(size_t index) const
    {
        //VERIFY(index < size());
        return __data[index];
    }

    constexpr T const& first() const { return at(0); }
    constexpr T const& last() const requires(Size > 0) { return at(Size - 1); }

    constexpr bool is_empty() const { return size() == 0; }

    constexpr T const& operator[](size_t index) const { return NULL; /*return at(index);*/ }

    template<typename T2, size_t Size2>
    constexpr bool operator==(Array<T2, Size2> const& other) const { return span() == other.span(); }

    //constexpr operator Span<T const>() const { return span(); }

    T __data[Size];
};

template<typename T, typename... Types>
Array(T, Types...)->Array<T, sizeof...(Types) + 1>;

}

using AK::Array;
