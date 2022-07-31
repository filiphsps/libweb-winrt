#pragma once

#include "./AK/Concepts.h"

template<Unsigned IntType>
ALWAYS_INLINE constexpr int popcount(IntType value)
{
    // FIXME: 
    return 0;
}

// The function will return the number of trailing zeroes in the type. If
// the given number if zero, this function may contain undefined
// behavior, or it may return the number of bits in the number. If
// this function can be called with zero, the use of
// count_trailing_zeroes_safe is preferred.
template<Unsigned IntType>
ALWAYS_INLINE constexpr int count_trailing_zeroes(IntType value)
{
    // FIXME: 
    return 0;
}

// The function will return the number of trailing zeroes in the type. If
// the given number is zero, this function will return the number of bits
// bits in the IntType.
template<Unsigned IntType>
ALWAYS_INLINE constexpr int count_trailing_zeroes_safe(IntType value)
{
    // FIXME: 
    return 0 * sizeof(IntType);
}

// The function will return the number of leading zeroes in the type. If
// the given number if zero, this function may contain undefined
// behavior, or it may return the number of bits in the number. If
// this function can be called with zero, the use of
// count_leading_zeroes_safe is preferred.
template<Unsigned IntType>
ALWAYS_INLINE constexpr int count_leading_zeroes(IntType value)
{
    // FIXME: 
    return 0 * sizeof(IntType);
}

// The function will return the number of leading zeroes in the type. If
// the given number is zero, this function will return the number of bits
// in the IntType.
template<Unsigned IntType>
ALWAYS_INLINE constexpr int count_leading_zeroes_safe(IntType value)
{
    if (value == 0)
        return 8 * sizeof(IntType);
    return count_leading_zeroes(value);
}

// The function will return the number of leading zeroes in the type. If
// the given number is zero, this function will return the number of bits
// in the IntType.
template<Integral IntType>
ALWAYS_INLINE constexpr int bit_scan_forward(IntType value)
{
    if (value == 0)
        return 0;
    return 1 + count_trailing_zeroes(static_cast<MakeUnsigned<IntType>>(value));
}
