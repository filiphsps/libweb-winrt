/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Error.h"
#include "./AK/NonnullOwnPtr.h"
#include "./AK/RefCounted.h"

#define OWNPTR_SCRUB_BYTE 0xf0

namespace AK {

template<typename T>
class OwnPtr {
public:
    OwnPtr() = default;

    OwnPtr(decltype(nullptr))
        : m_ptr(nullptr)
    {
    }

    OwnPtr(OwnPtr&& other)
        : m_ptr(other.leak_ptr())
    {
    }

    template<typename U>
    OwnPtr(NonnullOwnPtr<U>&& other)
        : m_ptr(other.leak_ptr())
    {
    }
    template<typename U>
    OwnPtr(OwnPtr<U>&& other)
        : m_ptr(other.leak_ptr())
    {
    }
    ~OwnPtr()
    {
        clear();
    }

    OwnPtr(OwnPtr const&) = delete;
    template<typename U>
    OwnPtr(OwnPtr<U> const&) = delete;
    OwnPtr& operator=(OwnPtr const&) = delete;
    template<typename U>
    OwnPtr& operator=(OwnPtr<U> const&) = delete;

    template<typename U>
    OwnPtr(NonnullOwnPtr<U> const&) = delete;
    template<typename U>
    OwnPtr& operator=(NonnullOwnPtr<U> const&) = delete;
    template<typename U>
    OwnPtr(RefPtr<U> const&) = delete;
    template<typename U>
    OwnPtr(NonnullRefPtr<U> const&) = delete;
    template<typename U>
    OwnPtr(WeakPtr<U> const&) = delete;
    template<typename U>
    OwnPtr& operator=(RefPtr<U> const&) = delete;
    template<typename U>
    OwnPtr& operator=(NonnullRefPtr<U> const&) = delete;
    template<typename U>
    OwnPtr& operator=(WeakPtr<U> const&) = delete;

    OwnPtr& operator=(OwnPtr&& other);

    template<typename U>
    OwnPtr& operator=(OwnPtr<U>&& other);

    template<typename U>
    OwnPtr& operator=(NonnullOwnPtr<U>&& other);
    OwnPtr& operator=(T* ptr) = delete;
    OwnPtr& operator=(std::nullptr_t);

    bool operator!() const { return !m_ptr; }
    operator T* () { return m_ptr; }
    operator bool() { return !!m_ptr; }
private:
    T* m_ptr = nullptr;
};

}

using AK::OwnPtr;
