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

    operator bool() { return !!m_ptr; }
private:
    T* m_ptr = nullptr;

};

}

using AK::OwnPtr;
