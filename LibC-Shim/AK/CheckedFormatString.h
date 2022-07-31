/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/AllOf.h"
#include "./AK/AnyOf.h"
#include "./AK/Array.h"
#include "./AK/StdLibExtras.h"
#include "./AK/StringView.h"

namespace AK::Format::Detail {
template<typename... Args>
struct CheckedFormatString {
    template<size_t N>
    consteval CheckedFormatString(char const (&fmt)[N])
        : m_string{ fmt, N - 1 }
    {
    }

    template<typename T>
    CheckedFormatString(const T& unchecked_fmt) requires(requires(T t) { StringView{ t }; })
        : m_string(unchecked_fmt)
    {
    }

    auto view() const { return m_string; }

private:
    StringView m_string;
};
}

namespace AK {

template<typename... Args>
using CheckedFormatString = Format::Detail::CheckedFormatString<IdentityType<Args>...>;

}
