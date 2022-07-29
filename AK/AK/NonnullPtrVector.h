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

    using Base::size;

    using ConstIterator = SimpleIterator<const NonnullPtrVector, const T>;
    using Iterator = SimpleIterator<NonnullPtrVector, T>;
    using ReverseIterator = SimpleReverseIterator<NonnullPtrVector, T>;
    using ReverseConstIterator = SimpleReverseIterator<NonnullPtrVector const, T const>;

    inline constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    inline constexpr Iterator begin() { return Iterator::begin(*this); }
    inline constexpr ReverseIterator rbegin() { return ReverseIterator::rbegin(*this); }
    inline constexpr ReverseConstIterator rbegin() const { return ReverseConstIterator::rbegin(*this); }

    inline constexpr ConstIterator end() const { return ConstIterator::end(*this); }
    inline constexpr Iterator end() { return Iterator::end(*this); }
    inline constexpr ReverseIterator rend() { return ReverseIterator::rend(*this); }
    inline constexpr ReverseConstIterator rend() const { return ReverseConstIterator::rend(*this); }

    inline T& at(size_t index);
    inline T& operator[](size_t index);
    inline T& first();
    inline T& last();
};

}
