/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/StdLibExtras.h"

namespace AK {

template<typename Collection, typename LessThan>
void dual_pivot_quick_sort(Collection& col, int start, int end, LessThan less_than);

template<typename Iterator, typename LessThan>
void single_pivot_quick_sort(Iterator start, Iterator end, LessThan less_than);

template<typename Iterator>
void quick_sort(Iterator start, Iterator end);

template<typename Iterator, typename LessThan>
void quick_sort(Iterator start, Iterator end, LessThan less_than);

template<typename Collection, typename LessThan>
void quick_sort(Collection& collection, LessThan less_than);

template<typename Collection>
void quick_sort(Collection& collection);

}

using AK::quick_sort;
