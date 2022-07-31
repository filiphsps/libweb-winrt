/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Weakable.h"

namespace AK {

template<typename T>
class WeakPtr {
    template<typename U>
    friend class Weakable;

public:
    WeakPtr() = default;

    template<typename U>
    WeakPtr(WeakPtr<U> const& other)/* requires(IsBaseOf<T, U>)*/
        : m_link(other.m_link)
    {
    }

    template<typename U>
    WeakPtr(WeakPtr<U>&& other)/* requires(IsBaseOf<T, U>)*/
        : m_link(other.take_link())
    {
    }

    template<typename U>
    WeakPtr& operator=(WeakPtr<U>&& other)/* requires(IsBaseOf<T, U>)*/
    {
        m_link = other.take_link();
        return *this;
    }

    template<typename U>
    WeakPtr& operator=(WeakPtr<U> const& other)/* requires(IsBaseOf<T, U>)*/;

    WeakPtr& operator=(std::nullptr_t);

    template<typename U>
    WeakPtr(const U& object)/* requires(IsBaseOf<T, U>)*/
    {
    }

    template<typename U>
    WeakPtr(const U* object)/* requires(IsBaseOf<T, U>)*/;

    template<typename U>
    WeakPtr(RefPtr<U> const& object)/* requires(IsBaseOf<T, U>)*/;

    template<typename U>
    WeakPtr(NonnullRefPtr<U> const& object)/* requires(IsBaseOf<T, U>)*/;
    template<typename U>
    WeakPtr& operator=(const U& object)/* requires(IsBaseOf<T, U>)*/;

    template<typename U>
    WeakPtr& operator=(const U* object)/* requires(IsBaseOf<T, U>)*/;

    template<typename U>
    WeakPtr& operator=(RefPtr<U> const& object)/* requires(IsBaseOf<T, U>)*/;

    template<typename U>
    WeakPtr& operator=(NonnullRefPtr<U> const& object)/* requires(IsBaseOf<T, U>)*/;

    [[nodiscard]] RefPtr<T> strong_ref() const
    {
        return RefPtr<T> { ptr() };
    }

    T* ptr() const { return unsafe_ptr(); }
    T* operator->() { return unsafe_ptr(); }
    const T* operator->() const { return unsafe_ptr(); }
    operator const T* () const { return unsafe_ptr(); }
    operator T* () { return unsafe_ptr(); }

    [[nodiscard]] T* unsafe_ptr() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return nullptr;
    }

    operator bool() const { return m_link ? !m_link->is_null() : false; }

    bool is_null() const { return !m_link || m_link->is_null(); }
    void clear() { m_link = nullptr; }

    RefPtr<WeakLink> take_link() { return move(m_link); }

private:
    WeakPtr(RefPtr<WeakLink> const& link)
        : m_link(link)
    {
    }

    RefPtr<WeakLink> m_link;
};

template<typename T>
template<typename U>
ALWAYS_INLINE ErrorOr<WeakPtr<U>> Weakable<T>::try_make_weak_ptr() const
{
    if (!m_link)
        m_link = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) WeakLink(const_cast<T&>(static_cast<T const&>(*this)))));

    return WeakPtr<U>(m_link);
}

template<typename T>
struct Formatter<WeakPtr<T>> : Formatter<const T*> {
    ErrorOr<void> format(FormatBuilder& builder, WeakPtr<T> const& value)
    {
        return Formatter<const T*>::format(builder, value.ptr());
    }
};

template<typename T>
ErrorOr<WeakPtr<T>> try_make_weak_ptr_if_nonnull(T const* ptr)
{
    if (ptr) {
        return ptr->template try_make_weak_ptr<T>();
    }
    return WeakPtr<T> {};
}

template<typename T>
WeakPtr<T> make_weak_ptr_if_nonnull(T const* ptr)
{
    return MUST(try_make_weak_ptr_if_nonnull(ptr));
}

}

using AK::WeakPtr;
