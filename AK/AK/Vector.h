#pragma once

#include <vector>
#include "./AK/Span.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Traits.h"

namespace AK {

template<typename T, size_t inline_capacity>
requires(!IsRvalueReference<T>) class Vector {
private:
    using VisibleType = RemoveReference<T>;

public:
    using ValueType = T;

    inline void append(T&& value) {}
    inline size_t size() const { return 0; }

    inline VisibleType const& at(size_t i) const { }
    inline VisibleType& at(size_t i) const { }

    VisibleType const& operator[](size_t i) const { return at(i); }
    VisibleType& operator[](size_t i) { return at(i); }
};

}

using AK::Vector;