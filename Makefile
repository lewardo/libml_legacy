CPP			:= g++-11

SRC			:= src
BIN			?= build
EXE			:= $(BIN)/main
OBJ			:= $(BIN)/obj
DEPS		:= $(BIN)/deps

SRCS		:= $(shell find . -name '*.cpp')
VPATH		:= $(dir $(SRCS))
OBJS		:= $(patsubst %.cpp, $(OBJ)/%.o, $(notdir $(SRCS)))
INCLUDE		:= $(shell find $(SRC) -type d | xargs printf '\-I%s ' | xargs)

STD 		?= c++2a
OPTIMISE	?= 0

CXXFLAGS 	+= -std=$(STD) -pedantic -Wall -O$(OPTIMISE) $(INCLUDE)
LDFLAGS  	+= -lm

MULTILINE 	?= 1

ifndef ECHO
HIT_N       ?= 0
HIT_TOTAL	 = $(eval HIT_TOTAL := $$(shell ECHO="HIT_MARK" $(MAKE) $(MAKECMDGOALS) --dry-run | grep -c "HIT_MARK"))$(HIT_TOTAL)
HIT_COUNT    = $(eval HIT_N = $(shell expr $(HIT_N) + 1))$(HIT_N)

ifneq ($(MULTILINE),0)
EOL       	:= \\n
else
RESET     	:= \033[2K\r
endif

ECHO       	 = printf "$(RESET)\033[2;35m[$(HIT_COUNT)/$(HIT_TOTAL)]\033[22m %b\033[39m$(EOL)"
endif

.PHONY: all run exec build rebuild clear remove
.SILENT:

all: clean build
	$(ECHO) "running \033[4m$(EXE)\033[0m:"
	$(EXE)

build: $(EXE)

rebuild: clean $(EXE)

run: build
	$(ECHO) "running \033[4m$(EXE)\033[0m:"
	$(EXE)

$(EXE): $(OBJS) | $(OBJ)
	$(ECHO) "linking \033[4m$@\033[0m"
	$(CPP) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o: %.cpp | $(OBJ) $(DEPS)
	$(ECHO) "building \033[4m$@\033[0m"
	$(CPP) $(CXXFLAGS) -c -MMD -MF $(DEPS)/$(shell echo $@ | xargs -L 1 basename | sed 's/o$$/d/') $< -o $@

$(BIN) $(OBJ) $(DEPS):
	mkdir -p $@

clean: remove
	$(ECHO) "cleaning"
	[ ! -d $(BIN)_ ] || rm -rf $(BIN)_

remove:
	[ ! -d $(BIN) ] || mv $(BIN) $(BIN)_

-include $(DEPS)/*.d
