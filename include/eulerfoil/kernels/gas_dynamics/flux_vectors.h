#include "eulerfoil/simd.h"

/**
 * @brief x-direction flux for the mass equation.
 *
 * Flux vector:
 * \f[
 * \overrightarrow{f} =
 * \begin{pmatrix}
 *     \rho u \\ \rho u^2 + p \\ \rho u v \\ \rho u H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_1 \\ \frac{m_1^2}{\rho} + p \\ \frac{m_1 m_2}{\rho} \\ \frac{m_1 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{f}_{\rho} = m_1 \f]
 *
 * @pre \f$m_1 \in (-\infty, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_x_rho(const EF_SimdF64 m1);

/**
 * @brief x-direction flux for the x-momentum equation.
 *
 * \f[
 * \overrightarrow{f} =
 * \begin{pmatrix}
 *     \rho u \\ \rho u^2 + p \\ \rho u v \\ \rho u H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_1 \\ \frac{m_1^2}{\rho} + p \\ \frac{m_1 m_2}{\rho} \\ \frac{m_1 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{f}_{m_1} = \frac{m_1^2}{\rho} + p \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_1 \in (-\infty, \infty)\f$,
 *      \f$p \in (0, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_x_m1(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 p);

/**
 * @brief x-direction flux for the y-momentum equation.
 *
 * \f[
 * \overrightarrow{f} =
 * \begin{pmatrix}
 *     \rho u \\ \rho u^2 + p \\ \rho u v \\ \rho u H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_1 \\ \frac{m_1^2}{\rho} + p \\ \frac{m_1 m_2}{\rho} \\ \frac{m_1 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{f}_{m_2} = \frac{m_1 m_2}{\rho} \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_1 \in (-\infty, \infty)\f$,
 *      \f$m_2 \in (-\infty, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_x_m2(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 m2);

/**
 * @brief x-direction flux for the energy equation.
 *
 * \f[
 * \overrightarrow{f} =
 * \begin{pmatrix}
 *     \rho u \\ \rho u^2 + p \\ \rho u v \\ \rho u H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_1 \\ \frac{m_1^2}{\rho} + p \\ \frac{m_1 m_2}{\rho} \\ \frac{m_1 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{f}_{e} = \frac{m_1 (e + p)}{\rho} \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_1 \in (-\infty, \infty)\f$,
 *      \f$e \in (0, \infty)\f$, \f$p \in (0, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_x_e(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                     const EF_SimdF64 e, cosnt EF_SimdF64 p);

/**
 * @brief y-direction flux for the mass equation.
 *
 * Flux vector:
 * \f[
 * \overrightarrow{g} =
 * \begin{pmatrix}
 *     \rho v \\ \rho u v \\ \rho v^2 + p \\ \rho v H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_2 \\ \frac{m_1 m_2}{\rho} \\ \frac{m_2^2}{\rho} + p \\ \frac{m_2 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{g}_{\rho} = m_2 \f]
 *
 * @pre \f$m_2 \in (-\infty, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_y_rho(const EF_SimdF64 m2);

/**
 * @brief y-direction flux for the x-momentum equation.
 *
 * Flux vector:
 * \f[
 * \overrightarrow{g} =
 * \begin{pmatrix}
 *     \rho v \\ \rho u v \\ \rho v^2 + p \\ \rho v H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_2 \\ \frac{m_1 m_2}{\rho} \\ \frac{m_2^2}{\rho} + p \\ \frac{m_2 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{g}_{\m_1} = \frac{m_1 m_2}{\rho} \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_1 \in (-\infty, \infty)\f$,
 *      \f$m_2 \in (-\infty, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_y_m1(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 m2);

/**
 * @brief y-direction flux for the y-momentum equation.
 *
 * Flux vector:
 * \f[
 * \overrightarrow{g} =
 * \begin{pmatrix}
 *     \rho v \\ \rho u v \\ \rho v^2 + p \\ \rho v H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_2 \\ \frac{m_1 m_2}{\rho} \\ \frac{m_2^2}{\rho} + p \\ \frac{m_2 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{g}_{\m_2} = \frac{m_2^2}{\rho} + p \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_2 \in (-\infty, \infty)\f$,
 *      \f$p \in (0, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_y_m2(const EF_SimdF64 rho, const EF_SimdF64 m2,
                                      const EF_SimdF64 p);

/**
 * @brief y-direction flux for the energy equation.
 *
 * Flux vector:
 * \f[
 * \overrightarrow{g} =
 * \begin{pmatrix}
 *     \rho v \\ \rho u v \\ \rho v^2 + p \\ \rho v H
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *     m_2 \\ \frac{m_1 m_2}{\rho} \\ \frac{m_2^2}{\rho} + p \\ \frac{m_2 (e +
 * p)}{\rho}
 * \end{pmatrix}
 * \f]
 *
 * \f[ \overrightarrow{g}_{e} = \frac{m_2 (e + p)}{\rho} \f]
 *
 * @pre \f$\rho \in (0, \infty)\f$, \f$m_2 \in (-\infty, \infty)\f$,
 *      \f$e \in (0, \infty)\f$, \f$p \in (0, \infty)\f$
 */
