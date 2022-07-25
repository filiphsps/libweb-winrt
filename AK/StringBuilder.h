#pragma once

#include "pch.h"
#include "String.h"
#include "Types.h"

namespace AK {

class StringBuilder {
public:
    using OutputType = String;

    explicit StringBuilder(size_t initial_capacity) {};
    ~StringBuilder() = default;

    void append(String);
    void append(char);
    void append_code_point(u32);
    void append(char const*, size_t);

    String to_string() const;

    void clear();

    size_t length() const { return 0; }
    bool is_empty() const { return true; }
};

}

using AK::StringBuilder;