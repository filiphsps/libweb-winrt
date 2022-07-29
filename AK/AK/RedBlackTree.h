/*
 * Copyright (c) 2021, Idan Horowitz <idan.horowitz@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Concepts.h"
#include "./AK/Error.h"
#include "./AK/Noncopyable.h"
#include "./AK/kmalloc.h"

namespace AK {

template<Integral K>
class BaseRedBlackTree {
    AK_MAKE_NONCOPYABLE(BaseRedBlackTree);
    AK_MAKE_NONMOVABLE(BaseRedBlackTree);

};

}