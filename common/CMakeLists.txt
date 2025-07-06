set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(common STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/util/process.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/split.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_prompt.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/multiselect.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/bind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/cycle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/header.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/height.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/infoPosition.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/pattern.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/prompt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/reverse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fzf/fzf_modes/style.cpp
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(common PRIVATE ${DEFAULT_COMPILE_OPTIONS})
target_compile_options(common PRIVATE ${DEFAULT_COMPILE_OPTIMIZATION})
target_compile_definitions(common PRIVATE ENABLE_DESCRIPTION_DETECTION)
