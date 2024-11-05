########################################################################
####################### Makefile for Compiling main.c ##################
########################################################################

# Compiler settings - Can be customized.
CC = gcc
CXXFLAGS = -std=c11 -Wall -I include  # Include the directory for header files
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = build/program                # Output executable name (in build directory)
SRC = src/main.c                       # Only the main.c file to compile
OBJ = build/main.o                     # Object file for main.c

# UNIX-based OS variables & settings
RM = rm

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Building rule for .o files from main.c
build/main.o: src/main.c
	@mkdir -p build                # Ensure the build directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<  # Compile main.c to main.o

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) -rf build $(APPNAME)      # Remove build directory and executable
