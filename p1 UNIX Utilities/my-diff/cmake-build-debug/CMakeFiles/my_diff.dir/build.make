# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangkoukou/Desktop/cs537/my-diff

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/my_diff.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_diff.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_diff.dir/flags.make

CMakeFiles/my_diff.dir/my-diff.c.o: CMakeFiles/my_diff.dir/flags.make
CMakeFiles/my_diff.dir/my-diff.c.o: ../my-diff.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/my_diff.dir/my-diff.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/my_diff.dir/my-diff.c.o   -c /Users/wangkoukou/Desktop/cs537/my-diff/my-diff.c

CMakeFiles/my_diff.dir/my-diff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/my_diff.dir/my-diff.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/wangkoukou/Desktop/cs537/my-diff/my-diff.c > CMakeFiles/my_diff.dir/my-diff.c.i

CMakeFiles/my_diff.dir/my-diff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/my_diff.dir/my-diff.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/wangkoukou/Desktop/cs537/my-diff/my-diff.c -o CMakeFiles/my_diff.dir/my-diff.c.s

# Object files for target my_diff
my_diff_OBJECTS = \
"CMakeFiles/my_diff.dir/my-diff.c.o"

# External object files for target my_diff
my_diff_EXTERNAL_OBJECTS =

my_diff: CMakeFiles/my_diff.dir/my-diff.c.o
my_diff: CMakeFiles/my_diff.dir/build.make
my_diff: CMakeFiles/my_diff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable my_diff"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_diff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_diff.dir/build: my_diff

.PHONY : CMakeFiles/my_diff.dir/build

CMakeFiles/my_diff.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_diff.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_diff.dir/clean

CMakeFiles/my_diff.dir/depend:
	cd /Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangkoukou/Desktop/cs537/my-diff /Users/wangkoukou/Desktop/cs537/my-diff /Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug /Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug /Users/wangkoukou/Desktop/cs537/my-diff/cmake-build-debug/CMakeFiles/my_diff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_diff.dir/depend
