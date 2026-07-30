#ifndef EULERFOIL_COMPAT_H
#define EULERFOIL_COMPAT_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if !defined(UINTPTR_MAX)
#   error "uintptr_t not provided, eulerfoil requires an implementation with <stdint.h> uintptr_t"
#endif

#if defined(_MSC_VER)
    #define EF_ALIGNAS(n) __declspec(align(n))
#elif defined(__GNUC__) || defined(__clang__)
    #define EF_ALIGNAS(n) __attribute__((aligned(n)))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 2011112L
    #define EF_ALIGNAS(n) _Alignas(n)
#else
    #error "EF_ALIGNAS requires GCC, Clang, MSVC, or a C11 compiler"
#endif

/**
 * @brief Test whether a pointer meets a given byte alignment
 *
 * @param[in] p Pointer to test.
 *
 * @param[in] n Aignment in bytes. Must be a nonzero power of two.
 *
 * @return @c true if @p p is aligned to @p n bytes, @c false otherwise.
 *
 * @pre @p n is a nonzero power of two. Violation triggers @c assert in debug
 *         build.
 *
 * @note Intended as the predicate for @c assert at SIMD load/store call sites:
 *          @code
 *          assert(ef_is_aligned(p, EF_SIMD_ALIGNMENT));
 *          @endcode
 */
static inline bool ef_is_aligned(const void *p, size_t n)
{
    assert((n != 0u) && "alignment must be nonzero");
    assert(((n & (n - 1u)) == 0u) && "alignment must be power of two");
    return ((uintptr_t)p & (n - 1u)) == 0u;
}

#endif
