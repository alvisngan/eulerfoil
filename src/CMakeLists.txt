add_library(eulerfoil STATIC
    state.c)

target_include_directories(eulerfoil PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eulerfoil PRIVATE eulerfoil_flags)

add_executable(eulerfoil_app main.c)
target_link_libraries(eulerfoil_app PRIVATE eulerfoil eulerfoil_flags)
