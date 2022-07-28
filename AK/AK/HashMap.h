#pragma once

#include "./AK/HashTable.h"
#include "./AK/Optional.h"
#include "./AK/Vector.h"
#include <initializer_list>

namespace AK {

template<typename K, typename V, typename KeyTraits, bool IsOrdered>
class HashMap {
public:
    using KeyType = K;
    using ValueType = V;

    HashMap() = default;

    bool is_empty() const { return true; }
    size_t size() const { return 0; }
    size_t capacity() const { return 0; }
    void clear();
    void clear_with_capacity();

    HashSetResult set(const K& key, const V& value);
    HashSetResult set(const K& key, V&& value);
    HashSetResult set(K&& key, V&& value);

    int* begin() const { return 0; }
    int* end() const { return 0; }
    int* find(const K& key)

    u32 hash() const;
};

}

using AK::HashMap;
using AK::OrderedHashMap;