#ifndef EULERFOIL_SIMD_SCALAR_H
#define EULERFOIL_SIMD_SCALAR_H

#include <math.h>
typedef double EF_SimdF64;
#define EF_SIMD_WIDTH 1
#define EF_SIMD_ALIGNMENT 8

static inline EF_SimdF64 ef_simd_set1_f64(double x)
{
    return x;
}

static inline EF_SimdF64 ef_simd_load_f64(const double *p)
{
    return *p;
}

static inline EF_SimdF64 ef_simd_load_aligned_f64(const double *p)
{
    return *p;
}

static inline void ef_simd_store_f64(double *restrict p, EF_SimdF64 simd_vec)
{
    *p = simd_vec;
}

static inline void ef_simd_store_aligned_f64(double *restrict p,
                                          EF_SimdF64 simd_vec)
{
    *p = simd_vec;
}

static inline EF_SimdF64 ef_simd_add_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a + b;
}

static inline EF_SimdF64 ef_simd_sub_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a - b;
}

static inline EF_SimdF64 ef_simd_mul_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a * b;
}

static inline EF_SimdF64 ef_simd_div_f64(EF_SimdF64 num, EF_SimdF64 den)
{
    return num / den;
}

static inline EF_SimdF64 ef_simd_mul_add_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                          EF_SimdF64 add)
{
    return fma(mul_a, mul_b, add);
}

static inline EF_SimdF64 ef_simd_neg_mul_add_f64(EF_SimdF64 mul_a,
                                              EF_SimdF64 mul_b, EF_SimdF64 add)
{
    return fma(-mul_a, mul_b, add);
}

static inline EF_SimdF64 ef_simd_mul_sub_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                          EF_SimdF64 sub)
{
    return fma(mul_a, mul_b, -sub);
}

static inline EF_SimdF64 ef_simd_neg_mul_sub_f64(EF_SimdF64 mul_a,
                                              EF_SimdF64 mul_b, EF_SimdF64 sub)
{
    return fma(-mul_a, mul_b, -sub);
}

static inline EF_SimdF64 ef_simd_sqrt_f64(EF_SimdF64 x)
{
    return sqrt(x);
}

static inline EF_SimdF64 ef_simd_abs_f64(EF_SimdF64 x)
{
    return fabs(x);
}

static inline EF_SimdF64 ef_simd_max_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return fmax(a, b);
}

static inline EF_SimdF64 ef_simd_min_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return fmin(a, b);
}

#endif
