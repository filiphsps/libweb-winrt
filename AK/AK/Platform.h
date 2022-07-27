#pragma once

#ifdef ALWAYS_INLINE
#    undef ALWAYS_INLINE
#endif
#define ALWAYS_INLINE /*__attribute__((always_inline))*/ inline

#ifdef NEVER_INLINE
#    undef NEVER_INLINE
#endif
#define NEVER_INLINE //__attribute__((noinline))

#ifdef RETURNS_NONNULL
#    undef RETURNS_NONNULL
#endif
#define RETURNS_NONNULL //__attribute__((returns_nonnull))

#define ASAN_POISON_MEMORY_REGION(addr, size)
#define ASAN_UNPOISON_MEMORY_REGION(addr, size)

// built-ins
#define __builtin_isnan isnan
#define __builtin_isinf isinf
#define __builtin_isinf_sign isinf