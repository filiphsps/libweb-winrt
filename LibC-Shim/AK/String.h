#pragma once

#include "Format.h"
#include "Forward.h"
#include "RefPtr.h"
//#include "Stream.h"
#include "StringBuilder.h"
#include "StringImpl.h"
#include "StringUtils.h"
#include "Traits.h"

namespace AK {

class String {
public:
    ~String() = default;

    String() = default;
    
    String(StringView view)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(String const& other)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(String&& other)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(char const* cstring, ShouldChomp shouldChomp = NoChomp)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(char const* cstring, size_t length, ShouldChomp shouldChomp = NoChomp)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    explicit String(ReadonlyBytes bytes, ShouldChomp shouldChomp = NoChomp)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(StringImpl const& impl)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(StringImpl const* impl)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(RefPtr<StringImpl>&& impl)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(NonnullRefPtr<StringImpl>&& impl)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    String(FlyString const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    static String repeated(char, size_t count)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }
    static String repeated(StringView, size_t count)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }

    static String bijective_base_from(size_t value, unsigned base = 26, StringView map = {})
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }
    static String roman_number_from(size_t value)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }

    template<class SeparatorType, class CollectionType>
    static String join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        StringBuilder builder;
        builder.join(separator, collection, fmtstr);
        return builder.build();
    }

    bool matches(StringView mask, CaseSensitivity = CaseSensitivity::CaseInsensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool matches(StringView mask, Vector<MaskSpan>&, CaseSensitivity = CaseSensitivity::CaseInsensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    template<typename T = int>
    Optional<T> to_int(TrimWhitespace = TrimWhitespace::Yes) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    template<typename T = unsigned>
    Optional<T> to_uint(TrimWhitespace = TrimWhitespace::Yes) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool contains(char, CaseSensitivity = CaseSensitivity::CaseSensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    Vector<String> split_limit(char separator, size_t limit, bool keep_empty = false) const;
    Vector<String> split(char separator, bool keep_empty = false) const;
    Vector<StringView> split_view(char separator, bool keep_empty = false) const;
    Vector<StringView> split_view(Function<bool(char)> separator, bool keep_empty = false) const;

    Optional<size_t> find(char needle, size_t start = 0) const;
    Optional<size_t> find(StringView needle, size_t start = 0) const;
    Optional<size_t> find_last(char needle) const;
    Vector<size_t> find_all(StringView needle) const;
    using SearchDirection = StringUtils::SearchDirection;
    Optional<size_t> find_any_of(StringView needles, SearchDirection direction) const;

    String substring(size_t start, size_t length) const;
    String substring(size_t start) const;
    StringView substring_view(size_t start, size_t length) const;
    StringView substring_view(size_t start) const;

    ALWAYS_INLINE ReadonlyBytes bytes() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    ALWAYS_INLINE char const& operator[](size_t i) const;

    using ConstIterator = SimpleIterator<const String, char const>;

    constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    constexpr ConstIterator end() const { return ConstIterator::end(*this); }

    bool starts_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool ends_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool starts_with(char) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool ends_with(char) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    bool is_null() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    ALWAYS_INLINE bool is_empty() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return true;
    }
    ALWAYS_INLINE size_t length() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }
    char* characters() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return nullptr;
    }

    u32 hash() const { return 0; }

    [[nodiscard]] ByteBuffer to_byte_buffer() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    template<typename BufferType>
    [[nodiscard]] static String copy(BufferType const& buffer, ShouldChomp should_chomp = NoChomp)
    {
        if (buffer.is_empty())
            return empty();
        return String((char const*)buffer.data(), buffer.size(), should_chomp);
    }

    [[nodiscard]] static String vformatted(StringView fmtstr, TypeErasedFormatParams&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }

    template<typename... Parameters>
    [[nodiscard]] static String formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        VariadicFormatParams variadic_format_parameters { parameters... };
        return vformatted(fmtstr.view(), variadic_format_parameters);
    }

    template<typename T>
    [[nodiscard]] static String number(T value) requires IsArithmetic<T>
    {
        return formatted("{}", value);
    }

    [[nodiscard]] StringView view() const
    {
        return { characters(), length() };
    }

    [[nodiscard]] static String empty()
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }

    bool operator==(String const&) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator!=(String const& other) const { return !(*this == other); }

    bool operator==(StringView) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator!=(StringView other) const { return !(*this == other); }

    bool operator==(FlyString const&) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator!=(FlyString const& other) const { return !(*this == other); }

    bool operator<(String const&) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator<(char const*) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator>=(String const& other) const { return !(*this < other); }
    bool operator>=(char const* other) const { return !(*this < other); }

    bool operator>(String const&) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator>(char const*) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator<=(String const& other) const { return !(*this > other); }
    bool operator<=(char const* other) const { return !(*this > other); }

    bool operator==(char const* cstring) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator!=(char const* cstring) const { return !(*this == cstring); }

    String& operator=(String&& other)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return *this;
    }

    String& operator=(String const& other)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return *this;
    }

    String& operator=(std::nullptr_t)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return *this;
    }

    String& operator=(ReadonlyBytes bytes)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return *this;
    }

    String replace(StringView needle, StringView replacement, ReplaceMode replace_mode) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }
    size_t count(StringView needle) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }
    String reverse() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return String();
    }

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of(Ts&&... strings) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of_ignoring_case(Ts&&... strings) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

private:
    RefPtr<StringImpl> m_impl;
};

template<>
struct Traits<String> : public GenericTraits<String> {
    static unsigned hash(String const& s);
};

struct CaseInsensitiveStringTraits : public Traits<String> {
    static unsigned hash(String const& s)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }
    static bool equals(String const& a, String const& b)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
};

String escape_html_entities(StringView html)
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return String();
}

//InputStream& operator>>(InputStream& stream, String& string);

}

using AK::escape_html_entities;
using AK::String;
