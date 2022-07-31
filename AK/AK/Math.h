#pragma once

#include "./AK/BuiltinWrappers.h"
#include "./AK/Concepts.h"
#include "./AK/NumericLimits.h"
#include "./AK/StdLibExtraDetails.h"
#include "./AK/Types.h"

namespace AK {

//template<FloatingPoint T>
//constexpr T NaN = __builtin_nan("");
template<FloatingPoint T>
constexpr T Pi = 3.141592653589793238462643383279502884L;
template<FloatingPoint T>
constexpr T E = 2.718281828459045235360287471352662498L;
template<FloatingPoint T>
constexpr T Sqrt2 = 1.414213562373095048801688724209698079L;
template<FloatingPoint T>
constexpr T Sqrt1_2 = 0.707106781186547524400844362104849039L;

template<Integral I>
inline I round_to(float value);

template<FloatingPoint T>
constexpr T hypot(T x, T y);

template<FloatingPoint T>
constexpr T exp2(T exponent)
{
    return __builtin_exp2(exponent);
};

}

using AK::round_to;
