#pragma once
/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Daniel Bertalan <dani@danielbertalan.dev>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Types.h"


namespace AK {

// NOTE: If you're here because of an internal compiler error in GCC 10.3.0+,
//       it's because of the following bug:
//
//       https://gcc.gnu.org/bugzilla/show_bug.cgi?id=96745
//
//       Make sure you didn't accidentally make your destructor private before
//       you start bug hunting. :^)

template<typename>
class Optional;

template<typename T>
requires(!IsLvalueReference<T>) class Optional<T> {
template<typename U>
friend class Optional;

static_assert(!IsLvalueReference<T> && !IsRvalueReference<T>);

public:
    using ValueType = T;

    inline Optional() = default;

    inline Optional(Optional const& other)
    : m_has_value(other.m_has_value)
    {
        if (other.has_value())
            new (&m_storage) T(other.value());
    }

    inline Optional(Optional&& other)
        : m_has_value(other.m_has_value)
    {
        if (other.has_value())
            new (&m_storage) T(other.release_value());
    }

    template<typename U>
        requires(IsConstructible<T, U const&> && !IsSpecializationOf<T, Optional> && !IsSpecializationOf<U, Optional>) inline explicit Optional(Optional<U> const& other)
    : m_has_value(other.m_has_value)
    {
        if (other.has_value())
            new (&m_storage) T(other.value());
    }

    template<typename U>
        requires(IsConstructible<T, U&&> && !IsSpecializationOf<T, Optional> && !IsSpecializationOf<U, Optional>) inline explicit Optional(Optional<U>&& other)
    : m_has_value(other.m_has_value)
    {
        if (other.has_value())
            new (&m_storage) T(other.release_value());
    }

    template<typename U = T>
    inline explicit(!IsConvertible<U&&, T>) Optional(U&& value) requires(!IsSame<RemoveCVReference<U>, Optional<T>>&& IsConstructible<T, U&&>)
        : m_has_value(true)
    {
        new (&m_storage) T(forward<U>(value));
    }

    inline Optional& operator=(Optional const& other)
    {
        if (this != &other) {
            clear();
            m_has_value = other.m_has_value;
            if (other.has_value()) {
                new (&m_storage) T(other.value());
            }
        }
        return *this;
    }

    inline Optional& operator=(Optional&& other)
    {
        if (this != &other) {
            clear();
            m_has_value = other.m_has_value;
            if (other.has_value()) {
                new (&m_storage) T(other.release_value());
            }
        }
        return *this;
    }

    template<typename O>
    inline bool operator==(Optional<O> const& other) const
    {
        return has_value() == other.has_value() && (!has_value() || value() == other.value());
    }

    template<typename O>
    inline bool operator==(O const& other) const
    {
        return has_value() && value() == other;
    }

    inline ~Optional()
    {
        clear();
    }

    inline void clear()
    {
        if (m_has_value) {
            value().~T();
            m_has_value = false;
        }
    }

    template<typename... Parameters>
    inline void emplace(Parameters&&... parameters)
    {
        clear();
        m_has_value = true;
        new (&m_storage) T(forward<Parameters>(parameters)...);
    }

    inline bool has_value() const { return m_has_value; }

    inline T& value()&
    {
        VERIFY(m_has_value);
        return *__builtin_launder(reinterpret_cast<T*>(&m_storage));
    }

    inline T const& value() const&
    {
        VERIFY(m_has_value);
        return *__builtin_launder(reinterpret_cast<T const*>(&m_storage));
    }

    inline T value()&&
    {
        return release_value();
    }

    inline T release_value()
    {
        VERIFY(m_has_value);
        T released_value = move(value());
        value().~T();
        m_has_value = false;
        return released_value;
    }

    inline T value_or(T const& fallback) const&
    {
        if (m_has_value)
            return value();
        return fallback;
    }

    inline T value_or(T&& fallback)&&
    {
        if (m_has_value)
            return move(value());
        return move(fallback);
    }

    inline T const& operator*() const { return value(); }
    inline T& operator*() { return value(); }

    inline T const* operator->() const { return &value(); }
    inline T* operator->() { return &value(); }

private:
    alignas(T) u8 m_storage[sizeof(T)];
    bool m_has_value{ false };
};

template<typename T>
requires(IsLvalueReference<T>) class Optional<T> {
template<typename>
friend class Optional;

template<typename U>
constexpr static bool CanBePlacedInOptional = IsSame<RemoveReference<T>, RemoveReference<AddConstToReferencedType<U>>> && (IsBaseOf<RemoveCVReference<T>, RemoveCVReference<U>> || IsSame<RemoveCVReference<T>, RemoveCVReference<U>>);

public:
    using ValueType = T;

    inline Optional() = default;

    template<typename U = T>
    inline Optional(U& value) requires(CanBePlacedInOptional<U&>)
        : m_pointer(&value)
    {
    }

    inline Optional(RemoveReference<T>& value)
        : m_pointer(&value)
    {
    }

    inline Optional(Optional const& other)
        : m_pointer(other.m_pointer)
    {
    }

    inline Optional(Optional&& other)
        : m_pointer(other.m_pointer)
    {
        other.m_pointer = nullptr;
    }

    template<typename U>
    inline Optional(Optional<U> const& other) requires(CanBePlacedInOptional<U>)
        : m_pointer(other.m_pointer)
    {
    }

    template<typename U>
    inline Optional(Optional<U>&& other) requires(CanBePlacedInOptional<U>)
        : m_pointer(other.m_pointer)
    {
        other.m_pointer = nullptr;
    }

    inline Optional& operator=(Optional const& other)
    {
        m_pointer = other.m_pointer;
        return *this;
    }

    inline Optional& operator=(Optional&& other)
    {
        m_pointer = other.m_pointer;
        other.m_pointer = nullptr;
        return *this;
    }

    template<typename U>
    inline Optional& operator=(Optional<U> const& other) requires(CanBePlacedInOptional<U>)
    {
        m_pointer = other.m_pointer;
        return *this;
    }

    template<typename U>
    inline Optional& operator=(Optional<U>&& other) requires(CanBePlacedInOptional<U>)
    {
        m_pointer = other.m_pointer;
        other.m_pointer = nullptr;
        return *this;
    }

    // Note: Disallows assignment from a temporary as this does not do any lifetime extension.
    template<typename U>
    inline Optional& operator=(U&& value) requires(CanBePlacedInOptional<U>&& IsLvalueReference<U>)
    {
        m_pointer = &value;
        return *this;
    }

    inline void clear()
    {
        m_pointer = nullptr;
    }

    inline bool has_value() const { return m_pointer != nullptr; }

    inline T value()
    {
        VERIFY(m_pointer);
        return *m_pointer;
    }

    inline AddConstToReferencedType<T> value() const
    {
        VERIFY(m_pointer);
        return *m_pointer;
    }

    template<typename U>
        requires(IsBaseOf<RemoveCVReference<T>, U>) inline AddConstToReferencedType<T> value_or(U& fallback) const
    {
        if (m_pointer)
            return value();
        return fallback;
    }

    // Note that this ends up copying the value.
    inline RemoveCVReference<T> value_or(RemoveCVReference<T> fallback) const
    {
        if (m_pointer)
            return value();
        return fallback;
    }

    inline T release_value()
    {
        return *exchange(m_pointer, nullptr);
    }

    template<typename U>
    inline bool operator==(Optional<U> const& other) const
    {
        return has_value() == other.has_value() && (!has_value() || value() == other.value());
    }

    template<typename U>
    inline bool operator==(U const& other) const
    {
        return has_value() && value() == other;
    }

    inline AddConstToReferencedType<T> operator*() const { return value(); }
    inline T operator*() { return value(); }

    inline RawPtr<AddConst<RemoveReference<T>>> operator->() const { return &value(); }
    inline RawPtr<RemoveReference<T>> operator->() { return &value(); }

    // Conversion operators from Optional<T&> -> Optional<T>
    inline operator Optional<RemoveCVReference<T>>() const
    {
        if (has_value())
            return Optional<RemoveCVReference<T>>(value());
        return {};
    }

private:
    RemoveReference<T>* m_pointer{ nullptr };
};

}

using AK::Optional;
