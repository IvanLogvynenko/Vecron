cmake_minimum_required(VERSION 4.0.0)
project(vecron VERSION 0.0.1 LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/defaults.cmake)

add_subdirectory(common)

set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Enable sanitizers if supported
# option(ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" ON)
#
# if (ENABLE_SANITIZERS)
#     set(SANITIZER_FLAGS "-fsanitize=leak,undefined -fno-omit-frame-pointer")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
#     set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${SANITIZER_FLAGS}")
# endif()
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB CPP_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*/*.cpp")

add_executable(main 
	src/main.cpp

	${CPP_FILES}
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(main PRIVATE ${DEFAULT_COMPILE_OPTIONS})
# target_compile_options(main PRIVATE ${DEFAULT_COMPILE_OPTIMIZATION})
target_compile_definitions(main PRIVATE ENABLE_DESCRIPTION_DETECTION)
target_link_libraries(main PRIVATE common)

