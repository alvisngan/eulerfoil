#ifndef EULERFOIL_TESTS_HELPERS_H /* NOLINT(llvm-header-guard */
#define EULERFOIL_TESTS_HELPERS_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Generate an array of unbounded pseudo-random f64 (double) numbers.
 *
 * @param[out]  buf             Array destination; must hold n elements.
 * @param[in]   n               Number of elements.
 * @param[in]   seed            Pseudo-random number generator seed.
 */
void ef_fill_random_f64(double *buf, size_t n, uint32_t seed);

/**
 * @brief Generate an array of bounded pseudo-random doubles.
 *
 * Each element is drawn uniformly from half-open interval
 * [lower_bound, upper_bound).
 *
 * @param[out]  buf             Array destination; must hold n elements.
 * @param[in]   n               Number of elements.
 * @param[in]   upper_bound     Upper bound; exclusive.
 * @param[in]   lower_bound     Lower bound; inclusive.
 * @param[in]   seed            Pseudo-random number generator seed.
 */
void ef_fill_random_bounded_f64(double *buf, size_t n, double upper_bound,
                                double lower_bound, uint32_t seed);

#endif /* EULERFOIL_TESTS_HELPERS_H */
