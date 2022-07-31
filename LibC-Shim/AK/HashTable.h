/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Concepts.h"
#include "Error.h"
#include "Forward.h"
#include "HashFunctions.h"
#include "StdLibExtras.h"
#include "Traits.h"
#include "Types.h"

namespace AK {

enum class HashSetResult {
    InsertedNewEntry,
    ReplacedExistingEntry,
    KeptExistingEntry
};

enum class HashSetExistingEntryBehavior {
    Keep,
    Replace
};

// Upper nibble determines state class:
// - 0: unused bucket
// - 1: used bucket
// - F: end bucket
// Lower nibble determines state within a class.
enum class BucketState : u8 {
    Free = 0x00,
    Used = 0x10,
    Deleted = 0x01,
    Rehashed = 0x12,
    End = 0xFF,
};

// Note that because there's the end state, used and free are not 100% opposites!
constexpr bool is_used_bucket(BucketState state)
{
    return (static_cast<u8>(state) & 0xf0) == 0x10;
}

constexpr bool is_free_bucket(BucketState state)
{
    return (static_cast<u8>(state) & 0xf0) == 0x00;
}

template<typename HashTableType, typename T, typename BucketType>
class HashTableIterator {
    friend HashTableType;

public:
    bool operator==(HashTableIterator const& other) const { return m_bucket == other.m_bucket; }
    bool operator!=(HashTableIterator const& other) const { return m_bucket != other.m_bucket; }
    T& operator*() { return *m_bucket->slot(); }
    T* operator->() { return m_bucket->slot(); }
    void operator++() { skip_to_next(); }

private:
    void skip_to_next()
    {
        if (!m_bucket)
            return;
        do {
            ++m_bucket;
            if (m_bucket->state == BucketState::Used)
                return;
        } while (m_bucket->state != BucketState::End);
        if (m_bucket->state == BucketState::End)
            m_bucket = nullptr;
    }

    explicit HashTableIterator(BucketType* bucket)
        : m_bucket(bucket)
    {
    }

    BucketType* m_bucket{ nullptr };
};

template<typename OrderedHashTableType, typename T, typename BucketType>
class OrderedHashTableIterator {
    friend OrderedHashTableType;

public:
    bool operator==(OrderedHashTableIterator const& other) const { return m_bucket == other.m_bucket; }
    bool operator!=(OrderedHashTableIterator const& other) const { return m_bucket != other.m_bucket; }
    T& operator*() { return *m_bucket->slot(); }
    T* operator->() { return m_bucket->slot(); }
    void operator++() { m_bucket = m_bucket->next; }
    void operator--() { m_bucket = m_bucket->previous; }

private:
    explicit OrderedHashTableIterator(BucketType* bucket)
        : m_bucket(bucket)
    {
    }

    BucketType* m_bucket{ nullptr };
};

template<typename T, typename TraitsForT, bool IsOrdered>
class HashTable {
    static constexpr size_t load_factor_in_percent = 60;

    struct Bucket {
        BucketState state;
        alignas(T) u8 storage[sizeof(T)];

        T* slot() { return reinterpret_cast<T*>(storage); }
        const T* slot() const { return reinterpret_cast<const T*>(storage); }
    };

    struct OrderedBucket {
        OrderedBucket* previous;
        OrderedBucket* next;
        BucketState state;
        alignas(T) u8 storage[sizeof(T)];
        T* slot() { return reinterpret_cast<T*>(storage); }
        const T* slot() const { return reinterpret_cast<const T*>(storage); }
    };

    using BucketType = Conditional<IsOrdered, OrderedBucket, Bucket>;

    struct CollectionData {
    };

    struct OrderedCollectionData {
        BucketType* head{ nullptr };
        BucketType* tail{ nullptr };
    };

    using CollectionDataType = Conditional<IsOrdered, OrderedCollectionData, CollectionData>;

public:
    HashTable() = default;
    explicit HashTable(size_t capacity);

    ~HashTable() = default;

    HashTable(HashTable const& other);

    HashTable& operator=(HashTable const& other);

