/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "HashTable.h"
#include "Optional.h"
#include "Vector.h"
#include <initializer_list>

namespace AK {

template<typename K, typename V, typename KeyTraits, bool IsOrdered>
class HashMap {
private:
    struct Entry {
        K key;
        V value;
    };

    struct EntryTraits {
        static unsigned hash(Entry const& entry) { return KeyTraits::hash(entry.key); }
        static bool equals(Entry const& a, Entry const& b) { return KeyTraits::equals(a.key, b.key); }
    };

public:
    using KeyType = K;
    using ValueType = V;

    HashMap() = default;

    HashMap(std::initializer_list<Entry> list)
    {
    }

    bool is_empty() const;
    size_t size() const;
    size_t capacity() const;
    void clear();
    void clear_with_capacity();

    HashSetResult set(const K& key, const V& value) { return m_table.set({ key, value }); }
    HashSetResult set(const K& key, V&& value) { return m_table.set({ key, move(value) }); }
    HashSetResult set(K&& key, V&& value) { return m_table.set({ move(key), move(value) }); }
    ErrorOr<HashSetResult> try_set(const K& key, const V& value) { return m_table.try_set({ key, value }); }
    ErrorOr<HashSetResult> try_set(const K& key, V&& value) { return m_table.try_set({ key, move(value) }); }
    ErrorOr<HashSetResult> try_set(K&& key, V&& value) { return m_table.try_set({ move(key), move(value) }); }

    bool remove(const K& key);

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) bool remove(Key const& key);

    template<typename TUnaryPredicate>
    bool remove_all_matching(TUnaryPredicate const& predicate);

    using HashTableType = HashTable<Entry, EntryTraits, IsOrdered>;
    using IteratorType = typename HashTableType::Iterator;
    using ConstIteratorType = typename HashTableType::ConstIterator;

    IteratorType begin();
    IteratorType end();
    IteratorType find(const K& key);
    template<typename TUnaryPredicate>
    IteratorType find(unsigned hash, TUnaryPredicate predicate);

    ConstIteratorType begin() const;
    ConstIteratorType end() const;
    ConstIteratorType find(const K& key) const;
    template<typename TUnaryPredicate>
    ConstIteratorType find(unsigned hash, TUnaryPredicate predicate) const;

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) IteratorType find(Key const& key);

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) ConstIteratorType find(Key const& key) const;

    void ensure_capacity(size_t capacity);
    ErrorOr<void> try_ensure_capacity(size_t capacity);

    Optional<typename Traits<V>::ConstPeekType> get(const K& key) const requires(!IsPointer<typename Traits<V>::PeekType>);

    Optional<typename Traits<V>::ConstPeekType> get(const K& key) const requires(IsPointer<typename Traits<V>::PeekType>);

    Optional<typename Traits<V>::PeekType> get(const K& key) requires(!IsConst<typename Traits<V>::PeekType>);

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) Optional<typename Traits<V>::PeekType> get(Key const& key)
    const requires(!IsPointer<typename Traits<V>::PeekType>);

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) Optional<typename Traits<V>::ConstPeekType> get(Key const& key)
    const requires(IsPointer<typename Traits<V>::PeekType>);

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) Optional<typename Traits<V>::PeekType> get(Key const& key)
    requires(!IsConst<typename Traits<V>::PeekType>);

    bool contains(const K& key) const;

    template<Concepts::HashCompatible<K> Key>
    requires(IsSame<KeyTraits, Traits<K>>) bool contains(Key const& value);

    void remove(IteratorType it);

    V& ensure(const K& key);

    template<typename Callback>
    V& ensure(K const& key, Callback initialization_callback);

    Vector<K> keys() const;

    u32 hash() const;

private:
    HashTableType m_table;
};

}

using AK::HashMap;
using AK::OrderedHashMap;
