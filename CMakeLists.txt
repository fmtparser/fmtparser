cmake_minimum_required(VERSION 3.16)

project(fmt_reader_main)

option(CHAR_TYPE "Default char type" "char")
option(ENABLE_STATIC "Enable static build" ON)
option(ENABLE_TEST "Enable tests" OFF)

add_subdirectory(lib)

if (ENABLE_TEST)
	include(deps/gtest.cmake)
	add_subdirectory(unittest)
endif ()