cmake_minimum_required(VERSION 4.0.0)
project(vecron VERSION 0.0.1 LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/defaults.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
	add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
	add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(common)

set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nlohmann_json 3.12.0 REQUIRED)

file(GLOB CPP_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*/*.cpp")
add_executable(vecron
	src/main.cpp

	${CPP_FILES}
)

target_include_directories(vecron PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(vecron PRIVATE ${DEFAULT_COMPILE_OPTIONS})
target_compile_definitions(vecron PRIVATE ENABLE_DESCRIPTION_DETECTION)
target_link_libraries(vecron PRIVATE vecron_common nlohmann_json::nlohmann_json)
target_include_directories(vecron PRIVATE luajit/src)
target_link_libraries(vecron PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a dl)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(vecron PRIVATE -O3 -DNDEBUG)
endif()

install(TARGETS vecron DESTINATION bin)

