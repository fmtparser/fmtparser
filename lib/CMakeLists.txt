# fmtparser library build script
# Author: Maxim Menshikov (maxim@menshikov.org)
cmake_minimum_required(VERSION 3.16)

project(fmt_parser)

if (ENABLE_STATIC)
	set(FMT_PARSER_LIB_MODE STATIC)
else ()
	set(FMT_PARSER_LIB_MODE SHARED)
endif ()

add_library(${PROJECT_NAME} ${FMT_PARSER_LIB_MODE}
			src/parser.c
			src/util.c)

if (ENABLE_SPEC_API)
	target_sources(${PROJECT_NAME} PUBLIC src/spec_api.c)
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
if (CHAR_TYPE)
	target_compile_definitions(${PROJECT_NAME} PUBLIC FMT_CHAR_TYPE=${CHAR_TYPE})
endif ()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE FMT_DEBUG=1)
    target_compile_options(${PROJECT_NAME} PUBLIC -g)
endif ()

if (WIN32 AND NOT ENABLE_STATIC)
    set(DST_PATH bin)
else ()
    set(DST_PATH lib)
endif ()
install(TARGETS ${PROJECT_NAME}
        RUNTIME
        DESTINATION ${DST_PATH}
        COMPONENT development)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING
            PATTERN "*.h"
            PATTERN "*.def")
