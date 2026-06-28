#include <stdint.h>
#include <stdlib.h>

/* --- Definitions --- */

/**
 * @def RAND_BITS
 * @brief Minimum usable pseudo-random bits in rand() call.
 *
 * C Standard guarantees minimum RAND_MAX to be at least 32767, which has
 * 15-bit.
 */
#define RAND_BITS 15u

/**
 * @def F64_BITS
 * @brief Number of bits in a double (f64).
 */
#define F64_BITS 64u


/* --- Implementations --- */

/**
 * @brief Generate 64 pseudo-random bits.
 *
 * The C standard only guarantees 15 bits (RAND_BITS) per call, so several
 * draws are packed together to form a 64-bit pseudo-random number.
 *
 * @return A 64-bit value with the bits pseudo-randomly set.
 */
static inline uint64_t rand_bits_64(void)
{
    uint64_t bits = 0;
    /* bit mask with RAND_BITS set bits on the right */
    const uint64_t rand_bitmask = ((uint64_t) 1u << RAND_BITS) - 1u;

    for (unsigned int i = 0; i < F64_BITS; i += RAND_BITS)
    {
        bits <<= RAND_BITS;
        bits |= (uint64_t) rand() & rand_bitmask;
    }

    return bits;
}

static inline void ef_fill_random_f64(double *buf, size_t n, uint32_t seed)
{
    srand(seed);
    for (size_t i = 0; i < n; ++i)
    {
        double   d;
        uint64_t u = rand_bits_64();
        memcpy(&d, &u, sizeof(d));
        buf[i] = d;
    }
}

static inline void ef_fill_random_bounded_f64(double *buf, size_t n,
                                              double upper_bound,
                                              double lower_bound, uint32_t seed)
{
    srand(seed);
    const double range = upper_bound - lower_bound;
    for (size_t i = 0; i < n; ++i)
    {
        /* convert int [0, RAND_MAX] to double [0, 1)               */
        /* + 1.0 on the denominator to force exlusive upper bound   */
        double foo = (double) rand() / ((double) RAND_MAX + 1.0);
        buf[i]     = lower_bound + range * foo;
    }
}
