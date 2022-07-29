/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, kleines Filmröllchen <malu.bertsch@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Format.h"
#include "./AK/Noncopyable.h"
#include "./AK/Types.h"

namespace Threading {

class Mutex {
    AK_MAKE_NONCOPYABLE(Mutex);
    AK_MAKE_NONMOVABLE(Mutex);
    friend class ConditionVariable;

public:
    Mutex()
        : m_lock_count(0)
    {
    }
    ~Mutex()
    {
    }

    void lock();
    void unlock();

private:
    unsigned m_lock_count { 0 };
};

class MutexLocker {
    AK_MAKE_NONCOPYABLE(MutexLocker);
    AK_MAKE_NONMOVABLE(MutexLocker);

public:
    ALWAYS_INLINE explicit MutexLocker(Mutex& mutex)
        : m_mutex(mutex)
    {
        lock();
    }
    ALWAYS_INLINE ~MutexLocker()
    {
        unlock();
    }
    ALWAYS_INLINE void unlock() { m_mutex.unlock(); }
    ALWAYS_INLINE void lock() { m_mutex.lock(); }

private:
    Mutex& m_mutex;
};

}