    HashTable(HashTable&& other) noexcept
        : m_buckets(other.m_buckets)
        , m_collection_data(other.m_collection_data)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_deleted_count(other.m_deleted_count)
    {
    }

    HashTable& operator=(HashTable&& other) noexcept;

    friend void swap(HashTable& a, HashTable& b) noexcept;

    bool is_empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

    template<typename U, size_t N>
    ErrorOr<void> try_set_from(U(&from_array)[N]);
    template<typename U, size_t N>
    void set_from(U(&from_array)[N]);

    void ensure_capacity(size_t capacity);

    ErrorOr<void> try_ensure_capacity(size_t capacity);

    bool contains(T const& value) const;

    template<Concepts::HashCompatible<T> K>
    requires(IsSame<TraitsForT, Traits<T>>) bool contains(K const& value) const;

    using Iterator = Conditional<IsOrdered,
        OrderedHashTableIterator<HashTable, T, BucketType>,
        HashTableIterator<HashTable, T, BucketType>>;

    Iterator begin();

    Iterator end();

    using ConstIterator = Conditional<IsOrdered,
        OrderedHashTableIterator<const HashTable, const T, const BucketType>,
        HashTableIterator<const HashTable, const T, const BucketType>>;

    ConstIterator begin() const;

    ConstIterator end() const;

    void clear();
    void clear_with_capacity();

    template<typename U = T>
    ErrorOr<HashSetResult> try_set(U&& value, HashSetExistingEntryBehavior existing_entry_behavior = HashSetExistingEntryBehavior::Replace);
    template<typename U = T>
    HashSetResult set(U&& value, HashSetExistingEntryBehavior existing_entry_behaviour = HashSetExistingEntryBehavior::Replace);

    template<typename TUnaryPredicate>
    Iterator find(unsigned hash, TUnaryPredicate predicate);

    Iterator find(T const& value);

    template<typename TUnaryPredicate>
    ConstIterator find(unsigned hash, TUnaryPredicate predicate) const;

    ConstIterator find(T const& value) const;

    template<Concepts::HashCompatible<T> K>
    requires(IsSame<TraitsForT, Traits<T>>) Iterator find(K const& value);

    template<Concepts::HashCompatible<T> K, typename TUnaryPredicate>
    requires(IsSame<TraitsForT, Traits<T>>) Iterator find(K const& value, TUnaryPredicate predicate);

    template<Concepts::HashCompatible<T> K>
    requires(IsSame<TraitsForT, Traits<T>>) ConstIterator find(K const& value) const;

    template<Concepts::HashCompatible<T> K, typename TUnaryPredicate>
    requires(IsSame<TraitsForT, Traits<T>>) ConstIterator find(K const& value, TUnaryPredicate predicate) const;

    bool remove(const T& value);

    template<Concepts::HashCompatible<T> K>
    requires(IsSame<TraitsForT, Traits<T>>) bool remove(K const& value);

    void remove(Iterator iterator);

    template<typename TUnaryPredicate>
    bool remove_all_matching(TUnaryPredicate const& predicate);

private:
    void insert_during_rehash(T&& value);

    static constexpr size_t size_in_bytes(size_t capacity);

    ErrorOr<void> try_rehash(size_t new_capacity);
    void rehash(size_t new_capacity);

    void rehash_in_place();

    void rehash_in_place_if_needed();

    template<typename TUnaryPredicate>
    BucketType* lookup_with_hash(unsigned hash, TUnaryPredicate predicate) const;

    ErrorOr<BucketType*> try_lookup_for_writing(T const& value);
    BucketType& lookup_for_writing(T const& value);

    size_t used_bucket_count() const;
    bool should_grow() const;

    void delete_bucket(auto& bucket);

    BucketType* m_buckets{ nullptr };

    CollectionDataType m_collection_data;
    size_t m_size{ 0 };
    size_t m_capacity{ 0 };
    size_t m_deleted_count{ 0 };
};
}

using AK::HashTable;
using AK::OrderedHashTable;
