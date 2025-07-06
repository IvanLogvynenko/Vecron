cmake_minimum_required(VERSION 4.0.0)
project(module VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(module
	SHARED main.cpp
)
