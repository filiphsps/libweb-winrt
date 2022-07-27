#pragma once

#include "./AK/Forward.h"
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
        //string.m_impl = move(impl);
        return string;
    }

    inline StringView view() const;
};

}

using AK::FlyString;