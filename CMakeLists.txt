# Main fmtparser's build script
# Author: Maxim Menshikov (maxim@menshikov.org)
cmake_minimum_required(VERSION 3.16)

project(fmt_reader_main)

option(CHAR_TYPE "Default char type" "char")
option(ENABLE_STATIC "Enable static build" ON)
option(ENABLE_TEST "Enable tests" OFF)
option(ENABLE_SPEC_API "Enable specifier API" ON)

add_subdirectory(lib)

if (ENABLE_TEST)
	include(deps/gtest.cmake)
	add_subdirectory(unittest)
endif ()

find_package(Doxygen)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen.config.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
