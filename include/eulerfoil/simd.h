#ifndef EULERFOIL_SIMD_H
#define EULERFOIL_SIMD_H

#include <math.h>

/*
 * MSVC does not define __FMA__, but if __AVX2__ is defined it must
 * contain FMA extensions.
 *
 * https://learn.microsoft.com/en-us/cpp/build/reference/arch-x86?view=msvc-170
 */
#if defined(__AVX2__) && (defined(__FMA__) || defined(_MSC_VER))
#include "eulerfoil/simd/avx2.h"
#else
#include "eulerfoil/simd/scalar.h"
#endif

static inline bool ef_simd_all_positive_f64(EF_SimdF64 vec)
{
    EF_SimdMask64 mask =
        ef_simd_compare_greater_f64(vec, ef_simd_set1_f64(0.0));
    return ef_simd_all_true_mask64(mask);
}

static inline bool ef_simd_all_positive_finite_f64(EF_SimdF64 vec)
{
    EF_SimdMask64 mask1 =
        ef_simd_compare_greater_f64(vec, ef_simd_set1_f64(0.0));
    EF_SimdMask64 mask2 =
        ef_simd_compare_less_f64(vec, ef_simd_set1_f64(INFINITY));
    return ef_simd_all_true_mask64(mask1) && ef_simd_all_true_mask64(mask2);
}

static inline bool ef_simd_all_finite_f64(EF_SimdF64 vec)
{
    EF_SimdMask64 mask1 =
        ef_simd_compare_less_f64(vec, ef_simd_set1_f64(INFINITY));
    EF_SimdMask64 mask2 =
        ef_simd_compare_greater_f64(vec, ef_simd_set1_f64(-INFINITY));
    return ef_simd_all_true_mask64(mask1) && ef_simd_all_true_mask64(mask2);
}

static inline bool ef_simd_all_greater_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    EF_SimdMask64 mask = ef_simd_compare_greater_f64(a, b);
    return ef_simd_all_true_mask64(mask);
}

static inline bool ef_simd_all_less_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    EF_SimdMask64 mask = ef_simd_compare_less_f64(a, b);
    return ef_simd_all_true_mask64(mask);
}

static inline bool ef_simd_all_greater_equal_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    EF_SimdMask64 mask = ef_simd_compare_greater_equal_f64(a, b);
    return ef_simd_all_true_mask64(mask);
}

static inline bool ef_simd_all_less_equal_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    EF_SimdMask64 mask = ef_simd_compare_less_equal_f64(a, b);
    return ef_simd_all_true_mask64(mask);
}

#endif
