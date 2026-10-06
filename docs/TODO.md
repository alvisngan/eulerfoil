# TODO

## Todo

-[ ] Forbidding `-ffast-math` compiler flag
    - Subnormals should be handled with intrinsics
    - fast-math may ignore NaN, which is undesirable

## In Progress


## Done

-[x] NaN handling decision on `ef_simd_max/min` operations
    - Problems
        - `fmax(NaN, x)` and `vmaxq_f64` returns `x`
        - `__mm256_max_pd(NaN, x)` returns the second operand
    - Fix
        - Uses `<math.h>` or IEEE specs as the standard
        - Additional `NaN` checks steps in AVX2 `max/min` operations
