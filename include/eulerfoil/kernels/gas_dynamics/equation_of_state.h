#ifndef EULERFOIL_KERNELS_GAS_DYNAMICS_EQUATION_OF_STATE_H
#define EULERFOIL_KERNELS_GAS_DYNAMICS_EQUATION_OF_STATE_H

#include "eulerfoil/simd.h"

#include <math.h>

/**
 * @brief Pressure from state.
 *
 * \f[ p = (\gamma - 1) \rho \left( E - \frac{u^2 + v^2}{2} \right) \f]
 * \f[ p = (\gamma - 1) \left( e - \frac{m_1^2 + m_2^2}{2 \rho} \right) \f]
 *
 * @pre \f$\gamma \in (1 , \infty)\f$, \f$\rho \in (0, \infty)\f$,
 *      \f$m_1 \in (-\infty, \infty)\f$, \f$m_2 \in (-\infty, \infty)\f$,
 *      \f$ e \in \left( \frac{m_1^2 + m_2^2}{2 \rho}, \infty \right)\f$
 */
static inline EF_SimdF64 ef_pressure(const double gamma, const EF_SimdF64 rho,
                                     const EF_SimdF64 m1, const EF_SimdF64 m2,
                                     const EF_SimdF64 e);

/**
 * @brief Local speed of sound.
 *
 * \f[ c = \sqrt{\frac{\gamma p}{\rho}} \f]
 *
 * @pre \f$\gamma \in (1 , \infty)\f$, \f$\rho \in (0, \infty)\f$,
 *      \f$p \in (0, \infty)\f$
 */
static inline EF_SimdF64 ef_sound(const double gamma, const EF_SimdF64 rho,
                                  const EF_SimdF64 p);

/* --- Definitions --- */

static inline EF_SimdF64 ef_pressure(const double gamma, const EF_SimdF64 rho,
                                     const EF_SimdF64 m1, const EF_SimdF64 m2,
                                     const EF_SimdF64 e)
{
    assert((gamma > 1.0) && (gamma < INFINITY));
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m1));
    assert(ef_simd_all_finite_f64(m2));
    assert(ef_simd_all_positive_finite_f64(e));

    /* (m_1^2 + m_2^2)/(2 rho) */
    const EF_SimdF64 kinectic = ef_simd_div_f64(
        ef_simd_add_f64(ef_simd_mul_f64(m1, m1), ef_simd_mul_f64(m2, m2)),
        ef_simd_mul_f64(ef_simd_set1_f64(2.0), rho));

    assert(ef_simd_all_greater_f64(e, kinectic));

    return (ef_simd_mul_f64(ef_simd_set1_f64(gamma - 1.0),
                            ef_simd_sub_f64(e, kinectic)));
}

static inline EF_SimdF64 ef_sound(const double gamma, const EF_SimdF64 rho,
                                  const EF_SimdF64 p)
{
    assert((gamma > 1.0) && (gamma < INFINITY));
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_positive_finite_f64(p));

    return ef_simd_sqrt_f64(
        ef_simd_div_f64(ef_simd_mul_f64(ef_simd_set1_f64(gamma), p), rho));
}

#endif
