#!/bin/bash

export TOP_DIR="$(cd "$(dirname "$(which "$0")")"/.. ; pwd -P)"

pushd ${TOP_DIR} > /dev/null
for test in `ls test_suite` ; do
	./build/test/fmtreader_test < ./test_suite/$test
	if [ "$?" != "0" ] ; then
		echo "Test $test failed"
		exit 1
	fi
done
popd > /dev/null