cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(fmtreader_test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt_parser)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)
if (ENABLE_SPEC_API)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_SPEC_API=1)
endif ()