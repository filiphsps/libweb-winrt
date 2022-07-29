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
   
    bool is_null() { return true; }
    inline bool is_empty() const { return true; }
    inline int length();
    char* characters() const { return (char*)""; }

    String replace(StringView, StringView, ReplaceMode) const;
    size_t count(StringView) const;

    u32 hash() const { return 0; }

    template<typename... Parameters>
    static String formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters) {}

    template<typename T>
    static String number(T value) requires IsArithmetic<T>
    {
        return formatted("{}", value);
    }

    inline char const& operator[](size_t i) const { return ' '; }

    StringView view() const;

private:
    RefPtr<StringImpl> m_impl;
};

String escape_html_entities(StringView html);

}

using AK::escape_html_entities;
using AK::String;
