#pragma once

#include "./AK/Concepts.h"
#include "./AK/Platform.h"
#include "./AK/Types.h"

namespace AK {

template<typename T>
static inline bool atomic_is_lock_free(volatile T* ptr = nullptr) noexcept;

template<typename T, MemoryOrder DefaultMemoryOrder = AK::MemoryOrder::memory_order_seq_cst>
class Atomic {

};

}