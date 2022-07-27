#pragma once

#include "./AK/Assertions.h"
#include "./AK/Forward.h"
#include "./AK/StringBuilder.h"

namespace AK {

class String {
public:
    String() = default;
    String(const char*);
    String(StringView);

    char* characters() const { return (char*)""; }
    int length();
    bool is_null() { return true; }
    String replace(StringView, StringView, ReplaceMode) const;
    size_t count(StringView) const;

    inline char const& operator[](size_t i) const { return ' '; }
};

}

using AK::String;