/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Forward.h"
#include "./AK/Optional.h"
#include "./AK/StringBuilder.h"
#include "./AK/String.h"

namespace AK {

class JsonValue {
public:
    enum class Type {
        Null,
        Int32,
        UnsignedInt32,
        Int64,
        UnsignedInt64,
        Double,
        Bool,
        String,
        Array,
        Object,
    };
};

}

using AK::JsonValue;
