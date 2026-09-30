#include "eulerfoil/compat.h"
#include "eulerfoil/simd.h"
#include "helpers.h"

#include <unity.h>

#include <stdio.h>

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
/* NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables) */
static EF_ALIGNAS(EF_SIMD_ALIGNMENT) double test_array_a_f64[N_TEST_ARRAY];
static EF_ALIGNAS(EF_SIMD_ALIGNMENT) double test_array_b_f64[N_TEST_ARRAY];
static EF_ALIGNAS(EF_SIMD_ALIGNMENT) double test_array_c_f64[N_TEST_ARRAY];
/* NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables) */

/* NOLINTNEXTLINE(readability-identifier-naming) */
void setUp(void)
{
    ef_fill_random_f64(test_array_a_f64, N_TEST_ARRAY, RAND_SEED);
    ef_fill_random_f64(test_array_b_f64, N_TEST_ARRAY, RAND_SEED);
    ef_fill_random_f64(test_array_c_f64, N_TEST_ARRAY, RAND_SEED);
}

/* NOLINTNEXTLINE(readability-identifier-naming) */
void tearDown(void)
{
}

void test_ef_simd_load_store_f64(void)
{
    for (size_t i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_load_f64(&test_array_a_f64[i]);
        ef_simd_store_f64(actual, vec);

        /* no arithmetics -> should be bitwise identical */
        TEST_ASSERT_EQUAL_MEMORY(&test_array_a_f64[i], actual, EF_SIMD_WIDTH);
    }
}

void test_ef_simd_load_store_aligned_f64(void)
{
    for (size_t i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_load_aligned_f64(&test_array_a_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);

        /* no arithmetics -> should be bitwise identical */
        TEST_ASSERT_EQUAL_MEMORY(&test_array_a_f64[i], actual, EF_SIMD_WIDTH);
    }
}

void test_ef_simd_set1_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; ++i)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_set1_f64(test_array_a_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);
        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* no arithmetics -> should be bitwise identical */
            TEST_ASSERT_EQUAL_MEMORY(&test_array_a_f64[i], &actual[j],
                                     sizeof(double));
        }
    }
}

void test_ef_simd_add_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_add_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = test_array_a_f64[i + j] + test_array_b_f64[i + j];
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_sub_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_sub_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = test_array_a_f64[i + j] - test_array_b_f64[i + j];
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_mul_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_mul_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = test_array_a_f64[i + j] * test_array_b_f64[i + j];
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_div_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_div_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = test_array_a_f64[i + j] / test_array_b_f64[i + j];
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_mul_add_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_c = ef_simd_load_f64(&test_array_c_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_mul_add_f64(vec_a, vec_b, vec_c);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = fma(test_array_a_f64[i + j],
                                  test_array_b_f64[i + j],
                                  test_array_c_f64[i + j]);
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_neg_mul_add_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_c = ef_simd_load_f64(&test_array_c_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_neg_mul_add_f64(vec_a, vec_b, vec_c);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = fma(-test_array_a_f64[i + j],
                                  test_array_b_f64[i + j],
                                  test_array_c_f64[i + j]);
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_mul_sub_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_c = ef_simd_load_f64(&test_array_c_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_mul_sub_f64(vec_a, vec_b, vec_c);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = fma(test_array_a_f64[i + j],
                                  test_array_b_f64[i + j],
                                  -test_array_c_f64[i + j]);
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_sqrt_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; ++i)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_sqrt_f64(test_array_a_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);
        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            double expected = sqrt(test_array_a_f64[i+j]);

            /* correctly-rounded op -> should be bit-identical to math.h */
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j],
                                     sizeof(double));
        }
    }
}

void test_ef_simd_abs_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; ++i)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_abs_f64(test_array_a_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);
        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            double expected = fabs(test_array_a_f64[i+j]);

            /* correctly-rounded op -> should be bit-identical to math.h */
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j],
                                     sizeof(double));
        }
    }
}

