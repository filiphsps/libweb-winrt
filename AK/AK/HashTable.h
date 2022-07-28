/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Concepts.h"
#include "./AK/Error.h"
#include "./AK/Forward.h"
#include "./AK/HashFunctions.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Traits.h"
#include "./AK/Types.h"

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

template<typename T, typename TraitsForT, bool IsOrdered>
class HashTable {
public:
    HashTable() = default;
    explicit HashTable(size_t capacity);

    ~HashTable();

    HashTable(HashTable const& other);

    HashTable& operator=(HashTable const& other);

    friend void swap(HashTable& a, HashTable& b) noexcept;

    bool is_empty() const { return true; }
    size_t size() const { return 0; }
    size_t capacity() const { return 0; }

    template<typename U, size_t N>
    ErrorOr<void> try_set_from(U(&from_array)[N]);
    template<typename U, size_t N>
    void set_from(U(&from_array)[N]);

    template<typename TUnaryPredicate>
    bool remove_all_matching(TUnaryPredicate const& predicate);

private:
};

}

using AK::HashTable;
using AK::OrderedHashTable;