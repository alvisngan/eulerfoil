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
EF_SimdF64 ef_pressure(const double gamma, const double EF_SimdF64 rho,
                       const EF_SimdF64 m_1, const EF_SimdF64 m_2,
                       const EF_SimdF64 e);
