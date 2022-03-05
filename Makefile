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

ifndef ECHO
HIT_N			?= 0
HIT_TOTAL := $(shell ECHO="HIT_MARK" $(MAKE) $(MAKECMDGOALS) --dry-run | grep -c "HIT_MARK")
HIT_COUNT = $(eval HIT_N = $(shell expr $(HIT_N) + 1))$(HIT_N)
ECHO = echo "[$(HIT_COUNT)/$(HIT_TOTAL)]"
endif

.PHONY: all run build rebuild clean
.SILENT:

all: clean build
	$(EXE)

build: $(EXE)

rebuild: clean build

run: build
	$(EXE)

$(EXE): $(OBJS) | $(OBJ)
	$(ECHO) "linking $@..."
	$(CPP) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o: %.cpp | $(OBJ) $(DEPS)
	$(ECHO) "building $@..."
	$(CPP) $(CXXFLAGS) -c -MMD -MF $(DEPS)/$(shell echo $@ | xargs -L 1 basename | sed 's/o$$/d/') $< -o $@

$(OBJ) $(DEPS):
	mkdir -p $@

clean:
	$(ECHO) "cleaning..."
	rm -rf $(BIN)

-include $(DEPS)/*.d
