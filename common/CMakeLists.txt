set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(vecron_common PRIVATE -O3 -DNDEBUG)
endif()

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(vecron_common STATIC ${CPP_FILES})

target_include_directories(vecron_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(vecron_common PRIVATE ${DEFAULT_COMPILE_OPTIONS})
target_compile_options(vecron_common PRIVATE ${DEFAULT_COMPILE_OPTIMIZATION})
target_compile_definitions(vecron_common PRIVATE ENABLE_DESCRIPTION_DETECTION)
