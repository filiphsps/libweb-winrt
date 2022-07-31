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

    constexpr char peek(size_t offset = 0) const;

    void retreat();

    char consume();

    template<typename T>
    constexpr bool consume_specific(const T& next);

    bool consume_specific(String const& next);

    constexpr bool consume_specific(char const* next);

    char consume_escaped_character(char, StringView);

    StringView consume(size_t count);
    StringView consume_all();
    StringView consume_line();
    StringView consume_until(char);
    StringView consume_until(StringView);
    StringView consume_quoted_string(char escape_char = 0);

    enum class UnicodeEscapeError {
        MalformedUnicodeEscape,
        UnicodeEscapeOverflow,
    };

    Result<u32, UnicodeEscapeError> consume_escaped_code_point(bool combine_surrogate_pairs = true);

    constexpr void ignore(size_t count = 1);

    constexpr void ignore_until(char stop);

    constexpr void ignore_until(char const* stop);

    template<typename TPredicate>
    StringView consume_while(TPredicate pred);

    template<typename TPredicate>
    StringView consume_until(TPredicate pred);

protected:
    StringView m_input;
    size_t m_index{ 0 };
};

constexpr auto is_any_of(StringView values)
{
    return [values](auto c) { return values.contains(c); };
}

constexpr auto is_not_any_of(StringView values)
{
    return [values](auto c) { return !values.contains(c); };
}

//constexpr auto is_path_separator = is_any_of("/\\"sv);
//constexpr auto is_quote = is_any_of("'\""sv);

}

using AK::GenericLexer;
using AK::is_any_of;
//using AK::is_path_separator;
//using AK::is_quote;