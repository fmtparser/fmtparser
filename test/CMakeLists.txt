cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(fmtreader_demo_001)

add_executable(${PROJECT_NAME} demo_001.c)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt_parser)