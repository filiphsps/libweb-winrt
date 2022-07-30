#pragma once

#include "./AK/BuiltinWrappers.h"
#include "./AK/Concepts.h"
#include "./AK/NumericLimits.h"
#include "./AK/StdLibExtraDetails.h"
#include "./AK/Types.h"

namespace AK {

template<FloatingPoint T>
constexpr T exp2(T exponent)
{
    return __builtin_exp2(exponent);
};

}
