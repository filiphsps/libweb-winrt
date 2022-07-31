/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Forward.h"

namespace AK {

template<typename Container, typename ValueType>
class SimpleIterator {
public:
    friend Container;

    constexpr bool is_end() const { return m_index == SimpleIterator::end(m_container).m_index; }
    constexpr size_t index() const { return m_index; }

    constexpr bool operator==(SimpleIterator other) const { return m_index == other.m_index; }
    constexpr bool operator!=(SimpleIterator other) const { return m_index != other.m_index; }
    constexpr bool operator<(SimpleIterator other) const { return m_index < other.m_index; }
    constexpr bool operator>(SimpleIterator other) const { return m_index > other.m_index; }
    constexpr bool operator<=(SimpleIterator other) const { return m_index <= other.m_index; }
    constexpr bool operator>=(SimpleIterator other) const { return m_index >= other.m_index; }

    constexpr SimpleIterator operator+(ptrdiff_t delta) const { return SimpleIterator{ m_container, m_index + delta }; }
    constexpr SimpleIterator operator-(ptrdiff_t delta) const { return SimpleIterator{ m_container, m_index - delta }; }

    constexpr ptrdiff_t operator-(SimpleIterator other) const { return static_cast<ptrdiff_t>(m_index) - other.m_index; }

    constexpr SimpleIterator operator++()
    {
        ++m_index;
        return *this;
    }
    constexpr SimpleIterator operator++(int)
    {
        ++m_index;
        return SimpleIterator{ m_container, m_index - 1 };
    }

    constexpr SimpleIterator operator--()
    {
        --m_index;
        return *this;
    }
    constexpr SimpleIterator operator--(int)
    {
        --m_index;
        return SimpleIterator{ m_container, m_index + 1 };
    }

    ALWAYS_INLINE constexpr ValueType const& operator*() const { return (ValueType const&)m_container[m_index]; }
    ALWAYS_INLINE constexpr ValueType& operator*() { return (ValueType&)m_container[m_index]; }

    ALWAYS_INLINE constexpr ValueType const* operator->() const { return (ValueType const*)&m_container[m_index]; }
    ALWAYS_INLINE constexpr ValueType* operator->() { return (ValueType*)&m_container[m_index]; }

    SimpleIterator& operator=(SimpleIterator const& other)
    {
        m_index = other.m_index;
        return *this;
    }
    SimpleIterator(SimpleIterator const& obj) = default;

private:
    static constexpr SimpleIterator begin(Container& container);
    static constexpr SimpleIterator end(Container& container);

    constexpr SimpleIterator(Container& container, size_t index)
        : m_container(container)
        , m_index(index)
    {
    }

    Container& m_container;
    size_t m_index;
};

}
