#pragma once

#include "StringView.h"

class UnicodeEscapeError {
public:
    bool is_error() {
        return true;
    }
    u32 value() {}
    GenericLexer::UnicodeEscapeError error() {}
};

namespace AK {

class GenericLexer {
public:
    constexpr explicit GenericLexer(StringView input) {}

    bool is_eof() {
        return true;
    }
    bool next_is(char*) {
        return false;
    }
    bool next_is(char) {
        return false;
    }
    bool next_is(StringView) {
        return false;
    }

    u32 peek() {}
    u32 peek(u32) {}

    char consume() {}
    StringView consume(size_t) {}
    UnicodeEscapeError consume_escaped_code_point() {}
    char consume_escaped_character(char, StringView) {}
    void ignore() {}
    void ignore(u32) {}
    void retreat() {}

    enum class UnicodeEscapeError {
        MalformedUnicodeEscape,
        UnicodeEscapeOverflow,
    };
};

}

using AK::GenericLexer;