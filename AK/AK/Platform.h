#pragma once
#include <limits.h>

#ifdef _M_IX86
#    define AK_ARCH_I386 1
#endif

#ifdef _M_AMD64
#    define AK_ARCH_X86_64 1
#endif

#ifdef _M_ARM
#    define AK_ARCH_AARCH64 1
#endif

#ifdef _M_ARM64
#    define AK_ARCH_AARCH32 1
#endif

#define AK_OS_WINRT

#ifdef ALWAYS_INLINE
#    undef ALWAYS_INLINE
#endif
#define ALWAYS_INLINE /*__attribute__((always_inline))*/ inline

#ifdef NEVER_INLINE
#    undef NEVER_INLINE
#endif
#define NEVER_INLINE //__attribute__((noinline))

#ifdef FLATTEN
#    undef FLATTEN
#endif
#define FLATTEN //__attribute__((flatten))

#ifdef RETURNS_NONNULL
#    undef RETURNS_NONNULL
#endif
#define RETURNS_NONNULL //__attribute__((returns_nonnull))

#ifdef NO_SANITIZE_ADDRESS
#    undef NO_SANITIZE_ADDRESS
#endif
#define NO_SANITIZE_ADDRESS //__attribute__((no_sanitize_address))

#ifdef NAKED
#    undef NAKED
#endif
#define NAKED //__attribute__((naked))

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
#define ssize_t __int64
#define suseconds_t long int
