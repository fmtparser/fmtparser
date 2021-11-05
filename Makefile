.PHONY: build

all: build

build:
	mkdir -p build && cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DENABLE_STATIC=ON .. && ninja
