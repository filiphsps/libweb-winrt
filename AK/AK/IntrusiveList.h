/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <list>
#include "./AK/Assertions.h"
#include "./AK/BitCast.h"
#include "./AK/Forward.h"
#include "./AK/IntrusiveDetails.h"
#include "./AK/Noncopyable.h"
#include "./AK/StdLibExtras.h"

namespace AK {

template<typename T>
class IntrusiveListNode {
public:
    void remove();
};

template<auto member>
class IntrusiveList {};

// Thanks to https://stackoverflow.com/a/59139500/3142553
template<typename NodeType, typename T, T NodeType::* P>
class IntrusiveList<P> {
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

    class Iterator {
    public:
        Iterator() = default;
        Iterator(T* value)
            : m_value(move(value))
        {
        }

        const T& operator*() const;
        auto operator->() const;
        T& operator*();
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
};

}

using AK::IntrusiveList;
using AK::IntrusiveListNode;
