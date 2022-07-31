/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "NonnullPtrVector.h"
#include "NonnullRefPtr.h"

namespace AK {

template<typename T, size_t inline_capacity>
class NonnullRefPtrVector : public NonnullPtrVector<NonnullRefPtr<T>, inline_capacity> {
    using NonnullPtrVector<NonnullRefPtr<T>, inline_capacity>::NonnullPtrVector;
};

}

using AK::NonnullRefPtrVector;
