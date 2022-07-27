#pragma once

#include "pch.h"
#include "Assertions.h"
#include "StringBuilder.h"
#include "StringUtils.h"
#include "Types.h"

namespace AK {

class String {
public:
    String() = default;
    String(const char*) {}
    String(StringView) {}

    char* characters() const {}
    int length() const {
        return 0;
    }
    bool is_null() {}
    String replace(StringView, StringView, ReplaceMode) const {}
    size_t count(StringView) const {}

    char const& operator[](size_t i) const {}
};

}

using AK::String;