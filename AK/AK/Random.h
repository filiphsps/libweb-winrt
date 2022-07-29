/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <stdlib.h>
#include "./AK/Platform.h"
#include "./AK/Types.h"

namespace AK {

inline void fill_with_random(void* buffer, size_t length)
{
}

template<typename T>
inline T get_random()
{
    T t;
    fill_with_random(&t, sizeof(T));
    return t;
}

u32 get_random_uniform(u32 max_bounds);

}

using AK::fill_with_random;
using AK::get_random;
using AK::get_random_uniform;
