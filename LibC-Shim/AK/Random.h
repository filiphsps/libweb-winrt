/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <stdlib.h>
#include "Platform.h"
#include "Types.h"

namespace AK {

ALWAYS_INLINE void fill_with_random(void* buffer, size_t length)
{
}

template<typename T>
ALWAYS_INLINE T get_random()
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
