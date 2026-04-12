# CMake toolchain file for cross-compiling to Windows using llvm-mingw with UCRT
# This toolchain uses the llvm-mingw toolchain downloaded by run_make.sh,
# which provides modern MinGW with Universal C Runtime (UCRT) support.

# Target operating system
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_CROSSCOMPILING TRUE)

# Platform definitions
set(EQUID_PLATFORM_WIN32 BOOL:ON)
add_definitions(-D__USE_MINGW_ANSI_STDIO=1 -D_WIN32_WINNT=0x0601)

# Compiler prefix for llvm-mingw
set(COMPILER_PREFIX "x86_64-w64-mingw32")

# Compilers - use llvm-mingw wrappers from PATH (set by run_make.sh)
# These wrappers automatically set the correct target and sysroot
set(CMAKE_C_COMPILER ${COMPILER_PREFIX}-clang)
set(CMAKE_CXX_COMPILER ${COMPILER_PREFIX}-clang++)
set(CMAKE_RC_COMPILER ${COMPILER_PREFIX}-windres)

# Use LLVM tools for better compatibility
set(CMAKE_AR llvm-ar)
set(CMAKE_RANLIB llvm-ranlib)
set(CMAKE_NM llvm-nm)
set(CMAKE_OBJCOPY llvm-objcopy)
set(CMAKE_OBJDUMP llvm-objdump)
set(CMAKE_STRIP llvm-strip)

# Use LLD linker (part of LLVM, faster than GNU ld)
set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "" FORCE)

# Search for programs, libraries, and headers in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)