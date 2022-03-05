CPP				:= g++

SRC				:= ./src
BIN				:= ./build
EXE				:= $(BIN)/main
OBJ				:= $(BIN)/obj
DEPS			:= $(BIN)/deps

SRCS			:= $(shell find . -name '*.cpp')
VPATH			:= $(dir $(SRCS))
OBJS			:= $(patsubst %.cpp, $(OBJ)/%.o, $(notdir $(SRCS)))
INCLUDE		:= $(shell find $(SRC) -type d | xargs printf '\-I%s ' | xargs)

CXXFLAGS 	+= -std=c++1z -pedantic -Wall -O3 $(INCLUDE)
LDFLAGS  	+= -lm

MULTILINE ?= 0

ifndef ECHO
HIT_N     ?= 0
HIT_TOTAL	 = $(eval HIT_TOTAL := $$(shell ECHO="HIT_MARK" $(MAKE) $(MAKECMDGOALS) --dry-run | grep -c "HIT_MARK"))$(HIT_TOTAL)
HIT_COUNT  = $(eval HIT_N = $(shell expr $(HIT_N) + 1))$(HIT_N)

ifneq ($(MULTILINE),0)
EOL       := \\n
else
RESET     := \033[2K\r
endif

ENDLINE    = $(shell [[ $(HIT_N) == $(HIT_TOTAL) ]] && echo '$(RESET)$(MAKECMDGOALS) successful\\n')

ECHO       = printf "$(RESET)[$(HIT_COUNT)/$(HIT_TOTAL)] %s$(EOL)$(ENDLINE)"
endif

.PHONY: all run exec build rebuild clear remove
.SILENT:

all: clean build
	$(EXE)

build: $(EXE)

rebuild: clean $(EXE)

exec run: build
	$(EXE)

$(EXE): $(OBJS) | $(OBJ)
	$(ECHO) "linking $@..."
	$(CPP) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o: %.cpp | $(OBJ) $(DEPS)
	$(ECHO) "building $@..."
	$(CPP) $(CXXFLAGS) -c -MMD -MF $(DEPS)/$(shell echo $@ | xargs -L 1 basename | sed 's/o$$/d/') $< -o $@

$(BIN) $(OBJ) $(DEPS):
	mkdir -p $@

clean: remove
	$(ECHO) "cleaning..."
	[ ! -d $(BIN)_ ] || rm -rf $(BIN)_

remove:
	[ ! -d $(BIN) ] || mv $(BIN) $(BIN)_

-include $(DEPS)/*.d
