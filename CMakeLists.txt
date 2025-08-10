cmake_minimum_required(VERSION 4.0.0)
project(vecron VERSION 0.0.1 LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/defaults.cmake)

add_subdirectory(common)

set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nlohmann_json 3.12.0 REQUIRED)

file(GLOB CPP_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*/*.cpp")

add_executable(main 
	src/main.cpp

	${CPP_FILES}
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(main PRIVATE ${DEFAULT_COMPILE_OPTIONS})
# target_compile_options(main PRIVATE ${DEFAULT_COMPILE_OPTIMIZATION})
target_compile_definitions(main PRIVATE ENABLE_DESCRIPTION_DETECTION)
target_link_libraries(main PRIVATE vecron_common)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

