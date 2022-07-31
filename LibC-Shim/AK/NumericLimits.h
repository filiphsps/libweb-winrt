#pragma once
#undef min
#undef max

#include <limits.h>
#include <float.h>
#include "./AK/Types.h"

namespace AK {

template<typename T>
struct NumericLimits {
};

template<>
struct NumericLimits<bool> {
    static constexpr bool min() { return false; }
    static constexpr bool max() { return true; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<signed char> {
    static constexpr signed char min() { return -SCHAR_MAX - 1; }
    static constexpr signed char max() { return SCHAR_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<char> {
    static constexpr char min() { return -SCHAR_MAX - 1; }
    static constexpr char max() { return SCHAR_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<short> {
    static constexpr short min() { return -SHRT_MAX - 1; }
    static constexpr short max() { return SHRT_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<int> {
    static constexpr int min() { return -INT_MAX - 1; }
    static constexpr int max() { return INT_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<long> {
    static constexpr long min() { return -LONG_MAX - 1; }
    static constexpr long max() { return LONG_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<long long> {
    static constexpr long long min() { return -LLONG_MAX - 1; }
    static constexpr long long max() { return LLONG_MAX; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<unsigned char> {
    static constexpr unsigned char min() { return 0; }
    static constexpr unsigned char max() { return SCHAR_MAX * 2u + 1; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<unsigned short> {
    static constexpr unsigned short min() { return 0; }
    static constexpr unsigned short max() { return SHRT_MAX * 2u + 1; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<unsigned> {
    static constexpr unsigned min() { return 0; }
    static constexpr unsigned max() { return INT_MAX * 2u + 1; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<unsigned long> {
    static constexpr unsigned long min() { return 0; }
    static constexpr unsigned long max() { return LONG_MAX * 2ul + 1; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<unsigned long long> {
    static constexpr unsigned long long min() { return 0; }
    static constexpr unsigned long long max() { return LLONG_MAX * 2ull + 1; }
    static constexpr bool is_signed() { return false; }
};

template<>
struct NumericLimits<float> {
    static constexpr float lowest() { return -FLT_MAX; }
    static constexpr float min() { return FLT_MIN; }
    static constexpr float max() { return FLT_MAX; }
    static constexpr float epsilon() { return FLT_EPSILON; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<double> {
    static constexpr double lowest() { return -DBL_MAX; }
    static constexpr double min() { return DBL_MIN; }
    static constexpr double max() { return DBL_MAX; }
    static constexpr double epsilon() { return DBL_EPSILON; }
    static constexpr bool is_signed() { return true; }
};

template<>
struct NumericLimits<long double> {
    static constexpr long double lowest() { return -LDBL_MAX; }
    static constexpr long double min() { return LDBL_MIN; }
    static constexpr long double max() { return LDBL_MAX; }
    static constexpr long double epsilon() { return LDBL_EPSILON; }
    static constexpr bool is_signed() { return true; }
};

}

using AK::NumericLimits;
