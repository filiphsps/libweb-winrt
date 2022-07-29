#pragma once

#include "./AK/HashMap.h"
#include "./AK/JsonArray.h"
#include "./AK/JsonObjectSerializer.h"
#include "./AK/JsonValue.h"
#include "./AK/String.h"


namespace AK {

class JsonObject {
public:
    JsonObject() = default;
    ~JsonObject() = default;

    JsonObject(JsonObject const& other)
        : m_members(other.m_members)
    {
    }

    JsonObject(JsonObject&& other)
        : m_members(move(other.m_members))
    {
    }

    JsonObject& operator=(JsonObject const& other);

    JsonObject& operator=(JsonObject&& other);

    size_t size() const;
    bool is_empty() const;

    JsonValue const& get(StringView key) const;

    JsonValue const* get_ptr(StringView key) const;

    bool has(StringView key) const;

    bool has_null(StringView key) const;
    bool has_bool(StringView key) const;
    bool has_string(StringView key) const;
    bool has_i32(StringView key) const;
    bool has_u32(StringView key) const;
    bool has_i64(StringView key) const;
    bool has_u64(StringView key) const;
    bool has_number(StringView key) const;
    bool has_array(StringView key) const;
    bool has_object(StringView key) const;
    bool has_double(StringView key) const;

    void set(String const& key, JsonValue value);

    template<typename Callback>
    void for_each_member(Callback callback) const;

    bool remove(StringView key);

    template<typename Builder>
    typename Builder::OutputType serialized() const;

    template<typename Builder>
    void serialize(Builder&) const;

    String to_string() const { return serialized<StringBuilder>(); }

private:
    OrderedHashMap<String, JsonValue> m_members;
};

template<typename Builder>
inline void JsonObject::serialize(Builder& builder) const;

template<typename Builder>
inline typename Builder::OutputType JsonObject::serialized() const;

template<typename Builder>
inline void JsonValue::serialize(Builder& builder) const;

template<typename Builder>
inline typename Builder::OutputType JsonValue::serialized() const;

}

using AK::JsonObject;
