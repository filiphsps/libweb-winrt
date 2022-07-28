#pragma once

#include "./AK/Vector.h"
#include "./AK/NonnullPtrVector.h"

namespace AK {

template<typename PtrType, size_t inline_capacity = 0>
class NonnullPtrVector : public Vector<PtrType, inline_capacity> {
    using T = typename PtrType::ElementType;
    using Base = Vector<PtrType, inline_capacity>;

public:
    NonnullPtrVector() = default;

    inline constexpr int* begin();

    inline constexpr int* end();

    inline T& at(size_t index);
    inline T& operator[](size_t index);
    inline T& first();
    inline T& last();
};

}
