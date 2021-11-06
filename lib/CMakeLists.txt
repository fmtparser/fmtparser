cmake_minimum_required(VERSION 3.16)

project(fmt_parser)

if (ENABLE_STATIC)
	set(FMT_PARSER_LIB_MODE STATIC)
else ()
	set(FMT_PARSER_LIB_MODE SHARED)
endif ()

add_library(${PROJECT_NAME} ${FMT_PARSER_LIB_MODE} src/parser.c src/util.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
if (CHAR_TYPE)
	target_compile_definitions(${PROJECT_NAME} PUBLIC FMT_CHAR_TYPE=${CHAR_TYPE})
endif ()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE FMT_DEBUG=1)
    target_compile_options(${PROJECT_NAME} PUBLIC -g)
endif ()