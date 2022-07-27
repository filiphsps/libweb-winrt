#pragma once

#include "./AK/Forward.h"
#include "./AK/StringView.h"

namespace AK {

class StringBuilder {
public:
    StringBuilder() = default;
    StringBuilder(size_t initial_capacity);
    ~StringBuilder() = default;

    void append(StringView) {}
    void append(char) {}
    void append_code_point(u32) {}
    void append(char const*, size_t) {}

    String build() const;
    String to_string() const;

    void clear() {}

    size_t length() const { return 0; }
    bool is_empty() const { return true; }
};

}

using AK::StringBuilder;