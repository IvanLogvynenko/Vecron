# cmake/defaults.cmake

# C++ standard and compile options

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(DEFAULT_CXX_STANDARD 23)
set(DEFAULT_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic" "-Wconversion" "-g")

set(DEFAULT_COMPILE_OPTIMIZATION "-O3")
