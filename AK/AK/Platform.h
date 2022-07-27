#pragma once

namespace AK {

template<typename T>
constexpr T&& move(T& arg)
{
    return static_cast<T&&>(arg);
}

}

using AK::move;