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
inline ErrorOr<WeakPtr<U>> Weakable<T>::try_make_weak_ptr() const;

template<typename T>
struct Formatter<WeakPtr<T>> : Formatter<const T*> {
    ErrorOr<void> format(FormatBuilder& builder, WeakPtr<T> const& value);
};

template<typename T>
ErrorOr<WeakPtr<T>> try_make_weak_ptr_if_nonnull(T const* ptr);

template<typename T>
WeakPtr<T> make_weak_ptr_if_nonnull(T const* ptr);

}

using AK::WeakPtr;
