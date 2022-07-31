/*
 * Copyright (c) 2021, Idan Horowitz <idan.horowitz@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "IntrusiveDetails.h"
#include "RedBlackTree.h"

namespace AK::Detail {

template<Integral K, typename V, typename Container = RawPtr<V>>
class IntrusiveRedBlackTreeNode;

struct ExtractIntrusiveRedBlackTreeTypes {
    template<typename K, typename V, typename Container, typename T>
    static K key(IntrusiveRedBlackTreeNode<K, V, Container> T::*x);
    template<typename K, typename V, typename Container, typename T>
    static V value(IntrusiveRedBlackTreeNode<K, V, Container> T::*x);
    template<typename K, typename V, typename Container, typename T>
    static Container container(IntrusiveRedBlackTreeNode<K, V, Container> T::*x);
};

template<Integral K, typename V, typename Container = RawPtr<V>>
using SubstitutedIntrusiveRedBlackTreeNode = IntrusiveRedBlackTreeNode<K, V, typename Detail::SubstituteIntrusiveContainerType<V, Container>::Type>;

template<Integral K, typename V, typename Container, SubstitutedIntrusiveRedBlackTreeNode<K, V, Container> V::*member>
class IntrusiveRedBlackTree : public BaseRedBlackTree<K> {

public:
    IntrusiveRedBlackTree() = default;
    virtual ~IntrusiveRedBlackTree() override
    {
        clear();
    }

    using BaseTree = BaseRedBlackTree<K>;
    using TreeNode = SubstitutedIntrusiveRedBlackTreeNode<K, V, Container>;

    Container find(K key);

    Container find_largest_not_above(K key);

    Container find_smallest_not_below(K key);

    void insert(K key, V& value);

    template<typename ElementType>
    class BaseIterator {
    public:
        BaseIterator() = default;
        bool operator!=(BaseIterator const& other) const { return m_node != other.m_node; }
        BaseIterator& operator++();
        BaseIterator& operator--();
        ElementType& operator*();
        auto operator->();
        bool is_end() const { return !m_node; }
        bool is_begin() const { return !m_prev; }
        auto key() const { return m_node->key; }

    private:
        friend class IntrusiveRedBlackTree;
        explicit BaseIterator(TreeNode* node, TreeNode* prev = nullptr)
            : m_node(node)
            , m_prev(prev)
        {
        }
        TreeNode* m_node { nullptr };
        TreeNode* m_prev { nullptr };
    };

    using Iterator = BaseIterator<V>;
    Iterator begin() { return Iterator(static_cast<TreeNode*>(this->m_minimum)); }
    Iterator end() { return {}; }
    Iterator begin_from(K key) { return Iterator(static_cast<TreeNode*>(BaseTree::find(this->m_root, key))); }
    Iterator begin_from(V& value) { return Iterator(&(value.*member)); }

    using ConstIterator = BaseIterator<const V>;
    ConstIterator begin() const { return ConstIterator(static_cast<TreeNode*>(this->m_minimum)); }
    ConstIterator end() const { return {}; }
    ConstIterator begin_from(K key) const { return ConstIterator(static_cast<TreeNode*>(BaseTree::find(this->m_rootF, key))); }
    ConstIterator begin_from(V const& value) const { return Iterator(&(value.*member)); }

    bool remove(K key);

    void clear();

private:
    static void clear_nodes(TreeNode* node);

    static V* node_to_value(TreeNode& node);
};

template<Integral K, typename V, typename Container>
class IntrusiveRedBlackTreeNode : public BaseRedBlackTree<K>::Node {
public:
    ~IntrusiveRedBlackTreeNode();

    bool is_in_tree() const;

    K key() const;

    static constexpr bool IsRaw = IsPointer<Container>;

    bool m_in_tree { false };
    SelfReferenceIfNeeded<Container, IsRaw> m_self;
};

// Specialise IntrusiveRedBlackTree for NonnullRefPtr
// By default, red black trees cannot contain null entries anyway, so switch to RefPtr
// and just make the user-facing functions deref the pointers.
template<Integral K, typename V, SubstitutedIntrusiveRedBlackTreeNode<K, V, NonnullRefPtr<V>> V::*member>
class IntrusiveRedBlackTree<K, V, NonnullRefPtr<V>, member> : public IntrusiveRedBlackTree<K, V, RefPtr<V>, member> {
public:
    NonnullRefPtr<V> find(K key) const { return IntrusiveRedBlackTree<K, V, RefPtr<V>, member>::find(key).release_nonnull(); }
    NonnullRefPtr<V> find_largest_not_above(K key) const { return IntrusiveRedBlackTree<K, V, RefPtr<V>, member>::find_largest_not_above(key).release_nonnull(); }
    NonnullRefPtr<V> find_smallest_not_below(K key) const { return IntrusiveRedBlackTree<K, V, RefPtr<V>, member>::find_smallest_not_below(key).release_nonnull(); }
};

}

namespace AK {

template<Integral K, typename V, typename Container = RawPtr<K>>
using IntrusiveRedBlackTreeNode = Detail::SubstitutedIntrusiveRedBlackTreeNode<K, V, Container>;

template<auto member>
using IntrusiveRedBlackTree = Detail::IntrusiveRedBlackTree<
    decltype(Detail::ExtractIntrusiveRedBlackTreeTypes::key(member)),
    decltype(Detail::ExtractIntrusiveRedBlackTreeTypes::value(member)),
    decltype(Detail::ExtractIntrusiveRedBlackTreeTypes::container(member)),
    member>;

}

using AK::IntrusiveRedBlackTree;
using AK::IntrusiveRedBlackTreeNode;
