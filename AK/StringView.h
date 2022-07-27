#pragma once

#include "pch.h"
#include "String.h"
#include "StringUtils.h"

namespace AK {

class StringView {
public:
    StringView() = default;
    StringView(char const*, size_t) {}
    StringView(unsigned char const*, size_t) {}

    bool contains(char) const {}
    bool contains(StringView, CaseSensitivity) const {}

    constexpr StringView substring_view(size_t start, size_t length) const { return StringView(); }

    StringView replace(StringView, StringView, ReplaceMode) const {}
    constexpr int compare() { return 0; }
    size_t length() {}

    bool operator==(StringView other) const {}
    bool operator==(char const* cstring) const {}
    bool operator!=(StringView other) const {}
    bool operator<(StringView other) const { return false; }
    bool operator<=(StringView other) const { return false; }
    bool operator>(StringView other) const { return false; }
    bool operator>=(StringView other) const { return false; }
};

}

AK::StringView operator"" sv(char const* str, size_t length) {
    return AK::StringView(str, length);
}

using AK::StringView;