# fmtparser build rules
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(ExternalProject)

set(USR_DIR_FMTPARSER ${CMAKE_CURRENT_BINARY_DIR}/usr/fmtparser)
set(FMTPARSER_LIB_PATH ${USR_DIR_FMTPARSER}/lib/libfmt_parser.a)

if (CMAKE_TOOLCHAIN_FILE)
    set(FMTPARSER_TOOLCHAIN_FILE -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
endif()

if (WIN32_TOOLCHAIN_PATH)
    set(FMTPARSER_WIN32_TOOLCHAIN_PATH -DWIN32_TOOLCHAIN_PATH=${WIN32_TOOLCHAIN_PATH})
endif ()

message("Toolchain: ${FMTPARSER_TOOLCHAIN_FILE}")

ExternalProject_Add(
  fmtparser-stub
  GIT_REPOSITORY    "https://github.com/fmtparser/fmtparser"
  GIT_TAG           "origin/build_improvements"
  UPDATE_COMMAND    ""
  PATCH_COMMAND     ""
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/fmtparser"
  CMAKE_ARGS        -DENABLE_DOCUMENTATION=OFF
                    ${FMTPARSER_TOOLCHAIN_FILE}
                    ${FMTPARSER_WIN32_TOOLCHAIN_PATH}
                    -DCMAKE_INSTALL_PREFIX=${USR_DIR_FMTPARSER}
                    -DCMAKE_PREFIX_PATH=${USR_DIR_FMTPARSER}
  BUILD_BYPRODUCTS  ${FMTPARSER_LIB_PATH}
)

# Import fmtparser library
if (WIN32)
  add_library(fmtparser-imported MODULE IMPORTED)
else ()
  add_library(fmtparser-imported SHARED IMPORTED)
endif ()

# We assume MinGW library
set_property(TARGET fmtparser-imported
             PROPERTY IMPORTED_LOCATION
                ${FMTPARSER_LIB_PATH})
add_dependencies(fmtparser-imported fmtparser-stub)

# Add fmt_parser interace library
add_library(fmt_parser INTERFACE)
target_link_libraries(fmt_parser INTERFACE fmtparser-imported)
target_include_directories(fmt_parser INTERFACE ${USR_DIR_FMTPARSER}/include)


