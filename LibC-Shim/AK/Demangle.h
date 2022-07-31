/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "String.h"
#include "StringView.h"

namespace AK {

ALWAYS_INLINE String demangle(StringView name);

}

using AK::demangle;
