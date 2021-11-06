#!/bin/bash
export TOP_DIR="$(cd "$(dirname "$(which "$0")")"/.. ; pwd -P)"

pushd ${TOP_DIR} > /dev/null

find lib -iname *.h -o -iname *.c | xargs clang-format -i -style=file
find unittest -iname *.hpp -o -iname *.cpp | xargs clang-format -i -style=file

popd > /dev/null
