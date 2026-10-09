#ifndef EULERFOIL_TESTS_HELPERS_H /* NOLINT(llvm-header-guard */
#define EULERFOIL_TESTS_HELPERS_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Cleaning up signaling NaN to canonical (quiet) NaN.
 *
 * @param[in] d Any double that could contain signaling or quiet NaN.
 *
 * @return If @p d is signaling NaN, it returns a canonical (quiet NaN);
 *         otherwise, the function returns d.
 */
double ef_canonicalize_nan(double d);

/**
 * @brief Seed ef_random_generator().
 *
 * @param[in] seed Starting point of the sequence.
 */
void ef_random_generator_seed(unsigned int seed);

/**
 * @brief 64bit random number generator built from the C standard library's
 *        @c rand().
 *
 * Seed with the C standard library's @c srand() before the first call.
 *
 * @param[in]   state   Random number generator internal state, currently
 *                      unused.
 *
 * @return 64 uniformly random bits.
 */
uint64_t ef_random_generator(void *state);

/**
 * @brief Generate an array of unbounded pseudo-random f64 (double) numbers.
 *
 * @pre Every call to @p random_func returns 64 uniformly random bits.
 *      C standard library does NOT generate 64 random bits, see
 *      ef_random_generator().
 *
 * @param[out]      buf             Array destination; must hold @p n elements.
 * @param[in]       n               Number of elements.
 * @param[in]       random_func     Random number generator function; must
 *                                  return 64 uniformly random bits per call.
 * @param[in,out]   random_state    Input for the @p random_func, may be @c NULL
 *                                  if the generator keeps its own state like
 *                                  the C standard library @c rand().
 */
void ef_fill_random_f64(double *buf, size_t n,
                        uint64_t (*random_func)(void *state),
                        void *random_state);

/**
 * @brief Generate an array of bounded pseudo-random doubles.
 *
 * Each element is drawn uniformly from half-open interval
 * [lower_bound, upper_bound).
 *
 * @pre Every call to @p random_func returns 64 uniformly random bits.
 *      C standard library does NOT generate 64 random bits, see
 *      ef_random_generator().
 *
 * @param[out]      buf             Array destination; must hold @p n elements.
 * @param[in]       n               Number of elements.
 * @param[in]       upper_bound     Upper bound; exclusive.
 * @param[in]       lower_bound     Lower bound; inclusive.
 * @param[in]       random_func     Random number generator function; must
 *                                  return 64 uniformly random bits per call.
 * @param[in,out]   random_state    Input for the @p random_func, may be @c NULL
 *                                  if the generator keeps its own state like
 *                                  the C standard library's @c rand().
 */
void ef_fill_random_bounded_f64(double *buf, size_t n, double upper_bound,
                                double lower_bound,
                                uint64_t (*random_func)(void *state),
                                void *random_state);

#endif /* EULERFOIL_TESTS_HELPERS_H */
