/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <list>
#include "Assertions.h"
#include "BitCast.h"
#include "Forward.h"
#include "IntrusiveDetails.h"
#include "Noncopyable.h"
#include "StdLibExtras.h"

namespace AK {

template<typename T>
class IntrusiveListNode {
public:
    void remove();
    bool is_in_list() const;
};

template<auto member>
class IntrusiveList {};

// Thanks to https://stackoverflow.com/a/59139500/3142553
template<typename NodeType, typename T, T NodeType::* P>
class IntrusiveList<P> {
    AK_MAKE_NONCOPYABLE(IntrusiveList);
    AK_MAKE_NONMOVABLE(IntrusiveList);

public:
    IntrusiveList() = default;
    ~IntrusiveList();

    void clear();
    bool is_empty();
    size_t size_slow();
    void append(NodeType&);
    void prepend(NodeType&);
    void insert_before(NodeType&, NodeType&);
    void remove(NodeType&);

    bool contains(const T&) const;
    NodeType* first();
    NodeType* last();

    NodeType take_first();
    NodeType take_last();

    class Iterator {
    public:
        Iterator() = default;
        Iterator(T* value)
            : m_value(move(value))
        {
        }

        const NodeType& operator*() const;
        auto operator->() const;
        NodeType& operator*();
        auto operator->();
        bool operator==(Iterator const& other) const;
        bool operator!=(Iterator const& other) const;
        Iterator& operator++();
        Iterator& erase();

    private:
        T* m_value{ nullptr };
    };

    Iterator begin();
    Iterator end() { return Iterator{}; }

    class ReverseIterator {
    public:
        ReverseIterator() = default;
        ReverseIterator(T* value)
            : m_value(move(value))
        {
        }

        const NodeType& operator*();
        auto operator->() const { return m_value; }
        NodeType& operator*();
        auto operator->() { return m_value; }
        bool operator==(ReverseIterator const& other) const;
        bool operator!=(ReverseIterator const& other) const;
        ReverseIterator& operator++();
        ReverseIterator& erase();

    private:
        T* m_value{ nullptr };
    };

    ReverseIterator rbegin();
    ReverseIterator rend() { return ReverseIterator{}; }

    class ConstIterator {
    public:
        ConstIterator() = default;
        ConstIterator(const T* value)
            : m_value(value)
        {
        }

        const NodeType& operator*() const;
        auto operator->() const;
        bool operator==(ConstIterator const& other) const;
        bool operator!=(ConstIterator const& other) const;
        ConstIterator& operator++();

    private:
        const T* m_value{ nullptr };
    };

    ConstIterator begin() const;
    ConstIterator end() const { return ConstIterator{}; }
};

}

using AK::IntrusiveList;
using AK::IntrusiveListNode;
