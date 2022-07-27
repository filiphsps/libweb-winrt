#pragma once

#include "./AK/Forward.h"
#include "./AK/StdLibExtras.h"


namespace AK::Concepts {

template<typename T, typename U>
concept HashCompatible = IsHashCompatible<Detail::Decay<T>, Detail::Decay<U>>;

}