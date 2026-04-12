# fmtparser

![Build and Test](https://github.com/fmtparser/fmtparser/actions/workflows/build.yml/badge.svg)

A trivial printf/scanf format parser, which can be useful when analyzing format strings or making compilers.

The tool is shipped as a static (or shared) library.

## Building

Use the provided build script:

	./tools/run_make.sh

Cross-compilation targets:
- Linux: `./tools/run_make.sh --linux`
- Windows: `./tools/run_make.sh --win32`
- macOS x86_64: `./tools/run_make.sh --mac-x86_64`
- macOS ARM64: `./tools/run_make.sh --mac-arm64`

The project is based on CMake, so a manual build is also possible:

	mkdir -p build && cd build
	cmake -GNinja -DENABLE_TEST=ON -DENABLE_STATIC=ON ..
	ninja

## Testing

Tests are built automatically by `run_make.sh` and can be run with:

	./build/unittest/fmtreader_test

To produce an XML report:

	./build/unittest/fmtreader_test --gtest_output=xml:test-results.xml

## Contribute
This project is created in spare time. We welcome all contributions including, but not limited to parser, documentation, test improvements, etc.

## License
MIT