#pragma once

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

    void append(StringView) {}
    void append(char) {}
    void append_code_point(u32) {}
    void append(char const*, size_t) {}

    String build() const;
    String to_string() const;

    void clear() {}

    size_t length() const { return 0; }
    bool is_empty() const { return true; }
    void trim(size_t count) { /*m_buffer.resize(m_buffer.size() - count);*/ }

    template<class SeparatorType, class CollectionType>
    void join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        /*bool first = true;
        for (auto& item : collection) {
            if (first)
                first = false;
            else
                append(separator);
            appendff(fmtstr, item);
        }*/
    }

private:
    ErrorOr<void> will_append(size_t);
    //u8* data() { return m_buffer.data(); }
    //u8 const* data() const { return m_buffer.data(); }

    static constexpr size_t inline_capacity = 256;
    //AK::Detail::ByteBuffer<inline_capacity> m_buffer;
};

}

using AK::StringBuilder;