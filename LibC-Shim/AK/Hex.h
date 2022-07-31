/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "ByteBuffer.h"
#include "Error.h"
#include "StringView.h"
#include "String.h"

namespace AK {

constexpr u8 decode_hex_digit(char digit)
{
    if (digit >= '0' && digit <= '9')
        return digit - '0';
    if (digit >= 'a' && digit <= 'f')
        return 10 + (digit - 'a');
    if (digit >= 'A' && digit <= 'F')
        return 10 + (digit - 'A');
    return 255;
}

ErrorOr<ByteBuffer> decode_hex(StringView);

String encode_hex(ReadonlyBytes);

}

using AK::decode_hex;
using AK::decode_hex_digit;
using AK::encode_hex;
