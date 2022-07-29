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
    inline PtrType const& ptr_at(size_t index) const { return Base::at(index); }

    inline T& at(size_t index) { return *Base::at(index); }
    inline const T& at(size_t index) const { return *Base::at(index); }
    inline T& operator[](size_t index) { return at(index); }
    inline const T& operator[](size_t index) const { return at(index); }
    inline T& first() { return at(0); }
    inline const T& first() const { return at(0); }
    inline T& last() { return at(size() - 1); }
    inline const T& last() const { return at(size() - 1); }

private:
    // NOTE: You can't use resize() on a NonnullFooPtrVector since making the vector
    //       bigger would require being able to default-construct NonnullFooPtrs.
    //       Instead, use shrink(new_size).
    void resize(size_t) = delete;
};

}
