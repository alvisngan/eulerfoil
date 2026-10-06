# TODO

## Todo

-[ ] NaN handling decision on `ef_simd_max/min` operations
    - `fmax(NaN, x)` and `vmaxq_f64` returns `x`
    - `__mm256_max_pd(NaN, x)` returns the second operand

-[ ] Forbidding `-ffast-math` compiler flag
    - Subnormals should be handled with intrinsics
    - fast-math may ignore NaN, which is undesirable

## In Progress


## Done
