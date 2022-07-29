/*
 * Copyright (c) 2021, Idan Horowitz <idan.horowitz@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Concepts.h"
#include "./AK/Error.h"
#include "./AK/Noncopyable.h"
#include "./AK/kmalloc.h"

namespace AK {

template<Integral K>
class BaseRedBlackTree {
    AK_MAKE_NONCOPYABLE(BaseRedBlackTree);
    AK_MAKE_NONMOVABLE(BaseRedBlackTree);

public:
    size_t size() const;
    bool is_empty() const;

    enum class Color : bool {
        Red,
        Black
    };
    struct Node {
        Node* left_child { nullptr };
        Node* right_child { nullptr };
        Node* parent { nullptr };

        Color color { Color::Red };

        K key;

        Node(K key)
            : key(key)
        {
        }
        Node()
        {
        }
        virtual ~Node() {};
    };

protected:
    BaseRedBlackTree() = default; // These are protected to ensure no one instantiates the leaky base red black tree directly
    virtual ~BaseRedBlackTree() = default;

    void rotate_left(Node* subtree_root);

    void rotate_right(Node* subtree_root);

    static Node* find(Node* node, K key);

    static Node* find_largest_not_above(Node* node, K key);

    static Node* find_smallest_not_below(Node* node, K key);

    void insert(Node* node);

    void insert_fixups(Node* node);

    void remove(Node* node);

    // We maintain parent as a separate argument since node might be null
    void remove_fixups(Node* node, Node* parent);

    static Node* successor(Node* node);

    static Node* predecessor(Node* node);

    Node* m_root { nullptr };
    size_t m_size { 0 };
    Node* m_minimum { nullptr }; // maintained for O(1) begin()
};

template<typename TreeType, typename ElementType>
class RedBlackTreeIterator {
public:
    RedBlackTreeIterator() = default;
    bool operator!=(RedBlackTreeIterator const& other) const;
    RedBlackTreeIterator& operator++();
    RedBlackTreeIterator& operator--();
    ElementType& operator*();
    ElementType* operator->();
    bool is_end() const;
    bool is_begin() const;

    auto key() const;

private:
    friend TreeType;
    explicit RedBlackTreeIterator(typename TreeType::Node* node, typename TreeType::Node* prev = nullptr)
        : m_node(node)
        , m_prev(prev)
    {
    }
    typename TreeType::Node* m_node { nullptr };
    typename TreeType::Node* m_prev { nullptr };
};

template<Integral K, typename V>
class RedBlackTree final : public BaseRedBlackTree<K> {
public:
    RedBlackTree() = default;
    virtual ~RedBlackTree() override
    {
        clear();
    }

    using BaseTree = BaseRedBlackTree<K>;

    V* find(K key);

    V* find_largest_not_above(K key);

    V* find_smallest_not_below(K key);

    ErrorOr<void> try_insert(K key, V const& value);

    void insert(K key, V const& value);

    ErrorOr<void> try_insert(K key, V&& value);

    void insert(K key, V&& value);

    using Iterator = RedBlackTreeIterator<RedBlackTree, V>;
    friend Iterator;
    Iterator begin();
    Iterator end();
    Iterator begin_from(K key);

    using ConstIterator = RedBlackTreeIterator<const RedBlackTree, const V>;
    friend ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator begin_from(K key) const;

    ConstIterator find_largest_not_above_iterator(K key) const;

    ConstIterator find_smallest_not_below_iterator(K key) const;

    V unsafe_remove(K key);

    bool remove(K key);

    void clear();

private:
    struct Node : BaseRedBlackTree<K>::Node {

        V value;

        Node(K key, V value)
            : BaseRedBlackTree<K>::Node(key)
            , value(move(value))
        {
        }

        ~Node()
        {
            delete this->left_child;
            delete this->right_child;
        }
    };
};

}

using AK::RedBlackTree;
