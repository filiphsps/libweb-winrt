#pragma once

#include <atomic>
#include "Concepts.h"
#include "Platform.h"
#include "Types.h"

namespace AK {

template<typename T>
static ALWAYS_INLINE T atomic_exchange(volatile T* var, T desired, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return desired;
}

/*template<typename T, typename V = RemoveVolatile<T>>
static ALWAYS_INLINE V* atomic_exchange(volatile T** var, V* desired, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}

template<typename T, typename V = RemoveVolatile<T>>
static ALWAYS_INLINE V* atomic_exchange(volatile T** var, std::nullptr_t, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}*/

template<typename T>
static ALWAYS_INLINE bool atomic_compare_exchange_strong(volatile T* var, T& expected, T desired, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}

template<typename T, typename V = RemoveVolatile<T>>
static ALWAYS_INLINE bool atomic_compare_exchange_strong(volatile T** var, V*& expected, V* desired, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}

template<typename T, typename V = RemoveVolatile<T>>
static ALWAYS_INLINE bool atomic_compare_exchange_strong(volatile T** var, V*& expected, std::nullptr_t, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}

template<typename T>
static ALWAYS_INLINE T atomic_fetch_add(volatile T* var, T val, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return val;
}

template<typename T>
static ALWAYS_INLINE T atomic_fetch_sub(volatile T* var, T val, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return val;
}

template<typename T>
static ALWAYS_INLINE T atomic_fetch_and(volatile T* var, T val, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return val;
}

template<typename T>
static ALWAYS_INLINE T atomic_fetch_or(volatile T* var, T val, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return val;
}

template<typename T>
static ALWAYS_INLINE T atomic_fetch_xor(volatile T* var, T val, MemoryOrder order = memory_order_seq_cst) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return val;
}

template<typename T>
static ALWAYS_INLINE bool atomic_is_lock_free(volatile T* ptr = nullptr) noexcept
{
    // FIXME: Impl this.
    VERIFY_NOT_REACHED();
    return false;
}

template<typename T, MemoryOrder DefaultMemoryOrder = AK::MemoryOrder::memory_order_seq_cst>
class Atomic {
    T* m_value{ nullptr };

public:
    Atomic() noexcept = default;
    Atomic& operator=(Atomic const&) volatile = delete;
    Atomic& operator=(Atomic&&) volatile = delete;
    Atomic(Atomic const&) = delete;
    Atomic(Atomic&&) = delete;

    constexpr Atomic(T* val) noexcept
        : m_value(val)
    {
    }

    T* operator++() volatile noexcept
    {
        return fetch_add(1) + 1;
    }

    T* operator++(int) volatile noexcept
    {
        return fetch_add(1);
    }

    T* operator+=(ptrdiff_t val) volatile noexcept
    {
        return fetch_add(val) + val;
    }

    T* fetch_add(ptrdiff_t val, MemoryOrder order = DefaultMemoryOrder) volatile noexcept
    {
        return atomic_fetch_add(&m_value, val * sizeof(*m_value), order);
    }

    T* operator--() volatile noexcept
    {
        return fetch_sub(1) - 1;
    }

    T* operator--(int) volatile noexcept
    {
        return fetch_sub(1);
    }

    T* operator-=(ptrdiff_t val) volatile noexcept
    {
        return fetch_sub(val) - val;
    }

    T* fetch_sub(ptrdiff_t val, MemoryOrder order = DefaultMemoryOrder) volatile noexcept
    {
        return fetch_sub(&m_value, val * sizeof(*m_value), order);
    }
};

}
