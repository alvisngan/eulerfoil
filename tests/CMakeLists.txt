add_subdirectory(${PROJECT_SOURCE_DIR}/external/Unity
                 ${CMAKE_CURRENT_BINARY_DIR}/Unity)

# Enables Unity TEST_ASSERT_DOUBLE_*
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_DOUBLE)

add_library(helpers STATIC helpers.c)
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test only flags
add_library(eulerfoil_test_flags INTERFACE)
target_compile_options(eulerfoil_test_flags INTERFACE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-missing-prototypes>)

# add_unity_test(<name>): builds <name>.c into a CTest case named <name>.
function(add_unity_test name)
    add_executable(${name} ${name}.c)
    target_link_libraries(${name} PRIVATE
        eulerfoil eulerfoil_test_flags unity helpers)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# --- Add tests ---
add_unity_test(test_simd)
add_unity_test(test_compat)
