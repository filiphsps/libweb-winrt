#pragma once

#include "./AK/Format.h"
#include "./AK/Forward.h"
#include "./AK/RefPtr.h"
#include "./AK/StringBuilder.h"
#include "./AK/StringImpl.h"
#include "./AK/StringUtils.h"
#include "./AK/Traits.h"

namespace AK {

class String {
public:
    String() = default;
    String(const char*);
    String(StringView);
    String(FlyString const&);

    template<class SeparatorType, class CollectionType>
    static String join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        StringBuilder builder;
        builder.join(separator, collection, fmtstr);
        return builder.build();
    }

    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    bool contains(char, CaseSensitivity = CaseSensitivity::CaseSensitive) const;

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
   
    bool is_null() { return true; }
    inline bool is_empty() const { return true; }
    inline int length();
    char* characters() const;

    String replace(StringView, StringView, ReplaceMode) const;
    size_t count(StringView) const;

    u32 hash() const { return 0; }

    template<typename... Parameters>
    static String formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters);

    template<typename T>
    static String number(T value) requires IsArithmetic<T>;

    inline char const& operator[](size_t i) const;

    StringView view() const;

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

    static String empty();

private:
    RefPtr<StringImpl> m_impl;
};

String escape_html_entities(StringView html);

}

using AK::escape_html_entities;
using AK::String;
