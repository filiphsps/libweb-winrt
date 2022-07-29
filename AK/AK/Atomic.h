#pragma once

#include "./AK/Concepts.h"
#include "./AK/Platform.h"
#include "./AK/Types.h"

namespace AK {

template<typename T>
static inline bool atomic_compare_exchange_strong(volatile T* var, T& expected, T desired, MemoryOrder order = memory_order_seq_cst) noexcept;

template<typename T, typename V = RemoveVolatile<T>>
static inline bool atomic_compare_exchange_strong(volatile T** var, V*& expected, V* desired, MemoryOrder order = memory_order_seq_cst) noexcept;

template<typename T, typename V = RemoveVolatile<T>>
static inline bool atomic_compare_exchange_strong(volatile T** var, V*& expected, std::nullptr_t, MemoryOrder order = memory_order_seq_cst) noexcept;

template<typename T>
static inline bool atomic_is_lock_free(volatile T* ptr = nullptr) noexcept;

template<typename T, MemoryOrder DefaultMemoryOrder = AK::MemoryOrder::memory_order_seq_cst>
class Atomic {


};

}