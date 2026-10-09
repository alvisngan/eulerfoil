#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* --- Definitions --- */

/**
 * @def RAND_BITS
 * @brief Minimum usable pseudo-random bits in the C standard library @c rand()
 *        call.
 *
 * C Standard guarantees minimum RAND_MAX to be at least 32767, which has
 * 15-bit.
 */
#define RAND_BITS 15U

/**
 * @def F64_BITS
 * @brief Number of bits in a double (f64).
 */
#define F64_BITS 64U

/* --- Implementations --- */

/**
 * @brief Generate 64 pseudo-random bits using the C standard library's
 *        @c rand().
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
    const uint64_t rand_bitmask = ((uint64_t) 1U << RAND_BITS) - 1U;

    for (unsigned int i = 0; i < F64_BITS; i += RAND_BITS)
    {
        bits <<= RAND_BITS;
        bits |= (uint64_t) rand();
    }

    return bits;
}

double ef_canonicalize_nan(double d)
{
    if (isnan(d))
    {
        d = (double) NAN;
    }

    return d;
}

void ef_random_generator_seed(unsigned int seed)
{
    srand(seed);
}

uint64_t ef_random_generator(void *state)
{
    (void) state;
    return rand_bits_64();
}

void ef_fill_random_f64(double *buf, size_t n,
                        uint64_t (*random_func)(void *state),
                        void *random_state)
{
    for (size_t i = 0; i < n; ++i)
    {
        double   d;
        uint64_t u = rand_bits_64();
        memcpy(&d, &u, sizeof(d));
        d      = ef_canonicalize_nan(d);
        buf[i] = d;
    }
}

void ef_fill_random_bounded_f64(double *buf, size_t n, double upper_bound,
                                double lower_bound,
                                uint64_t (*random_func)(void *state),
                                void *random_state)
{
    const double range = upper_bound - lower_bound;

    /* doubles have precision of 53 (DBL_MANT_DIG), so every whole number  */
    /* from 0 to 2^53 (1.000...000 x 2^53) are exact, converting to double */
    /* never rounds                                                        */
    double max_exact = (double) (UINT64_MAX >> (F64_BITS - DBL_MANT_DIG));

    for (size_t i = 0; i < n; ++i)
    {
        /* random exact double, within the [0, 2^53] exact whole number limit */
        uint64_t bits = random_func(random_state) >> (F64_BITS - DBL_MANT_DIG);
        double   random_exact = (double) bits;

        /* convert the random bits to double [0.0, 1.0) */
        /* adding one since the upper bound is exclusive */
        double foo = random_exact / (max_exact + 1.0);
        double bar = lower_bound + range * foo;

        /* bar may round up to reach or exceed the upper bound          */
        /* if so, reduce it to the largest double below the upper bound */
        if (bar >= upper_bound)
        {
            bar = nextafter(upper_bound, lower_bound);
        }
        buf[i] = bar;
    }
}
