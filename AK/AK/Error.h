#pragma once

#include <errno.h>
#include <string.h>
#include "./AK/Optional.h"
#include "./AK/StringView.h"
#include "./AK/Try.h"
#include "./AK/Variant.h"

namespace AK {

class Error {
};

template<typename T, typename ErrorType>
class ErrorOr final : public Variant<T, ErrorType>{
public:
    static Error from_errno(int code) { return Error(code); }
    static Error from_syscall(StringView syscall_name, int rc) { return Error(syscall_name, rc); }
    static Error from_string_view(StringView string_literal) { return Error(string_literal); }

    bool is_errno() const { return m_code != 0; }
    bool is_syscall() const { return m_syscall; }

    int code() const { return m_code; }
    StringView string_literal() const { return m_string_literal; }

protected:
    Error(int code)
        : m_code(code)
    {
    }

private:
    Error(StringView string_literal)
        : m_string_literal(string_literal)
    {
    }

    Error(StringView syscall_name, int rc)
        : m_code(-rc)
        , m_string_literal(syscall_name)
        , m_syscall(true)
    {
    }

    int m_code{ 0 };
    StringView m_string_literal;
    bool m_syscall{ false };
};

}

using AK::Error;
using AK::ErrorOr;