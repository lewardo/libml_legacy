CPP		:= g++

SRC		:= src
BIN		:= build
EXE		:= $(BIN)/main
OBJ		:= $(BIN)/obj
DEPS	:= $(BIN)/deps

SRCS	:= $(shell find . -name '*.cpp')
VPATH	:= $(dir $(SRCS))
OBJS	:= $(patsubst %.cpp, $(OBJ)/%.o, $(notdir $(SRCS)))
INCLUDE	:= $(shell find $(SRC) -type d | xargs printf '\-I%s ' | xargs)

CXXFLAGS += -std=c++17 -pedantic -Wall -O3 $(INCLUDE)
LDFLAGS += -lm

.PHONY: all run build clean newline
.SILENT:

build: $(EXE)

all run: build
	$(EXE)

$(EXE): $(OBJS) | $(OBJ)
	echo "linking $@..."
	$(CPP) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o: %.cpp | $(OBJ) $(DEPS)
	echo "building $@..."
	$(CPP) $(CXXFLAGS) -c -MMD -MF $(DEPS)/$(shell echo $@ | xargs -L 1 basename | sed 's/o$$/d/') $< -o $@

$(OBJ) $(DEPS):
	mkdir -p $@

clean:
	echo "cleaning..."
	rm -rf $(BIN)

-include $(DEPS)/*.d
