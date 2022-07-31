/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Find.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Traits.h"
#include "./AK/Types.h"

namespace AK {

template<typename ListType, typename ElementType>
class SinglyLinkedListIterator {
public:
    SinglyLinkedListIterator() = default;
    bool operator!=(SinglyLinkedListIterator const& other) const;
    SinglyLinkedListIterator& operator++();
    ElementType& operator*();
    ElementType* operator->();
    bool is_end() const { return !m_node; }
    bool is_begin() const { return !m_prev; }
    void remove(ListType& list);

private:
    friend ListType;
    explicit SinglyLinkedListIterator(typename ListType::Node* node, typename ListType::Node* prev = nullptr)
        : m_node(node)
        , m_prev(prev)
        , m_next(node ? node->next : nullptr)
    {
    }
    typename ListType::Node* m_node { nullptr };
    typename ListType::Node* m_prev { nullptr };
    typename ListType::Node* m_next { nullptr };
    bool m_removed { false };
};

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        explicit Node(T&& v)
            : value(move(v))
        {
        }
        explicit Node(const T& v)
            : value(v)
        {
        }
        T value;
        Node* next { nullptr };
    };

public:
    SinglyLinkedList() = default;
    SinglyLinkedList(SinglyLinkedList const& other) = delete;
    SinglyLinkedList(SinglyLinkedList&& other)
        : m_head(other.m_head)
        , m_tail(other.m_tail)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }
    SinglyLinkedList& operator=(SinglyLinkedList const& other) = delete;
    SinglyLinkedList& operator=(SinglyLinkedList&&) = delete;

    ~SinglyLinkedList() { clear(); }

    bool is_empty() const { return !head(); }

    ALWAYS_INLINE size_t size_slow() const;

    void clear();

    T& first();
    T& last();

    T take_first();

    template<typename U = T>
    void append(U&& value);

    template<typename U = T>
    void prepend(U&& value);

    bool contains_slow(const T& value) const;

    using Iterator = SinglyLinkedListIterator<SinglyLinkedList, T>;
    friend Iterator;
    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return {}; }

    using ConstIterator = SinglyLinkedListIterator<const SinglyLinkedList, const T>;
    friend ConstIterator;
    ConstIterator begin() const { return ConstIterator(m_head); }
    ConstIterator end() const { return {}; }

    template<typename TUnaryPredicate>
    ConstIterator find_if(TUnaryPredicate&& pred) const;

    template<typename TUnaryPredicate>
    Iterator find_if(TUnaryPredicate&& pred);

    ConstIterator find(const T& value) const;

    Iterator find(const T& value);

    template<typename U = T>
    void insert_before(Iterator iterator, U&& value);

    template<typename U = T>
    void insert_after(Iterator iterator, U&& value);

    void remove(Iterator& iterator);

private:
    Node* head() { return m_head; }
    Node const* head() const { return m_head; }

    Node* tail() { return m_tail; }
    Node const* tail() const { return m_tail; }

    Node* m_head { nullptr };
    Node* m_tail { nullptr };
};

}

using AK::SinglyLinkedList;
