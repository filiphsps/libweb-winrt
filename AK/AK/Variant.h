#pragma once

#include "./AK/Forward.h"

namespace AK {

struct Empty {
};

template<typename... Ts>
struct Variant {
public:
    Variant() = default;
    template<typename T>
    Variant(T);
};

}

using AK::Empty;
using AK::Variant;