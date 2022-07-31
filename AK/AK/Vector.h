/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Error.h"
#include "./AK/Find.h"
#include "./AK/Forward.h"
#include "./AK/Iterator.h"
#include "./AK/Optional.h"
#include "./AK/ReverseIterator.h"
#include "./AK/Span.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Traits.h"
#include "./AK/TypedTransfer.h"
#include "./AK/kmalloc.h"
#include <initializer_list>

namespace AK {

namespace Detail {

template<typename StorageType, bool>
struct CanBePlacedInsideVectorHelper;

template<typename StorageType>
struct CanBePlacedInsideVectorHelper<StorageType, true> {
    template<typename U>
    static constexpr bool value = requires(U && u) { StorageType{ &u }; };
};

template<typename StorageType>
struct CanBePlacedInsideVectorHelper<StorageType, false> {
    template<typename U>
    static constexpr bool value = requires(U && u) { StorageType(forward<U>(u)); };
};

}

template<typename T, size_t inline_capacity>
requires(!IsRvalueReference<T>) class Vector {
    private:
        static constexpr bool contains_reference = IsLvalueReference<T>;
        using StorageType = Conditional<contains_reference, RawPtr<RemoveReference<T>>, T>;

        using VisibleType = RemoveReference<T>;

        template<typename U>
        static constexpr bool CanBePlacedInsideVector = Detail::CanBePlacedInsideVectorHelper<StorageType, contains_reference>::template value<U>;

    public:
        using ValueType = T;
        Vector()
            : m_capacity(inline_capacity)
        {
        }

        Vector(std::initializer_list<T> list) requires(!IsLvalueReference<T>);

        Vector(Vector&& other)
            : m_size(other.m_size)
            , m_capacity(other.m_capacity)
            , m_outline_buffer(other.m_outline_buffer)
        {
        }

        Vector(Vector const& other);

        explicit Vector(Span<T const> other) requires(!IsLvalueReference<T>);

        template<size_t other_inline_capacity>
        Vector(Vector<T, other_inline_capacity> const& other);

        ~Vector()
        {
            clear();
        }

        Span<StorageType> span() { return { data(), size() }; }
        Span<StorageType const> span() const { return { data(), size() }; }

        operator Span<StorageType>() { return span(); }
        operator Span<StorageType const>() const { return span(); }

        bool is_empty() const { return size() == 0; }
        ALWAYS_INLINE size_t size() const { return m_size; }
        size_t capacity() const { return m_capacity; }

        ALWAYS_INLINE StorageType* data();

        ALWAYS_INLINE StorageType const* data() const;

        ALWAYS_INLINE VisibleType const& at(size_t i) const;

        ALWAYS_INLINE VisibleType& at(size_t i);

        ALWAYS_INLINE VisibleType const& operator[](size_t i) const { return at(i); }
        ALWAYS_INLINE VisibleType& operator[](size_t i) { return at(i); }

        VisibleType const& first() const { return at(0); }
        VisibleType& first() { return at(0); }

        VisibleType const& last() const { return at(size() - 1); }
        VisibleType& last() { return at(size() - 1); }

        template<typename TUnaryPredicate>
        Optional<VisibleType&> first_matching(TUnaryPredicate const& predicate) requires(!contains_reference);

        template<typename TUnaryPredicate>
        Optional<VisibleType const&> first_matching(TUnaryPredicate const& predicate) const requires(!contains_reference);

        template<typename TUnaryPredicate>
        Optional<VisibleType&> last_matching(TUnaryPredicate const& predicate) requires(!contains_reference);

        template<typename V>
        bool operator==(V const& other) const;

        template<typename V>
        bool contains_slow(V const& value) const;

        bool contains_in_range(VisibleType const& value, size_t const start, size_t const end) const;

        template<typename U = T>
        void insert(size_t index, U&& value) requires(CanBePlacedInsideVector<U>);

        template<typename TUnaryPredicate, typename U = T>
        void insert_before_matching(U&& value, TUnaryPredicate const& predicate, size_t first_index = 0, size_t* inserted_index = nullptr) requires(CanBePlacedInsideVector<U>);

        void extend(Vector&& other);

        void extend(Vector const& other);

        ALWAYS_INLINE void append(T&& value);

        ALWAYS_INLINE void append(T const& value) requires(!contains_reference);

        void append(StorageType const* values, size_t count);

        template<typename U = T>
        ALWAYS_INLINE void unchecked_append(U&& value) requires(CanBePlacedInsideVector<U>);

        ALWAYS_INLINE void unchecked_append(StorageType const* values, size_t count);

        template<class... Args>
        void empend(Args&&... args)/* requires(!contains_reference)*/;

        template<typename U = T>
        void prepend(U&& value)/* requires(CanBePlacedInsideVector<U>)*/;

        void prepend(Vector&& other);

        void prepend(StorageType const* values, size_t count);

        Vector& operator=(Vector&& other);

        Vector& operator=(Vector const& other);

        template<size_t other_inline_capacity>
        Vector& operator=(Vector<T, other_inline_capacity> const& other);

        void clear();

        void clear_with_capacity();

        void remove(size_t index);

        void remove(size_t index, size_t count);

        template<typename TUnaryPredicate>
        bool remove_first_matching(TUnaryPredicate const& predicate);

        template<typename TUnaryPredicate>
        bool remove_all_matching(TUnaryPredicate const& predicate);

        ALWAYS_INLINE T take_last();

        T take_first();

        T take(size_t index);

        T unstable_take(size_t index);

        template<typename U = T>
        ErrorOr<void> try_insert(size_t index, U&& value) requires(CanBePlacedInsideVector<U>);

        template<typename TUnaryPredicate, typename U = T>
        ErrorOr<void> try_insert_before_matching(U&& value, TUnaryPredicate const& predicate, size_t first_index = 0, size_t* inserted_index = nullptr) requires(CanBePlacedInsideVector<U>);

        ErrorOr<void> try_extend(Vector&& other);

        ErrorOr<void> try_extend(Vector const& other);

        ErrorOr<void> try_append(T&& value);

        ErrorOr<void> try_append(T const& value) requires(!contains_reference);

        ErrorOr<void> try_append(StorageType const* values, size_t count);

        template<class... Args>
        ErrorOr<void> try_empend(Args&&... args) requires(!contains_reference);

        template<typename U = T>
        ErrorOr<void> try_prepend(U&& value) requires(CanBePlacedInsideVector<U>);

        ErrorOr<void> try_prepend(Vector&& other);

        ErrorOr<void> try_prepend(StorageType const* values, size_t count);

        ErrorOr<void> try_grow_capacity(size_t needed_capacity);

        ErrorOr<void> try_ensure_capacity(size_t needed_capacity);

        ErrorOr<void> try_resize(size_t new_size, bool keep_capacity = false) requires(!contains_reference);

        ErrorOr<void> try_resize_and_keep_capacity(size_t new_size) requires(!contains_reference);

        void grow_capacity(size_t needed_capacity);

        void ensure_capacity(size_t needed_capacity);

        void shrink(size_t new_size, bool keep_capacity = false);

        void resize(size_t new_size, bool keep_capacity = false) requires(!contains_reference);

        void resize_and_keep_capacity(size_t new_size) requires(!contains_reference);

        using ConstIterator = SimpleIterator<Vector const, VisibleType const>;
        using Iterator = SimpleIterator<Vector, VisibleType>;
        using ReverseIterator = SimpleReverseIterator<Vector, VisibleType>;
        using ReverseConstIterator = SimpleReverseIterator<Vector const, VisibleType const>;

        ConstIterator begin() const { return ConstIterator::begin(*this); }
        Iterator begin() { return Iterator::begin(*this); }
        ReverseIterator rbegin() { return ReverseIterator::rbegin(*this); }
        ReverseConstIterator rbegin() const { return ReverseConstIterator::rbegin(*this); }

        ConstIterator end() const { return ConstIterator::end(*this); }
        Iterator end() { return Iterator::end(*this); }
        ReverseIterator rend() { return ReverseIterator::rend(*this); }
        ReverseConstIterator rend() const { return ReverseConstIterator::rend(*this); }

        ALWAYS_INLINE constexpr auto in_reverse()
        {
            return ReverseWrapper::in_reverse(*this);
        }

        template<typename TUnaryPredicate>
        ConstIterator find_if(TUnaryPredicate&& finder) const;

        template<typename TUnaryPredicate>
        Iterator find_if(TUnaryPredicate&& finder);

        ConstIterator find(VisibleType const& value) const;

        Iterator find(VisibleType const& value);

        Optional<size_t> find_first_index(VisibleType const& value) const;

        void reverse();

    private:
        void reset_capacity();

        static size_t padded_capacity(size_t capacity);

        StorageType* slot(size_t i) { return &data()[i]; }
        StorageType const* slot(size_t i) const { return &data()[i]; }

        StorageType* inline_buffer();
        StorageType const* inline_buffer() const;

        StorageType& raw_last() { return raw_at(size() - 1); }
        StorageType& raw_first() { return raw_at(0); }
        StorageType& raw_at(size_t index) { return *slot(index); }

        size_t m_size{ 0 };
        size_t m_capacity{ 0 };

        static constexpr size_t storage_size();

        static constexpr size_t storage_alignment();

        //alignas(storage_alignment()) unsigned char m_inline_buffer_storage[storage_size()];
        StorageType* m_outline_buffer{ nullptr };
};

template<class... Args>
Vector(Args... args)->Vector<CommonType<Args...>>;

}

using AK::Vector;