static inline EF_SimdF64 ef_flux_y_e(const EF_SimdF64 rho, const EF_SimdF64 m2,
                                     const EF_SimdF64 e, const EF_SimdF64 p);

/* --- Definitions --- */

static inline EF_SimdF64 ef_flux_x_rho(const EF_SimdF64 m1)
{
    assert(ef_simd_all_finite_f64(m1));

    return EF_SimdF64 m1;
}

static inline EF_SimdF64 ef_flux_x_m1(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 p)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m1));
    assert(ef_simd_all_positive_finite_f64(p));

    return ef_simd_add_f64(ef_simd_div_f64(ef_simd_mul_f64(m1, m1), rho), p);
}

static inline EF_SimdF64 ef_flux_x_m2(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 m2)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m1));
    assert(ef_simd_all_finite_f64(m2));

    return ef_simd_div_f64(ef_simd_mul_f64(m1, m2), rho);
}

static inline EF_SimdF64 ef_flux_x_e(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                     cosnt EF_SimdF64 e, const EF_SimdF64 p)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m1));
    assert(ef_simd_all_positive_finite_f64(e));
    assert(ef_simd_all_positive_finite_f64(p));

    return ef_simd_div_f64(ef_simd_mul_f64(m1, ef_simd_add_f64(e, p)), rho);
}

static inline EF_SimdF64 ef_flux_y_rho(const EF_SimdF64 m2)
{
    assert(ef_simd_all_finite_f64(m2));

    return EF_SimdF64 m2;
}

static inline EF_SimdF64 ef_flux_y_m1(const EF_SimdF64 rho, const EF_SimdF64 m1,
                                      const EF_SimdF64 m2)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m1));
    assert(ef_simd_all_finite_f64(m2));

    return ef_simd_div_f64(ef_simd_mul_f64(m1, m2), rho);
}

static inline EF_SimdF64 ef_flux_y_m2(const EF_SimdF64 rho, const EF_SimdF64 m2,
                                      const EF_SimdF64 p)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m2));
    assert(ef_simd_all_positive_finite_f64(p));

    return ef_simd_add_f64(ef_simd_div_f64(ef_simd_mul_f64(m2, m2), rho), p);
}

static inline EF_SimdF64 ef_flux_y_e(const EF_SimdF64 rho, const EF_SimdF64 m2,
                                     cosnt EF_SimdF64 e, const EF_SimdF64 p)
{
    assert(ef_simd_all_positive_finite_f64(rho));
    assert(ef_simd_all_finite_f64(m2));
    assert(ef_simd_all_positive_finite_f64(e));
    assert(ef_simd_all_positive_finite_f64(p));

    return ef_simd_div_f64(ef_simd_mul_f64(m2, ef_simd_add_f64(e, p)), rho);
}
