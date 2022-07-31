#pragma once

#include "./AK/Format.h"
#include "./AK/Forward.h"
#include "./AK/RefPtr.h"
//#include "./AK/Stream.h"
#include "./AK/StringBuilder.h"
#include "./AK/StringImpl.h"
#include "./AK/StringUtils.h"
#include "./AK/Traits.h"

namespace AK {

class String {
public:
    ~String() = default;

    String() = default;
    
    String(StringView view);
    String(String const& other);
    String(String&& other);
    String(char const* cstring, ShouldChomp shouldChomp = NoChomp);
    String(char const* cstring, size_t length, ShouldChomp shouldChomp = NoChomp);
    explicit String(ReadonlyBytes bytes, ShouldChomp shouldChomp = NoChomp);
    String(StringImpl const& impl);
    String(StringImpl const* impl);
    String(RefPtr<StringImpl>&& impl);
    String(NonnullRefPtr<StringImpl>&& impl);
    String(FlyString const&);

    static String repeated(char, size_t count);
    static String repeated(StringView, size_t count);

    static String bijective_base_from(size_t value, unsigned base = 26, StringView map = {});
    static String roman_number_from(size_t value);

    template<class SeparatorType, class CollectionType>
    static String join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        StringBuilder builder;
        builder.join(separator, collection, fmtstr);
        return builder.build();
    }

    bool matches(StringView mask, CaseSensitivity = CaseSensitivity::CaseInsensitive) const;
    bool matches(StringView mask, Vector<MaskSpan>&, CaseSensitivity = CaseSensitivity::CaseInsensitive) const;

    template<typename T = int>
    Optional<T> to_int(TrimWhitespace = TrimWhitespace::Yes) const;
    template<typename T = unsigned>
    Optional<T> to_uint(TrimWhitespace = TrimWhitespace::Yes) const;

    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool contains(char, CaseSensitivity = CaseSensitivity::CaseSensitive) const;

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

    ALWAYS_INLINE ReadonlyBytes bytes() const;

    ALWAYS_INLINE char const& operator[](size_t i) const;

    using ConstIterator = SimpleIterator<const String, char const>;

    constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    constexpr ConstIterator end() const { return ConstIterator::end(*this); }

    bool starts_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool ends_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool starts_with(char) const;
    bool ends_with(char) const;

    bool is_null() const { return !m_impl; }
    ALWAYS_INLINE bool is_empty() const { return true; }
    ALWAYS_INLINE size_t length() const { return m_impl ? m_impl->length() : 0; }
    char* characters() const;

    u32 hash() const { return 0; }

    static String vformatted(StringView fmtstr, TypeErasedFormatParams&);

    template<typename... Parameters>
    static String formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters);

    template<typename T>
    static String number(T value) requires IsArithmetic<T>;

    static String empty();

    bool operator==(String const&) const;
    bool operator!=(String const& other) const;

    bool operator==(StringView) const;
    bool operator!=(StringView other) const;

    bool operator==(FlyString const&) const;
    bool operator!=(FlyString const& other) const;

    bool operator<(String const&) const;
    bool operator<(char const*) const;
    bool operator>=(String const& other) const;
    bool operator>=(char const* other) const;

    bool operator>(String const&) const;
    bool operator>(char const*) const;
    bool operator<=(String const& other) const;
    bool operator<=(char const* other) const;

    bool operator==(char const* cstring) const;
    bool operator!=(char const* cstring) const;

    String& operator=(String&& other);

    String& operator=(String const& other);

    String& operator=(std::nullptr_t);

    String& operator=(ReadonlyBytes bytes);

    StringView view() const;

    String replace(StringView needle, StringView replacement, ReplaceMode replace_mode) const;
    size_t count(StringView needle) const;
    String reverse() const;

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of(Ts&&... strings) const;

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of_ignoring_case(Ts&&... strings) const;

private:
    RefPtr<StringImpl> m_impl;
};

template<>
struct Traits<String> : public GenericTraits<String> {
    static unsigned hash(String const& s);
};

struct CaseInsensitiveStringTraits : public Traits<String> {
    static unsigned hash(String const& s);
    static bool equals(String const& a, String const& b);
};

String escape_html_entities(StringView html);

//InputStream& operator>>(InputStream& stream, String& string);

}

using AK::escape_html_entities;
using AK::String;
