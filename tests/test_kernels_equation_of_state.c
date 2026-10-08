#include "eulerfoil/kernels/gas_dynamics/equation_of_state.h"
#include "eulerfoil/simd.h"
#include "helpers.h"

#include <math.h>
#include <stdbool.h>
#include <unity.h>

/**
 * @file test_kernels_equation_of_state.c
 * @brief Unit tests for eulerfoil/kernels/gas_dynamcis/equation_of_state.
 *
 * Each kernel is covered by up to three kinds of tests:
 * - Known cases:   compare results from hand-picked inputs against
 *                  hand-calculated results
 * - Scalar oracle: compare results from random valid inputs against results
 *                  from formula written in plain double arithmetic.
 * - Properties:    random states with constraint applied, such as zero
 *                  momentum
 */

/* floating point test tolerance */
#ifndef EF_TEST_TOLERANCE
#define EF_TEST_TOLERANCE 1.0e-12
#endif /* EF_TEST_TOLERANCE */

/* random seed */
#ifndef RAND_SEED
#define RAND_SEED 42U
#endif /* RAND_SEED */

/* number of SIMD vectors the test case array can hold. */
#ifndef N_SIMD_VEC
#define N_SIMD_VEC
#endif /* N_SIMD_VEC */

/* number of elements (doubles) in the test array */
#ifndef N_TEST_ARRAY
#define N_TEST_ARRAY ((size_t) N_SIMD_VEC * EF_SIMD_WIDTH)
#endif /* N_TEST_ARRAY */

/* NOLINTNEXTLINE(readability-identifier-naming) */
void setUp(void)
{
}

/* NOLINTNEXTLINE(readability-identifier-naming) */
void tearDown(void)
{
}

void test_ef_pressure_known_case(void)
{
    double     gamma      = 1.5;
    EF_SimdF64 rho        = ef_simd_set1_f64(2.0);
    EF_SimdF64 m1         = ef_simd_set1_f64(4.0);
    EF_SimdF64 m2         = ef_simd_set1_f64(2.0);
    EF_SimdF64 e          = ef_simd_set1_f64(7.0);
    double     p_expected = 1.0;

    double p_actual[EF_SIMD_WIDTH];
    ef_simd_store_f64(p_actual, ef_pressure(gamma, rho, m1, m2, e));

    for (size_t i = 0; i < EF_SIMD_WIDTH; ++i)
    {
        TEST_ASSERT_DOUBLE_WITHIN(EF_TEST_TOLERANCE, p_expected, p_actual[i]);
    }
}

void test_ef_pressure_random_sweep(void)
{
    /* compare against plain double version of the equation */
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ef_pressure_known_case);

    return UNITY_END();
}
