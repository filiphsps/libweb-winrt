#pragma once

#ifdef ALWAYS_INLINE
#    undef ALWAYS_INLINE
#endif
#define ALWAYS_INLINE __attribute__((always_inline)) inline

namespace AK {

template<typename T>
constexpr T&& move(T& arg)
{
    return static_cast<T&&>(arg);
}

}

using AK::move;