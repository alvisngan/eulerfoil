#include "eulerfoil/simd.h"

/**
 * @brief Pressure from state.
 *
 * \f[ p = (\gamma - 1) \rho \left( E - \frac{u^2 + v^2}{2} \right) \f]
 * \f[ p = (\gamma - 1) \left( e - \frac{m_1^2 + m_2^2}{2 \rho} \right) \f]
 *
 * @pre \f$\gamma > 1\f$, \f$\rho > 0\f$,
 *      \f$ e > \frac{m_1^2 + m_2^2}{2 \rho}\f$
 */
static inline EF_SimdF64 ef_pressure(const double gamma, const EF_SimdF64 rho,
                                     const EF_SimdF64 m_1, const EF_SimdF64 m_2,
                                     const EF_SimdF64 e);

/* --- Definitions --- */

static inline EF_SimdF64 ef_pressure(const double gamma, const EF_SimdF64 rho,
                                     const EF_SimdF64 m_1, const EF_SimdF64 m_2,
                                     const EF_SimdF64 e)
{
    assert(gamma > 1.0);
    assert(ef_simd_all_true_mask64(
        ef_simd_compare_greater_f64(rho, ef_simd_set1_f64(0.0))));

    /* (m_1^2 + m_2^2)/(2 rho) */
    const EF_SimdF64 kinectic = ef_simd_div_f64(
        ef_simd_add_f64(ef_simd_mul_f64(m_1, m_1), ef_simd_mul_f64(m_2, m_2)),
        ef_simd_mul_f64(ef_simd_set1_f64(2.0), rho));

    assert(ef_simd_all_true_mask64(ef_simd_compare_greater_f64(e, kinectic)));

    return (ef_simd_mul_f64(ef_simd_set1_f64(gamma - 1.0),
                            ef_simd_sub_f64(e, kinectic)));
}
