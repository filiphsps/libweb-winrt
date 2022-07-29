#pragma once
#pragma warning(disable: 4455)

#include "./AK/Assertions.h"
#include "./AK/Forward.h"
#include "./AK/Span.h"
#include "./AK/StringUtils.h"

namespace AK {

class StringView {
public:
    inline constexpr StringView() = default;
    inline constexpr StringView(char const*, size_t) {}
    inline StringView(unsigned char const* characters, size_t length)
        : m_characters((char const*)characters)
        , m_length(length)
    {
        //VERIFY(!Checked<uintptr_t>::addition_would_overflow((uintptr_t)characters, length));
    }
    inline StringView(ReadonlyBytes bytes)
        : m_characters(reinterpret_cast<char const*>(bytes.data()))
        , m_length(bytes.size())
    {
    }

    StringView(ByteBuffer const&);
    StringView(String const&);
    StringView(FlyString const&);

    explicit StringView(ByteBuffer&&) = delete;
    explicit StringView(String&&) = delete;
    explicit StringView(FlyString&&) = delete;

    constexpr bool is_null() const;
    constexpr bool is_empty() const { return m_length == 0; }

    constexpr char const* characters_without_null_termination() const { return m_characters; }
    constexpr size_t length() const { return m_length; }

    bool contains(char) const { return false; }
    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const { return false; }

    constexpr StringView substring_view(size_t start, size_t length) const { return StringView(); }

    StringView replace(StringView, StringView, ReplaceMode) const { return StringView(); }
    constexpr int compare() { return 0; }

    constexpr int* begin() const { return 0; }
    constexpr int* end() const { return 0; }

    bool operator==(StringView other) const { return false; }
    bool operator==(char const* cstring) const { return false; }
    bool operator!=(StringView other) const { return false; }
    bool operator<(StringView other) const { return false; }
    bool operator<=(StringView other) const { return false; }
    bool operator>(StringView other) const { return false; }
    bool operator>=(StringView other) const { return false; }

    String to_string() const;

private:
    friend class String;
    char const* m_characters{ nullptr };
    size_t m_length{ 0 };
};

}

AK::StringView operator"" sv(char const* str, size_t length) {
    return AK::StringView(str, length);
}

using AK::StringView;