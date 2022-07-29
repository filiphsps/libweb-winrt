#pragma once

#include "./AK/Result.h"
#include "./AK/StringView.h"

namespace AK {

class GenericLexer {
public:
    constexpr explicit GenericLexer(StringView input)
        : m_input(input)
    {
    }

    constexpr size_t tell();
    constexpr size_t tell_remaining();

    bool is_eof();
    bool next_is(char*) {
        return false;
    }
    bool next_is(char) {
        return false;
    }
    bool next_is(const char[]) {
        return false;
    }
    bool next_is(StringView) {
        return false;
    }

    u32 peek() { return 0; }
    u32 peek(u32) { return 0; }

    void ignore() {}
    void ignore(u32) {}
    void retreat() {}

    enum class UnicodeEscapeError {
        MalformedUnicodeEscape,
        UnicodeEscapeOverflow,
    };

    char consume() { return ' '; }
    StringView consume(size_t);
    Result<u32, UnicodeEscapeError> consume_escaped_code_point() { return NULL; }
    char consume_escaped_character(char, StringView) { return ' '; }

protected:
    StringView m_input;
    size_t m_index{ 0 };
};

}

using AK::GenericLexer;