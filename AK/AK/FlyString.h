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

    inline StringView view() const { }
};

}

using AK::FlyString;