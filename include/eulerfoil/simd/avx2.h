#ifndef EULERFOIL_SIMD_AVX2_H
#define EULERFOIL_SIMD_AVX2_H

#include "eulerfoil/compat.h"

#include <immintrin.h>

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
typedef __m256d EF_SimdF64;
typedef __m256i EF_SimdMask64;
#define EF_SIMD_WIDTH 4
#define EF_SIMD_ALIGNMENT 32

static inline EF_SimdF64 ef_simd_set1_f64(double x)
{
    return _mm256_set1_pd(x);
}

static inline EF_SimdF64 ef_simd_load_f64(const double *p)
{
    return _mm256_loadu_pd(p);
}

static inline EF_SimdF64 ef_simd_load_aligned_f64(const double *p)
{
    assert(ef_is_aligned(p, EF_SIMD_ALIGNMENT) &&
           "pointer must be SIMD-aligned");
    return _mm256_load_pd(p);
}

static inline void ef_simd_store_f64(double *restrict p, EF_SimdF64 simd_vec)
{
    _mm256_storeu_pd(p, simd_vec);
}

static inline void ef_simd_store_aligned_f64(double *restrict p,
                                             EF_SimdF64 simd_vec)
{
    assert(ef_is_aligned(p, EF_SIMD_ALIGNMENT) &&
           "pointer must be SIMD-aligned");
    _mm256_store_pd(p, simd_vec);
}

static inline void ef_simd_store_mask64(uint64_t *restrict p,
                                        EF_SimdMask64 mask)
{
    /* storing to i64 array is not supported in AVX2 */
    void *dst = p;
    _mm256_storeu_si256((__m256i *)dst, mask);
}

static inline EF_SimdF64 ef_simd_add_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return _mm256_add_pd(a, b);
}

static inline EF_SimdF64 ef_simd_sub_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return _mm256_sub_pd(a, b);
}

static inline EF_SimdF64 ef_simd_mul_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return _mm256_mul_pd(a, b);
}

static inline EF_SimdF64 ef_simd_div_f64(EF_SimdF64 num, EF_SimdF64 den)
{
    return _mm256_div_pd(num, den);
}

static inline EF_SimdF64 ef_simd_mul_add_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                             EF_SimdF64 add)
{
    return _mm256_fmadd_pd(mul_a, mul_b, add);
}

static inline EF_SimdF64
ef_simd_neg_mul_add_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b, EF_SimdF64 add)
{
    return _mm256_fnmadd_pd(mul_a, mul_b, add);
}

static inline EF_SimdF64 ef_simd_mul_sub_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                             EF_SimdF64 sub)
{
    return _mm256_fmsub_pd(mul_a, mul_b, sub);
}

static inline EF_SimdF64
ef_simd_neg_mul_sub_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b, EF_SimdF64 sub)
{
    return _mm256_fnmsub_pd(mul_a, mul_b, sub);
}

static inline EF_SimdF64 ef_simd_sqrt_f64(EF_SimdF64 x)
{
    return _mm256_sqrt_pd(x);
}

static inline EF_SimdF64 ef_simd_abs_f64(EF_SimdF64 x)
{
    /* clear the sign bit */
    const __m256i sign_cleared = _mm256_set1_epi64x(UINT64_MAX >> 1);
    return _mm256_and_pd(x, _mm256_castsi256_pd(sign_cleared));
}

static inline EF_SimdF64 ef_simd_max_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    /* AVX max/min returns b when there is a NaN, violating IEEE specs */
    const __m256d foo = _mm256_max_pd(a, b);

    /* (b_i == NaN) ? all-ones : 0 */
    const __m256d b_nan_mask = _mm256_cmp_pd(b, b, _CMP_UNORD_Q);

    /* choose a_i if b_i is NaN, matching the IEEE specs */
    return _mm256_blendv_pd(foo, a, b_nan_mask);
}

static inline EF_SimdF64 ef_simd_min_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    /* AVX max/min returns b when there is a NaN, violating IEEE specs */
    const __m256d foo = _mm256_min_pd(a, b);

    /* (b_i == NaN) ? all-ones : 0 */
    const __m256d b_nan_mask = _mm256_cmp_pd(b, b, _CMP_UNORD_Q);

    /* choose a_i if b_i is NaN, matching the IEEE specs */
    return _mm256_blendv_pd(foo, a, b_nan_mask);
}

static inline EF_SimdF64 ef_simd_neg_f64(EF_SimdF64 x)
{
    /* set the sign bit; (two's complement) */
    const __m256i sign_bit = _mm256_set1_epi64x(INT64_MIN);
    return _mm256_xor_pd(x, _mm256_castsi256_pd(sign_bit));
}

static inline EF_SimdMask64 ef_simd_compare_greater_f64(EF_SimdF64 a,
                                                        EF_SimdF64 b)
{
    return _mm256_castpd_si256(_mm256_cmp_pd(a, b, _CMP_GT_OS));
}

static inline EF_SimdMask64 ef_simd_compare_less_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return _mm256_castpd_si256(_mm256_cmp_pd(a, b, _CMP_LT_OS));
}

static inline EF_SimdMask64 ef_simd_compare_greater_equal_f64(EF_SimdF64 a,
                                                              EF_SimdF64 b)
{
    return _mm256_castpd_si256(_mm256_cmp_pd(a, b, _CMP_GE_OS));
}

static inline EF_SimdMask64 ef_simd_compare_less_equal_f64(EF_SimdF64 a,
                                                           EF_SimdF64 b)
{
    return _mm256_castpd_si256(_mm256_cmp_pd(a, b, _CMP_LE_OS));
}

static inline bool ef_simd_is_canonical_mask64(EF_SimdMask64 mask)
{
    const __m256i is_zero = _mm256_cmpeq_epi64(mask, _mm256_setzero_si256());
    const __m256i is_ones = _mm256_cmpeq_epi64(mask, _mm256_set1_epi64x(-1));
    const __m256i ok = _mm256_or_si256(is_zero, is_ones);
    return _mm256_movemask_pd(_mm256_castsi256_pd(ok)) == 0xF;
}

static inline bool ef_simd_all_true_mask64(EF_SimdMask64 mask)
{
    assert(ef_simd_is_canonical_mask64(mask) &&
           "mask lanes mush be all-ones or zero");
    return _mm256_movemask_pd(_mm256_castsi256_pd(mask)) == 0xF;
}

#endif
