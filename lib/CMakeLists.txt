cmake_minimum_required(VERSION 3.16)

project(fmt_parser)

add_library(${PROJECT_NAME} SHARED src/parser.c src/util.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PUBLIC -g)