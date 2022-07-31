/*
 * Copyright (c) 2020-2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Array.h"
#include "./AK/Assertions.h"
#include "./AK/Span.h"
#include "./AK/Types.h"
#include "./AK/Vector.h"

namespace AK {

namespace Detail {

constexpr void const* bitap_bitwise(void const* haystack, size_t haystack_length, void const* needle, size_t needle_length);

}

template<typename HaystackIterT>
ALWAYS_INLINE Optional<size_t> memmem(HaystackIterT const& haystack_begin, HaystackIterT const& haystack_end, Span<const u8> needle) requires(requires { (*haystack_begin).data(); (*haystack_begin).size(); });

ALWAYS_INLINE Optional<size_t> memmem_optional(void const* haystack, size_t haystack_length, void const* needle, size_t needle_length);

ALWAYS_INLINE void const* memmem(void const* haystack, size_t haystack_length, void const* needle, size_t needle_length);

}

