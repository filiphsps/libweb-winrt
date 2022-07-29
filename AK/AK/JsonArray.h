/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Concepts.h"
#include "./AK/JsonObjectSerializer.h"
#include "./AK/JsonValue.h"
#include "./AK/Vector.h"

namespace AK {

class JsonArray {
public:
    JsonArray() = default;
    ~JsonArray() = default;

    JsonArray(JsonArray const& other)
        : m_values(other.m_values)
    {
    }

    JsonArray(JsonArray&& other)
        : m_values(move(other.m_values))
    {
    }

    template<IterableContainer ContainerT>
    JsonArray(ContainerT const& source);

    JsonArray& operator=(JsonArray const& other);

    JsonArray& operator=(JsonArray&& other);

    size_t size() const;
    bool is_empty() const;

    JsonValue const& at(size_t index) const;
    JsonValue const& operator[](size_t index) const;

    void clear() { m_values.clear(); }
    void append(JsonValue value);
    void set(size_t index, JsonValue value);

    template<typename Builder>
    typename Builder::OutputType serialized() const;

    template<typename Builder>
    void serialize(Builder&) const;

    String to_string() const { return serialized<StringBuilder>(); }

    template<typename Callback>
    void for_each(Callback callback) const;

    Vector<JsonValue> const& values();

    void ensure_capacity(size_t capacity);

private:
    Vector<JsonValue> m_values;
};

template<typename Builder>
inline void JsonArray::serialize(Builder& builder) const;

template<typename Builder>
inline typename Builder::OutputType JsonArray::serialized() const;

}

using AK::JsonArray;
