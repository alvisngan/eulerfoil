#include <math.h>
typedef double simd_f64_t;
#define EF_SIMD_WIDTH 1

static inline simd_f64_t simd_set1_f64(double x)
{
    return x;
}

static inline simd_f64_t simd_load_f64(const double *p)
{
    return *p;
}

static inline simd_f64_t simd_load_aligned_f64(const double *p)
{
    return *p;
}

static inline void simd_store_f64(double *restrict p, simd_t simd_vec)
{
    *p = simd_vec;
}

static inline void simd_store_aligned_f64(double *restrict p, simd_t simd_vec)
{
    *p = simd_vec;
}

static inline simd_f64_t simd_add_f64(simd_f64_t a, simd_f64_t b)
{
    return a + b;
}

static inline simd_f64_t simd_sub_f64(simd_f64_t a, simd_f64_t b)
{
    return a - b;
}

static inline simd_f64_t simd_mul_f64(simd_f64_t a, simd_f64_t b)
{
    return a * b;
}

static inline simd_f64_t simd_div_f64(simd_f64_t num, simd_f64_t den)
{
    return num / den;
}

static inline simd_f64_t simd_mul_add_f64(simd_f64_t mul_a, simd_f64_t mul_b,
                                          simd_f64_t add)
{
    return fma(mul_a, mul_b, add);
}

static inline simd_f64_t simd_neg_mul_add_f64(simd_f64_t mul_a,
                                              simd_f64_t mul_b, simd_f64_t add)
{
    return fma(-mul_a, mul_b, add);
}

static inline simd_f64_t simd_mul_sub_f64(simd_f64_t mul_a, simd_f64_t mul_b,
                                          simd_f64_t sub)
{
    return fma(mul_a, mul_b, -sub);
}

static inline simd_f64_t simd_neg_mul_sub_f64(simd_f64_t mul_a,
                                              simd_f64_t mul_b, simd_f64_t sub)
{
    return fma(-mul_a, mul_b, -sub);
}

static inline simd_f64_t simd_sqrt_f64(simd_f64_t x)
{
    return sqrt(x);
}

static inline simd_f64_t simd_abs_f64(simd_f64_t x)
{
    return fabs(x);
}

static inline simd_f64_t simd_max_f64(simd_f64_t a, simd_f64_t b)
{
    return fmax(a, b);
}

static inline simd_f64_t simd_min_f64(simd_f64_t a, simd_f64_t b)
{
    return fmin(a, b);
}
