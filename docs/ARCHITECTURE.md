# Architecture Overview

2D, structured mesh, steady, inviscid, compressible flow solver.
Euler equations, implicit time-stepping, 2nd order JST discretication.

## High-level System Overview

|   | Layer    | Responsibility                              |
| - | -------- | ------------------------------------------- |
| 0 | kernel   | compute the flux on a face                  |
| 1 | stencil  | compute the flux on a cell                  |
| 2 | strip    | run stencil over a contiguous run of cells  |
| 3 | op       | sweep the mesh, dispatch parallel work      |
| 4 | solver   | advance one timestep, check convergence     |


```
eulerfoil
  CMakeLists.txt
  README.txt
  docs/
    ARCHITECTURE.md
    validation.md
    testing.md
  include/
    types.h
    config.h
    simd.h

    layout.h                    # cell indexing, padding, stride size

    mesh.h                      # mesh struct (arena allocation, geometry)
    state.h                     # solution fields and arena allocation
    init.h                      # initial conditions

    solver.h                    # advance one timestep
    io.h                        # mesh load, output, coefficients

    kernels/
      kernels.h                 # umbrella include
      schemes/
        jst.h
      gas_dynamics/
        equation_of_state.h     # pressure, speed of sound
        flux_vectors.h          # Euler equation flux
        spectral_radius.h       # |u·n̂| + c
      bc_primitives/
        wall.h
        farfield.h
        periodic.h
      time_integration/
        cfl_timestep.h          # local CFL condition
        rk.h                    # Runge-Kutta arithmetic
        residual.h
    stencil/
        stencil.h               # umbrella include
        stencil_jst.h
        stencil_cfl_timestep.h
        stencil_bc.h
    strip/
      strip.h                   # umbrella include
      strip_jst.h
      strip_cfl_timestep.h
      strip_rk.h
      strip_bc.h
      strip_residual.h
    ops/
      ops.h
      op_jst.h
      op_cfl_timestep.h
      op_rk.h
      op_bc.h
      op_residual.h
```
