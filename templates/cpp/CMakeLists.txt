cmake_minimum_required(VERSION 3.31)
project({{ProjectName}} VERSION 0.0.0)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

add_compile_options(-std=c++20 -O3)
add_compile_options(-g -Wall -Wextra -Wconversion -Werror)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(main 
    ${SRC_FILES}
)
target_link_options(main PRIVATE -fsanitize=address)