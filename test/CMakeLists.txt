cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(fmtreader_test)

add_executable(${PROJECT_NAME} test.c)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt_parser)