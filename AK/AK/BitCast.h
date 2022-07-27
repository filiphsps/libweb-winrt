/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <bit>

namespace AK {

template<typename T, typename U>
inline T bit_cast(const U& a)
{
    return std::bit_cast<T>(a);
}

}

using AK::bit_cast;