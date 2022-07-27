/*
 * Copyright (c) 2018-2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Atomic.h"
#include "./AK/RefCounted.h"
#include "./AK/RefPtr.h"
#include "./AK/StdLibExtras.h"

namespace AK {

template<typename T>
class Weakable;
template<typename T>
class WeakPtr;

class WeakLink : public RefCounted<WeakLink> {
    template<typename T>
    friend class Weakable;
    template<typename T>
    friend class WeakPtr;

private:
    template<typename T>
    explicit WeakLink(T&)
    {
    }
};

template<typename T>
class Weakable {
private:
    class Link;

public:
    template<typename U = T>
    ErrorOr<WeakPtr<U>> try_make_weak_ptr() const;

protected:
    Weakable() = default;

private:
    mutable RefPtr<WeakLink> m_link;
};

}

using AK::Weakable;
