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

    char* characters() const { return (char*)""; }
    int length();
    bool is_null() { return true; }
    String replace(StringView, StringView, ReplaceMode) const;
    size_t count(StringView) const;

    template<typename... Parameters>
    static String formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters) {}

    inline char const& operator[](size_t i) const { return ' '; }

private:
    RefPtr<StringImpl> m_impl;
};

}

using AK::String;