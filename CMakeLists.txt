cmake_minimum_required(VERSION 3.15)
project(eulerfoil C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Compiler options ---
# Warnings and errors
option(EULERFOIL_WERROR "Treat warnings as errors" ON)

set(eulerfoil_warnings_gnu
    -Wall -Wextra -Wconversion
    -Wswitch-default -Wwrite-strings
    -Wstrict-prototypes -Wmissing-prototypes
    -Wpointer-arith -Wshadow -Wfloat-equal
    -Wundef -Wcast-qual -Wcast-align)

set(eulerfoil_warnings_msvc
    /W4             # ~ -Wall -Wextra
    /permissive-)   # standards conformance (catches MSVC-isms)

# Sanitizers
option(EULERFOIL_SANITIZE
       "Build with AddressSanitizer and UndefinedBehaviorSanitizer"
       OFF)

if(EULERFOIL_SANITIZE)
    if(MSVC)
        message(FATAL_ERROR "EULERFOIL_SANITIZE is not supported with MSVC")
    endif()
    add_compile_options(-fsanitize=address,undefined
                        -fno-sanitize-recover=undefined
                        -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()


add_library(eulerfoil_flags INTERFACE)

target_compile_options(eulerfoil_flags INTERFACE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:${eulerfoil_warnings_gnu}>
    $<$<C_COMPILER_ID:MSVC>:${eulerfoil_warnings_msvc}>
    $<$<AND:$<BOOL:${EULERFOIL_WERROR}>,$<C_COMPILER_ID:GNU,Clang,AppleClang>>:-Werror>
    $<$<AND:$<BOOL:${EULERFOIL_WERROR}>,$<C_COMPILER_ID:MSVC>>:/WX>)

# --- Source and testing ---
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
