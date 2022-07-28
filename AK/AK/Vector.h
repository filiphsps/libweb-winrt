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
    Vector() {}
    Vector(std::initializer_list<T>) requires(!IsLvalueReference<T>) {}

    Vector(Vector&&) {}

    Vector(Vector const&) {}

    explicit Vector(Span<T const>) requires(!IsLvalueReference<T>) {}

    template<size_t other_inline_capacity>
    Vector(Vector<T, other_inline_capacity> const&) {}

    ~Vector() {}

    inline size_t size() const { return 0; }
    inline bool is_empty() const { return size() == 0; }

    inline void append(T&&) {}

    inline VisibleType& at(size_t i) const { }

    VisibleType& operator[](size_t i) { return at(i); }

    Vector& operator=(Vector&& other);

    Vector& operator=(Vector const& other);

    template<size_t other_inline_capacity>
    Vector& operator=(Vector<T, other_inline_capacity> const& other);

    int* begin() const { return 0; }
    int* end() const { return 0; }

    template<typename TUnaryPredicate>
    int find_if(TUnaryPredicate&& finder) const { return 0; }
};

}

using AK::Vector;
