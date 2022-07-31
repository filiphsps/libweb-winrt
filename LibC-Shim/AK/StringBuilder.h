#pragma once

#include "ByteBuffer.h"
#include "Format.h"
#include "Forward.h"
#include "StringView.h"

namespace AK {

class StringBuilder {
public:
    using OutputType = String;

    explicit StringBuilder(size_t initial_capacity = inline_capacity)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    ~StringBuilder() = default;

    ErrorOr<void> try_append(StringView)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    ErrorOr<void> try_append_code_point(u32)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    ErrorOr<void> try_append(char)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    template<typename... Parameters>
    ErrorOr<void> try_appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    void append(StringView)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append(Utf16View const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append(Utf32View const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append(char)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append_code_point(u32)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append(char const*, size_t)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void appendvf(char const*, va_list)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    void append_as_lowercase(char)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    void append_escaped_for_json(StringView)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    template<typename... Parameters>
    void appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    String build() const;
    String to_string() const;

    ByteBuffer to_byte_buffer() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    StringView string_view() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return StringView();
    }

    void clear()
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    size_t length() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }
    bool is_empty() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return true;
    }
    void trim(size_t count)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    template<class SeparatorType, class CollectionType>
    void join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

private:
    ErrorOr<void> will_append(size_t)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    u8* data() { return m_buffer.data(); }

    static constexpr size_t inline_capacity = 256;
    AK::Detail::ByteBuffer<inline_capacity> m_buffer;
};

}

using AK::StringBuilder;
