#ifndef EULERFOIL_SIMD_H
#define EULERFOIL_SIMD_H

/*
 * MSVC does not define __FMA__, but if __AVX2__ is defined it must
 * contain FMA extensions.
 *
 * https://learn.microsoft.com/en-us/cpp/build/reference/arch-x86?view=msvc-170
 */
#if defined(__AVX2__) && (defined(__FMA__) || defined(_MSC_VER))
#include "eulerfoil/simd/avx2.h"
#else
#include "eulerfoil/simd/scalar.h"
#endif

#endif
