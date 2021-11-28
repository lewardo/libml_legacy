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


.PHONY: all clean cosm

all: $(EXE)
	@echo "=== running ==="
	@$<

$(EXE): $(OBJS) | $(BIN) $(OBJ)
	@echo "=== linking $@ ==="
	$(CPP) $(LDFLAGS) $^ -o $@

.SECONDEXPANSION:
source = $(shell find . -type f | grep -m 1 $*.cpp)

$(OBJ)/%.o: $${source} | $(OBJ) cosm
	@$(CPP) -c $< $(CXXFLAGS) -o $@

$(BIN) $(OBJ):
	@mkdir -p $@

clean:
	@echo "=== cleaning ==="
	@rm -rf $(BIN)

cosm:
	@echo "=== building ==="
