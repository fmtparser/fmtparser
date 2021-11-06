# fmtparser

![Build](https://github.com/fmtparser/fmtparser/actions/workflows/build.yml/badge.svg)
![Test](https://github.com/fmtparser/fmtparser/actions/workflows/test.yml/badge.svg)

A trivial printf/scanf format parser, which can be useful when analyzing format strings or making compilers.

The tool is shipped as a static (or shared) library.

## Building
The project is based on CMake, so use a typical CMake approach:

	mkdir -p build && cd build
	cmake -GNinja ..

There is also a ``Makefile`` wrapper around CMake, so it is possible to use ``make`` on *nix based distributions.

## Contribute
This project is created in spare time. We welcome all contributions including, but not limited to parser, documentation, test improvements, etc.

## License
MIT
