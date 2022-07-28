#pragma once
#include <limits.h>
#include <minwindef.h>

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

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

// built-ins
#define __builtin_isnan isnan
#define __builtin_isinf isinf
#define __builtin_isinf_sign isinf
#define ssize_t size_t
