cmake_minimum_required(VERSION 3.17)

project(Process)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CONFIG:DEBUG>:-O0>")
add_compile_options("$<$<CONFIG:RELEASE>:-O3>")

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(lib)