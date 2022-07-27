/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Weakable.h"

namespace AK {

template<typename T>
class WeakPtr {
    WeakPtr() = default;
};

template<typename T>
template<typename U>
inline ErrorOr<WeakPtr<U>> Weakable<T>::try_make_weak_ptr() const
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
