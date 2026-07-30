#include "eulerfoil/compat.h"
#include "eulerfoil/simd.h"
#include "helpers.h"

#include <unity.h>

/**
 * @file test_simd.c
 * @brief Unit tests for eulerfoil/simd.h functions.
 *
 * Corresponding <math.h> functions are used as the ground truth. Each function
 * is tested over a randomly generated array and its lanes are compared against
 * the scalar math.h result.
 *
 * fma() is the reference for the SIMD FMA-like instructions, since it gives
 * the same single-rounding as the SIMD FMA instructions.
 */

/* random seed */
#define RAND_SEED 42U

/* number of SIMD vectors the test case array can hold. */
#define N_SIMD_VEC 1024U

/* number of elements (doubles) in the test array */
#define N_TEST_ARRAY ((size_t) N_SIMD_VEC * EF_SIMD_WIDTH)

/* test cases */
/* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */
static EF_ALIGNAS(EF_SIMD_ALIGNMENT) double test_array_f64[N_TEST_ARRAY];

/* NOLINTNEXTLINE(readability-identifier-naming) */
void setUp(void)
{
    ef_fill_random_f64(test_array_f64, N_TEST_ARRAY, RAND_SEED);
}

/* NOLINTNEXTLINE(readability-identifier-naming) */
void tearDown(void)
{
}

void test_ef_simd_set1_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; ++i)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_set1_f64(test_array_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);
        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* no arithmetics -> should be bitwise identical */
            TEST_ASSERT_EQUAL_MEMORY(&test_array_f64[i], &actual[j],
                                     sizeof(double));
        }
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ef_simd_set1_f64);

    return UNITY_END();
}
