########################################################################
####################### Makefile for Compiling main.c ##################
########################################################################
# Compiler settings - Can be customized.
CC = gcc                            # Compiler to use
CXXFLAGS = -std=c99 -Wall -I include  # Compilation flags: 
                                      # -std=c11: Use C11 standard
                                      # -Wall: Enable all warnings
                                      # -I include: Include path for header files
LDFLAGS =                           # Linker flags (currently empty)

# Makefile settings - Can be customized.
APPNAME = build/program              # Output executable name (located in build directory)
SRC = src/main.c                     # Source file to compile (main.c)
OBJ = build/main.o                   # Object file for main.c

# UNIX-based OS variables & settings
RM = rm                              # Command to remove files/directories

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)                      # Default target to build the application

# Builds the application
$(APPNAME): $(OBJ)                   # Target to create the executable from object files
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)  # Compile the object files into the executable

# Building rule for .o files from main.c
build/main.o: src/main.c             # Target to compile main.c into an object file
	@mkdir -p build                  # Ensure the build directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<    # Compile main.c to main.o, creating the object file

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean                        # Declares clean as a phony target (not a file)
clean:                               # Target to clean up the build
	$(RM) -rf build $(APPNAME)      # Remove the build directory and executable
