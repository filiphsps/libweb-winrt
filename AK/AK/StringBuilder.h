#pragma once

#include "./AK/ByteBuffer.h"
#include "./AK/Format.h"
#include "./AK/Forward.h"
#include "./AK/StringView.h"

namespace AK {

class StringBuilder {
public:
    using OutputType = String;

    explicit StringBuilder(size_t initial_capacity = inline_capacity);
    ~StringBuilder() = default;

    ErrorOr<void> try_append(StringView);
    ErrorOr<void> try_append_code_point(u32);
    ErrorOr<void> try_append(char);
    template<typename... Parameters>
    ErrorOr<void> try_appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters);

    void append(StringView) {}
    void append(Utf16View const&);
    void append(Utf32View const&);
    void append(char) {}
    void append_code_point(u32) {}
    void append(char const*, size_t) {}
    void appendvf(char const*, va_list) {}

    void append_as_lowercase(char) {}
    void append_escaped_for_json(StringView) {}

    template<typename... Parameters>
    void appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters) {}

    String build() const;
    String to_string() const;
    ByteBuffer to_byte_buffer() const;

    StringView string_view() const;

    void clear() {}

    size_t length() const { return 0; }
    bool is_empty() const { return true; }
    void trim(size_t count) { /*m_buffer.resize(m_buffer.size() - count);*/ }

    template<class SeparatorType, class CollectionType>
    void join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv) {}

private:
    ErrorOr<void> will_append(size_t);
    u8* data() { return m_buffer.data(); }

    static constexpr size_t inline_capacity = 256;
    AK::Detail::ByteBuffer<inline_capacity> m_buffer;
};

}

using AK::StringBuilder;