#include "pch.h"
#include "FlyString.h"

namespace AK {

FlyString::FlyString(String const&)
{
}

FlyString::FlyString(StringView)
{
}

inline StringView FlyString::view() const
{
    return StringView();
}

}