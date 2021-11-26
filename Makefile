CPP		:= g++

SRC		:= src
BIN		:= build

INCLUDE	:= $(shell find $(SRC) -type d | xargs printf '\-I %s ')
SRCS	:= $(shell find . -name '*.cpp')

CXXFLAGS += -std=c++17 -stdlib=libc++ $(INCLUDE) -Wall -O3


run: build
	@build/main

build: $(SRCS)
	mkdir -p build
	$(CPP) $^ $(CXXFLAGS) -o $(BIN)/$@

clean:
	rm -rf $(BIN)
