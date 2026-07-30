#include "eulerfoil/compat.h"

#include <unity.h>

/**
 * @file test_compat.c
 * @brief Unit tests for eulerfoil/compat.h functions.
 */

#define ARR_SIZE 128U

/* NOLINTNEXTLINE(readability-identifier-naming) */
void setUp(void)
{
}

/* NOLINTNEXTLINE(readability-identifier-naming) */
void tearDown(void)
{
}

void test_ef_is_aligned(void)
{
    EF_ALIGNAS(64) unsigned char arr[ARR_SIZE] = {0};

    /* aligned cases */
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 1U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 2U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 4U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 8U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 16U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 32U));
    TEST_ASSERT_TRUE(ef_is_aligned((void *) arr, 64U));

    /* misaligned cases */
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[1], 2U));
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[2], 4U));
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[4], 8U));
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[8], 16U));
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[16], 32U));
    TEST_ASSERT_FALSE(ef_is_aligned((void *) &arr[32], 64U));

    /* every byte is aligned to one byte */
    for (size_t i = 0U; i < ARR_SIZE; ++i)
    {
        TEST_ASSERT_TRUE(ef_is_aligned(&arr[i], 1U));
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ef_is_aligned);

    return UNITY_END();
}
