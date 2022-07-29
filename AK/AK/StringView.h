#pragma once
#pragma warning(disable: 4455)

#include "./AK/Assertions.h"
#include "./AK/Checked.h"
#include "./AK/Forward.h"
#include "./AK/Optional.h"
#include "./AK/Span.h"
#include "./AK/StdLibExtras.h"
#include "./AK/StringHash.h"
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

    ReadonlyBytes bytes() const;
    constexpr char const& operator[](size_t index) const;

    constexpr StringView substring_view(size_t start, size_t length) const;
    constexpr StringView substring_view(size_t start) const;

    StringView replace(StringView, StringView, ReplaceMode) const;
    constexpr int compare() { return 0; }

    constexpr int* begin() const { return 0; }
    constexpr int* end() const { return 0; }

    constexpr unsigned hash() const;

    bool starts_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool ends_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool starts_with(char) const;
    bool ends_with(char) const;
    bool matches(StringView mask, CaseSensitivity = CaseSensitivity::CaseInsensitive) const;
    bool matches(StringView mask, Vector<MaskSpan>&, CaseSensitivity = CaseSensitivity::CaseInsensitive) const;
    bool contains(char) const;
    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool equals_ignoring_case(StringView other) const;

    Vector<StringView> lines(bool consider_cr = true) const;

    template<typename T = int>
    Optional<T> to_int() const;
    template<typename T = unsigned>
    Optional<T> to_uint() const;

    StringView substring_view_starting_from_substring(StringView substring) const;
    StringView substring_view_starting_after_substring(StringView substring) const;

    bool copy_characters_to_buffer(char* buffer, size_t buffer_size) const;

    bool operator==(StringView other) const { return false; }
    bool operator==(char const* cstring) const { return false; }
    bool operator!=(StringView other) const { return false; }
    bool operator<(StringView other) const { return false; }
    bool operator<=(StringView other) const { return false; }
    bool operator>(StringView other) const { return false; }
    bool operator>=(StringView other) const { return false; }

    String to_string() const;

    template<typename... Ts>
    inline constexpr bool is_one_of(Ts&&... strings) const;

    template<typename... Ts>
    inline constexpr bool is_one_of_ignoring_case(Ts&&... strings) const;

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