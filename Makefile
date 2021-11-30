CPP		:= g++

SRC		:= src
BIN		:= build
EXE		:= $(BIN)/main
OBJ		:= $(BIN)/obj

SRCS	:= $(shell find . -name '*.cpp')
OBJS	:= $(shell find . -name '*.cpp' | xargs -L 1 basename | sed 's/cpp$$/o/' | awk '{ print "$(OBJ)/" $$0 }')
INCLUDE	:= $(shell find $(SRC) -type d | xargs printf '\-I%s ' | xargs)

CXXFLAGS += -std=c++17 -pedantic -Wall -O3 $(INCLUDE)
LDFLAGS += -lm

source 	= $(shell find . -type f | grep -m 1 $*.cpp)
done 	:= 0
c 		:= \033[2K\r


.PHONY: all run build clean

all run: build
	@ $(EXE)

build: $(EXE)

$(EXE): $(OBJS) | $(OBJ)
	@ printf "$clinking $@..."
	@ $(CPP) $(LDFLAGS) $^ -o $@
	@ printf "$c"

.SECONDEXPANSION:

$(OBJ)/%.o: $${source} | $(OBJ)
	@ printf "$c[$(done)/$(words $(OBJS))] building $@..."
	@ $(eval done = $(shell echo $$(($(done) + 1))))

	@ $(CPP) -c $< $(CXXFLAGS) -o $@

$(OBJ):
	@ mkdir -p $@

clean:
	@ printf "$ccleaning..."
	@ rm -rf $(BIN)
