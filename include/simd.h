#include <math.h>
typedef double EF_SimdF64;
#define EF_SIMD_WIDTH 1

static inline EF_SimdF64 simd_set1_f64(double x)
{
    return x;
}

static inline EF_SimdF64 simd_load_f64(const double *p)
{
    return *p;
}

static inline EF_SimdF64 simd_load_aligned_f64(const double *p)
{
    return *p;
}

static inline void simd_store_f64(double *restrict p, EF_SimdF64 simd_vec)
{
    *p = simd_vec;
}

static inline void simd_store_aligned_f64(double *restrict p, EF_SimdF64 simd_vec)
{
    *p = simd_vec;
}

static inline EF_SimdF64 simd_add_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a + b;
}

static inline EF_SimdF64 simd_sub_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a - b;
}

static inline EF_SimdF64 simd_mul_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return a * b;
}

static inline EF_SimdF64 simd_div_f64(EF_SimdF64 num, EF_SimdF64 den)
{
    return num / den;
}

static inline EF_SimdF64 simd_mul_add_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                          EF_SimdF64 add)
{
    return fma(mul_a, mul_b, add);
}

static inline EF_SimdF64 simd_neg_mul_add_f64(EF_SimdF64 mul_a,
                                              EF_SimdF64 mul_b, EF_SimdF64 add)
{
    return fma(-mul_a, mul_b, add);
}

static inline EF_SimdF64 simd_mul_sub_f64(EF_SimdF64 mul_a, EF_SimdF64 mul_b,
                                          EF_SimdF64 sub)
{
    return fma(mul_a, mul_b, -sub);
}

static inline EF_SimdF64 simd_neg_mul_sub_f64(EF_SimdF64 mul_a,
                                              EF_SimdF64 mul_b, EF_SimdF64 sub)
{
    return fma(-mul_a, mul_b, -sub);
}

static inline EF_SimdF64 simd_sqrt_f64(EF_SimdF64 x)
{
    return sqrt(x);
}

static inline EF_SimdF64 simd_abs_f64(EF_SimdF64 x)
{
    return fabs(x);
}

static inline EF_SimdF64 simd_max_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return fmax(a, b);
}

static inline EF_SimdF64 simd_min_f64(EF_SimdF64 a, EF_SimdF64 b)
{
    return fmin(a, b);
}
