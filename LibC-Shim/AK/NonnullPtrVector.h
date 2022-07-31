/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

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

    ALWAYS_INLINE constexpr ConstIterator begin() const;
    ALWAYS_INLINE constexpr Iterator begin();
    ALWAYS_INLINE constexpr ReverseIterator rbegin();
    ALWAYS_INLINE constexpr ReverseConstIterator rbegin() const;

    ALWAYS_INLINE constexpr ConstIterator end() const;
    ALWAYS_INLINE constexpr Iterator end();
    ALWAYS_INLINE constexpr ReverseIterator rend();
    ALWAYS_INLINE constexpr ReverseConstIterator rend() const;

    ALWAYS_INLINE constexpr auto in_reverse();

    Optional<size_t> find_first_index(T const& value) const;

    ALWAYS_INLINE PtrType& ptr_at(size_t index);
    ALWAYS_INLINE PtrType const& ptr_at(size_t index) const { return Base::at(index); }

    ALWAYS_INLINE T& at(size_t index) { return *Base::at(index); }
    ALWAYS_INLINE const T& at(size_t index) const { return *Base::at(index); }
    ALWAYS_INLINE T& operator[](size_t index) { return at(index); }
    ALWAYS_INLINE const T& operator[](size_t index) const { return at(index); }
    ALWAYS_INLINE T& first() { return at(0); }
    ALWAYS_INLINE const T& first() const { return at(0); }
    ALWAYS_INLINE T& last() { return at(size() - 1); }
    ALWAYS_INLINE const T& last() const { return at(size() - 1); }

private:
    // NOTE: You can't use resize() on a NonnullFooPtrVector since making the vector
    //       bigger would require being able to default-construct NonnullFooPtrs.
    //       Instead, use shrink(new_size).
    void resize(size_t) = delete;
};

}
