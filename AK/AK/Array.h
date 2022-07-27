#pragma once

#include <array>

namespace AK {

template<typename T, size_t Size>
struct Array {
    using ValueType = T;

    constexpr T const* data() const { return __data; }
    constexpr T* data() { return __data; }

    T __data[Size];
};

}

using AK::Array;