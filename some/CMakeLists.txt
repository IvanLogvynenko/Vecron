cmake_minimum_required(VERSION 3.31)
project({{projectName}} VERSION 0.0.0)

add_compile_options(-std=c++20 -O3)
add_compile_options(-g -Wall -Wextra -Wconversion -Werror)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(main 
    ${SRC_FILES}
)
target_link_options(main PRIVATE -fsanitize=address)
