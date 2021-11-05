.PHONY: build

all: build

build:
	mkdir -p build && cd build && cmake -GNinja .. && ninja
