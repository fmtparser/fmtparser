# fmtparser

![Build and Test](https://github.com/fmtparser/fmtparser/actions/workflows/build.yml/badge.svg)

A trivial printf/scanf format parser, which can be useful when analyzing format strings or making compilers.

The tool is shipped as a static (or shared) library.

## Building

### Quick build (recommended)
Use the provided build script that supports cross-compilation:

	./tools/run_make.sh

For cross-compilation:
- Linux: `./tools/run_make.sh --linux`
- Windows: `./tools/run_make.sh --win32`
- macOS x86_64: `./tools/run_make.sh --mac-x86_64`
- macOS ARM64: `./tools/run_make.sh --mac-arm64`

### Manual CMake build
The project is based on CMake, so you can also use a typical CMake approach:

	mkdir -p build && cd build
	cmake -GNinja -DENABLE_TEST=ON -DENABLE_STATIC=ON ..
	ninja

There is also a `Makefile` wrapper around CMake for *nix based distributions.

## Testing

The project includes unit tests using Google Test. Tests are built automatically when using `run_make.sh`.

### Running tests locally

After building with tests enabled, run:

	./build/unittest/fmtreader_test

For cross-compiled builds:

	# Linux (native)
	./build-linux/unittest/fmtreader_test
	
	# Windows (using Wine)
	wine ./build-win32/unittest/fmtreader_test.exe

### Test output

To generate XML test results:

	./build/unittest/fmtreader_test --gtest_output=xml:test-results.xml

## Contribute
This project is created in spare time. We welcome all contributions including, but not limited to parser, documentation, test improvements, etc.

## License
MIT
