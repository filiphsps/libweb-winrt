/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <list>
#include "./AK/Assertions.h"
#include "./AK/BitCast.h"
#include "./AK/Forward.h"
#include "./AK/IntrusiveDetails.h"
#include "./AK/Noncopyable.h"
#include "./AK/StdLibExtras.h"

namespace AK {

template<typename T>
class IntrusiveListNode;

namespace Detail {

template<typename V, typename T>
static V ExtractIntrusiveListType(IntrusiveListNode<V> T::* x);

template<class T>
class IntrusiveListImpl {
public:
    void append(T&);

    T* last();

    bool is_empty();
};

}

template<typename T>
class IntrusiveListNode {
public:
    void remove();
};

template<auto member>
using IntrusiveList = Detail::IntrusiveListImpl<decltype(Detail::ExtractIntrusiveListType(member))>;

}

using AK::IntrusiveList;
using AK::IntrusiveListNode;
