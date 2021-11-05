# Google Test build rules
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)

set(INSTALL_GTEST OFF)
set(USR_DIR_GOOGLETEST ${CMAKE_CURRENT_BINARY_DIR}/usr/googletest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG        "release-1.11.0"
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  SOURCE_DIR "${CMAKE_BINARY_DIR}/googletest"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${USR_DIR_GOOGLETEST} -DCMAKE_PREFIX_PATH=${USR_DIR_GOOGLETEST}
  BUILD_BYPRODUCTS ${USR_DIR_GOOGLETEST}/lib/libgtest.a
)

FetchContent_MakeAvailable(googletest)
