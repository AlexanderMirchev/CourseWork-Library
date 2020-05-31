# THIS MAKEFILE IS MADE WITH IDEAS FROM: 
# https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f

################################################################################################

# Files/directories used/created in compilation process

# output binary file
BIN := library.exe

# source directory
SRCDIR := src
# directory for object and dependency files
OBJDIR := obj

# source files
SRCS := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
# object files, auto generated from source files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
# dependency files, auto generated from source files
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

# creates directory for objects and dependency if it does not exist
$(shell mkdir -p $(OBJDIR))

################################################################################################

# Compiler variables and predefined actions

# C++ compiler
CXX := g++

# C++ flags
# -std=c++17 - standard level
CXXFLAGS := -std=c++17
# C/C++ flags
CPPFLAGS := -g -Wall -Wextra -pedantic
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(OBJDIR)/$*.d

# compile C++ source files
COMPILE = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
# link object files to binary
LINK = $(CXX) -o $@
# precompile step to ensure there is a 
# folder ready for newly compiled files
PRECOMPILE = mkdir -p $(@D)

################################################################################################

# Compilation and linking 
all: $(BIN)

# Removes directory for object and dependency files
.PHONY: clean
clean:
	rm -f -r $(OBJDIR)
	rm -f $(BIN)

# Links all object files into the binary
$(BIN): $(OBJS)
	$(LINK) $^

# Compiles source file into obj file while 
# including all dependencies.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE) $<

# Allows creation of dependencies
$(OBJDIR)/%.d: ;

# ################################################################################################