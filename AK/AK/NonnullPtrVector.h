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

    NonnullPtrVector(Vector<PtrType>&& other)
        : Base(static_cast<Base&&>(other))
    {
    }
    NonnullPtrVector(Vector<PtrType> const& other)
        : Base(static_cast<Base const&>(other))
    {
    }

    using Base::size;

    using ConstIterator = SimpleIterator<const NonnullPtrVector, const T>;
    using Iterator = SimpleIterator<NonnullPtrVector, T>;
    using ReverseIterator = SimpleReverseIterator<NonnullPtrVector, T>;
    using ReverseConstIterator = SimpleReverseIterator<NonnullPtrVector const, T const>;

    inline constexpr ConstIterator begin() const;
    inline constexpr Iterator begin();
    inline constexpr ReverseIterator rbegin();
    inline constexpr ReverseConstIterator rbegin() const;

    inline constexpr ConstIterator end() const;
    inline constexpr Iterator end();
    inline constexpr ReverseIterator rend();
    inline constexpr ReverseConstIterator rend() const;

    inline constexpr auto in_reverse();

    Optional<size_t> find_first_index(T const& value) const;

    inline PtrType& ptr_at(size_t index);

    inline T& at(size_t index);
    inline T& operator[](size_t index);
    inline T& first();
    inline T& last();
};

}
