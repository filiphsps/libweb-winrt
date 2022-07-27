#pragma once

#include <array>

namespace AK {

template<typename T, size_t Size>
struct Array {
    using ValueType = T;

    constexpr T const* data() const { return __data; }
    constexpr T* data() { return __data; }

    constexpr T& operator[](size_t index) { return at(index); }

    T __data[Size];
};

template<typename T, typename... Types>
Array(T, Types...)->Array<T, sizeof...(Types) + 1>;

}

using AK::Array;