void test_ef_simd_max_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_max_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = fmax(test_array_a_f64[i + j],
                                   test_array_b_f64[i + j]);
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_min_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdF64 vec_actual = ef_simd_min_f64(vec_a, vec_b);
        ef_simd_store_f64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            double expected = fmin(test_array_a_f64[i + j],
                                   test_array_b_f64[i + j]);
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_neg_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; ++i)
    {
        EF_ALIGNAS(EF_SIMD_ALIGNMENT) double actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec = ef_simd_neg_f64(test_array_a_f64[i]);
        ef_simd_store_aligned_f64(actual, vec);
        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            double expected = -test_array_a_f64[i+j];

            /* correctly-rounded op -> should be bit-identical to math.h */
            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j],
                                     sizeof(double));
        }
    }
}

void test_ef_simd_compare_greater_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        uint64_t actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdMask64 vec_actual = ef_simd_compare_greater_f64(vec_a, vec_b);
        ef_simd_store_mask64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            uint64_t expected = (test_array_a_f64[i + j] >
                                 test_array_b_f64[i + j]) ? UINT64_MAX : 0U;

            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_compare_less_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        uint64_t actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdMask64 vec_actual = ef_simd_compare_less_f64(vec_a, vec_b);
        ef_simd_store_mask64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            uint64_t expected = (test_array_a_f64[i + j] <
                                 test_array_b_f64[i + j]) ? UINT64_MAX : 0U;

            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_compare_greater_equal_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        uint64_t actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdMask64 vec_actual = ef_simd_compare_greater_equal_f64(vec_a,
                                                                     vec_b);
        ef_simd_store_mask64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            uint64_t expected = (test_array_a_f64[i + j] >=
                                 test_array_b_f64[i + j]) ? UINT64_MAX : 0U;

            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

void test_ef_simd_compare_less_equal_f64(void)
{
    for (unsigned int i = 0; i < N_TEST_ARRAY; i += EF_SIMD_WIDTH)
    {
        uint64_t actual[EF_SIMD_WIDTH];
        EF_SimdF64 vec_a = ef_simd_load_f64(&test_array_a_f64[i]);
        EF_SimdF64 vec_b = ef_simd_load_f64(&test_array_b_f64[i]);
        EF_SimdMask64 vec_actual = ef_simd_compare_less_equal_f64(vec_a,
                                                                  vec_b);
        ef_simd_store_mask64(actual, vec_actual);

        for (unsigned int j = 0; j < EF_SIMD_WIDTH; ++j)
        {
            /* correctly-rounded op -> should be bit-identical to math.h */
            uint64_t expected = (test_array_a_f64[i + j] <=
                                 test_array_b_f64[i + j]) ? UINT64_MAX : 0U;

            TEST_ASSERT_EQUAL_MEMORY(&expected, &actual[j], sizeof(double));
        }
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ef_simd_load_store_f64);
    RUN_TEST(test_ef_simd_load_store_aligned_f64);
    RUN_TEST(test_ef_simd_set1_f64);
    RUN_TEST(test_ef_simd_add_f64);
    RUN_TEST(test_ef_simd_sub_f64);
    RUN_TEST(test_ef_simd_mul_f64);
    RUN_TEST(test_ef_simd_div_f64);
    RUN_TEST(test_ef_simd_mul_add_f64);
    RUN_TEST(test_ef_simd_neg_mul_add_f64);
    RUN_TEST(test_ef_simd_mul_sub_f64);
    RUN_TEST(test_ef_simd_sqrt_f64);
    RUN_TEST(test_ef_simd_abs_f64);
    RUN_TEST(test_ef_simd_max_f64);
    RUN_TEST(test_ef_simd_min_f64);
    RUN_TEST(test_ef_simd_compare_greater_f64);
    RUN_TEST(test_ef_simd_compare_less_f64);
    RUN_TEST(test_ef_simd_compare_greater_equal_f64);
    RUN_TEST(test_ef_simd_compare_less_equal_f64);

    return UNITY_END();
}
