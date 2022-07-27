#pragma once

#include "./AK/String.h"
#include "./AK/StringUtils.h"

namespace AK {

class FlyString {
public:
    FlyString() = default;
    FlyString(String const&);
    FlyString(StringView);

    static FlyString from_fly_impl(NonnullRefPtr<StringImpl> impl)
    {
        //VERIFY(impl->is_fly());
        FlyString string;
        string.m_impl = move(impl);
        return string;
    }

    bool operator==(FlyString const& other) const { return m_impl == other.m_impl; }

    StringImpl const* impl() const { return m_impl; }
    char const* characters() const { return nullptr; }
    size_t length() const { return 0; }

    inline StringView view() const;

private:
    RefPtr<StringImpl> m_impl;
};

}

using AK::FlyString;