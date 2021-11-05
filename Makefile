.PHONY: build

all: build

build:
	mkdir -p build && cd build && cmake -GNinja -DENABLE_TEST=ON -DCMAKE_BUILD_TYPE=Debug -DENABLE_STATIC=ON .. && ninja
