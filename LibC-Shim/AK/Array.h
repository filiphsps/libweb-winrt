#pragma once

#include <array>
#include "./AK/Iterator.h"
#include "./AK/Span.h"

namespace AK {

template<typename T, size_t Size>
struct Array {
    using ValueType = T;

    constexpr T* data();

    constexpr size_t size();

    constexpr Span<T> span();

    constexpr T const& at(size_t index) const;

    constexpr T const& first() const;
    constexpr T const& last() const requires(Size > 0);

    constexpr bool is_empty() const { return size() == 0; }

    constexpr T const& operator[](size_t index) const;

    template<typename T2, size_t Size2>
    constexpr bool operator==(Array<T2, Size2> const& other);

    using ConstIterator = SimpleIterator<Array const, T const>;
    using Iterator = SimpleIterator<Array, T>;

    constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    constexpr Iterator begin() { return Iterator::begin(*this); }

    constexpr ConstIterator end() const { return ConstIterator::end(*this); }
    constexpr Iterator end() { return Iterator::end(*this); }

    constexpr operator Span<T const>() const;

    T __data[Size];
};

template<typename T, typename... Types>
Array(T, Types...)->Array<T, sizeof...(Types) + 1>;

namespace Detail {

template<typename T, size_t... Is>
constexpr auto integer_sequence_generate_array([[maybe_unused]] T const offset, IntegerSequence<T, Is...>)->Array<T, sizeof...(Is)>;

}

template<typename T, T N>
constexpr static auto iota_array(T const offset = {});

}

using AK::Array;
using AK::iota_array;
