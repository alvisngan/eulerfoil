# TODO: when the src/ is populated with .c files
#   - change add_library() keyword to STATIC
#   - change target_include_directories keyword to PUBLIC
#   - change target_link_libraries keyword to PRIVATE

add_library(eulerfoil INTERFACE)

target_include_directories(eulerfoil INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eulerfoil INTERFACE eulerfoil_flags)

#add_executable(eulerfoil_app main.c)
#target_link_libraries(eulerfoil_app PRIVATE eulerfoil eulerfoil_flags)
