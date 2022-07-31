/*
 * Copyright (c) 2020-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Assertions.h"
#include "Platform.h"
#include "StdLibExtras.h"

namespace AK {

template<typename OutputType, typename InputType>
ALWAYS_INLINE bool is(InputType& input);

template<typename OutputType, typename InputType>
ALWAYS_INLINE bool is(InputType* input);

template<typename OutputType, typename InputType>
ALWAYS_INLINE CopyConst<InputType, OutputType>* verify_cast(InputType* input);

template<typename OutputType, typename InputType>
ALWAYS_INLINE CopyConst<InputType, OutputType>& verify_cast(InputType& input);

}

using AK::is;
using AK::verify_cast;
