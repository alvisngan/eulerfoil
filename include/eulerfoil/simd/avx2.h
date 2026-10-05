
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

static inline EF_SimdF64 ef_simd_neg_f64(EF_SimdF64 x)
{
    /* set the sign bit; (two's complement) */
    const __m256i sign_bit = _mm256_set1_epi64x(INT64_MIN);
    return _mm256_xor_pd(x, _mm256_castsi256_pd(sign_bit));
}
