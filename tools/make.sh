#!/bin/bash
export TOP_DIR="$(cd "$(dirname "$(which "$0")")"/.. ; pwd -P)"

build_folder="build"
toolchain=
release_type="Debug"
include_tests=

while test -n "$1" ; do
    case $1 in
        --win32)
            is_win32=1
            build_folder="build-win32"
            toolchain="-DCMAKE_TOOLCHAIN_FILE=$(pwd)/toolchain/Toolchain-cross-mingw32-linux.cmake"
            ;;
        --release)
            release_type="Release"
            ;;
        --test)
			include_tests="-DENABLE_TEST=ON"
			;;
    esac
    shift 1
done

pushd ${TOP_DIR} > /dev/null
mkdir -p ${build_folder}
pushd ${build_folder} > /dev/null
cmake -GNinja \
	  ${include_tests:+${include_tests}} \
	  -DCMAKE_BUILD_TYPE=${release_type} \
	  -DENABLE_STATIC=ON \
	  ${toolchain:+${toolchain}} \
	  ..
ninja
popd > /dev/null
popd > /dev/null

