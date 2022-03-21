############################################
##### c++ library development Makefile #####
############################################


#### environment variables ####

### compiler/linker and archiver ###
# compiler/linker
CPP				:= g++-11
# archiver
AR				:= ar

### directory names ###
# source code directory
SRCDIR			?= ./src
# development build directory
BUILDDIR		:= ./build
# install library directory (change to /usr/local/lib)
ILIBDIR			?= ./lib
# install library includes' directory (change to /usr/local/include)
IINCDIR			?= ./include
# object file directory
OBJDIR			:= $(BUILDDIR)/obj
# dependency file directory
DEPDIR			:= $(BUILDDIR)/deps

### file names ###
# name of built development executable
EXE				:= $(BUILDDIR)/main
# library header, tries to find {{foldername}}.h, otherwise picks first top-level header
LIBHDR			:= $(notdir $(shell find . -depth 1 -name $(notdir $(CURDIR)).h | grep . || find . -depth 1 -name '*.h' | head -n 1))
# enclosing folder name for library name
LIBNAME			?= $(notdir $(CURDIR))

### file lists ###
# source files
SRCS			:= $(shell find $(SRCDIR) -name '*.cpp')
# sources' respective object files
OBJS			:= $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRCS)))
# header files to be included
HDRS			:= $(shell find $(SRCDIR) -name '*.h')

### path variables for make and the compiler respectively ###
# to shorten .o target dependencies
VPATH			:= $(dir $(SRCS))
# all paths in src directory to shorten includes
export CPATH	:= $(shell find $(SRCDIR) -type d | tr '\n' ':' | sed 's/:$$//')

### command line parameters to change behaviour ###
# c++ version
STD 			?= c++2a
# optimisation level
OPTIMISE		?= 0
# printing style
MULTILINE 		?= 1

### compiler/linker flags ###
# compiler flags, with options
CXXFLAGS 		+= -std=$(STD) -Wall -Werror -O$(OPTIMISE)
# linker flags, link libmath
LDFLAGS  		+= -lm


#### progress indication ####

ifndef ECHO
### variables ###
# count variable
N		       	 = 0
# lazily evaluated once, to allow file deletions/moves before target count
TOTAL			 = $(eval TOTAL := $$(shell ECHO="MARK" $(MAKE) $(MAKECMDGOALS) --dry-run | grep -c "MARK"))$(TOTAL)
# variable that updates every time called
COUNT		   	 = $(eval N = $(shell expr $N + 1))$N

### printing style ###
ifneq ($(MULTILINE),0)
# default, newline as EOL
EOL       		:= \\n
else
# otherwise clear line and carriage return
RESET     		:= \033[2K\r
endif

# set echo variable with colours
ECHO       		 = printf "$(RESET)\033[2;35m[$(COUNT)/$(TOTAL)]\033[22m %b\033[39m$(EOL)"
# same as echo but do not count in job list
NOPECHO			 = printf "$(RESET)\033[2;35m\033[22m%b\033[39m$(EOL)"
endif


#### targets ####

### target attributes ###
# phony targets [all, run, build, rebuild, dev, clear] for development, [install, uninstall] for installation
.PHONY: all build rebuild run install uninstall clear _move _includes
# run all following targets silently
.SILENT:

### targets ###
# clean build directory, compile and link executable, and run
all: clean run

# build executable
build: $(EXE)

# clean build directory
rebuild: clean $(EXE)

# build executable and run
run: $(EXE)
	$(ECHO) "running \033[4m$^\033[0m:"
	$(EXE)

# install libraries to directoies 
install: $(LIBNAME).a $(LIBNAME).so _includes
	$(NOPECHO) "$(LIBNAME) successfully installed"

# remove libraries and includes, delete directories if empty
uninstall:
	$(ECHO) "uninstalling $(ILIBDIR)/$(LIBNAME) shared and static libraries"
	[ ! -f $(ILIBDIR)/$(LIBNAME).a ] || rm $(ILIBDIR)/$(LIBNAME).a
	[ ! -f $(ILIBDIR)/$(LIBNAME).so ] || rm $(ILIBDIR)/$(LIBNAME).so
	[ ! -z "$$(ls -A $(ILIBDIR))" ] || rmdir $(ILIBDIR)
	
	$(ECHO) "uninstalling $(IINCDIR)/$(LIBHDR) and corresponding includes"
	[ ! -f $(IINCDIR)/$(LIBHDR) ] || rm $(IINCDIR)/$(LIBHDR)
	[ ! -d $(IINCDIR)/$(LIBNAME) ] || rm -rf $(IINCDIR)/$(LIBNAME)
	[ ! -z "$$(ls -A $(IINCDIR))" ] || rmdir $(IINCDIR)

# delete build directory
clean: _move
	$(ECHO) "cleaning"
	[ ! -d $(BUILDDIR)_ ] || rm -rf $(BUILDDIR)_

# development executable from object files
$(EXE): $(OBJS) $(OBJDIR)/main.o
	$(ECHO) "linking \033[4m$@\033[0m"
	$(CPP) $(LDFLAGS) -o $@ $^

# object file from corresponding source file
$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(DEPDIR)
	$(ECHO) "building \033[4m$@\033[0m"
	$(CPP) $(CXXFLAGS) -c -fPIC -MMD -MF $(DEPDIR)/$(shell echo $@ | xargs -L 1 basename | sed 's/o$$/d/') -o $@ $<

# static archive library creation
$(LIBNAME).a: $(OBJS) | $(ILIBDIR)
	$(ECHO) "generating static library archive $(LIBNAME).a"
	$(AR) rcs $(ILIBDIR)/$@ $^

# shared library creation
$(LIBNAME).so: $(OBJS) | $(ILIBDIR)
	$(ECHO) "generating shared library $(LIBNAME).so"
	$(CPP) -shared -o $(ILIBDIR)/$@ $^

# directory creation
$(BUILDDIR) $(OBJDIR) $(DEPDIR) $(ILIBDIR) $(IINCDIR) $(IINCDIR)/$(LIBNAME):
	mkdir -p $@

# move the build directory so the target couting works properly
_move:
	[ ! -d $(BUILDDIR) ] || mv $(BUILDDIR){,_}

# copy include headers in includepath
_includes: $(HDRS) | $(IINCDIR) $(IINCDIR)/$(LIBNAME)
	$(ECHO) "moving headers to $(IINCDIR)/$(LIBNAME)"
	cp $(LIBHDR) $(IINCDIR)
	cp $^ $(IINCDIR)/$(LIBNAME)

# include source dependecies to recompile when changed
-include $(DEPDIR)/*.d
