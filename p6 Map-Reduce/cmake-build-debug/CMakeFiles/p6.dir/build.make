# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /Users/wangkoukou/Desktop/cs537/p6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p6.dir/flags.make

CMakeFiles/p6.dir/main.c.o: CMakeFiles/p6.dir/flags.make
CMakeFiles/p6.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/p6.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p6.dir/main.c.o   -c /Users/wangkoukou/Desktop/cs537/p6/main.c

CMakeFiles/p6.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p6.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/wangkoukou/Desktop/cs537/p6/main.c > CMakeFiles/p6.dir/main.c.i

CMakeFiles/p6.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p6.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/wangkoukou/Desktop/cs537/p6/main.c -o CMakeFiles/p6.dir/main.c.s

CMakeFiles/p6.dir/mapreduce.c.o: CMakeFiles/p6.dir/flags.make
CMakeFiles/p6.dir/mapreduce.c.o: ../mapreduce.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/p6.dir/mapreduce.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p6.dir/mapreduce.c.o   -c /Users/wangkoukou/Desktop/cs537/p6/mapreduce.c

CMakeFiles/p6.dir/mapreduce.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p6.dir/mapreduce.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/wangkoukou/Desktop/cs537/p6/mapreduce.c > CMakeFiles/p6.dir/mapreduce.c.i

CMakeFiles/p6.dir/mapreduce.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p6.dir/mapreduce.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/wangkoukou/Desktop/cs537/p6/mapreduce.c -o CMakeFiles/p6.dir/mapreduce.c.s

# Object files for target p6
p6_OBJECTS = \
"CMakeFiles/p6.dir/main.c.o" \
"CMakeFiles/p6.dir/mapreduce.c.o"

# External object files for target p6
p6_EXTERNAL_OBJECTS =

p6: CMakeFiles/p6.dir/main.c.o
p6: CMakeFiles/p6.dir/mapreduce.c.o
p6: CMakeFiles/p6.dir/build.make
p6: CMakeFiles/p6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable p6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p6.dir/build: p6

.PHONY : CMakeFiles/p6.dir/build

CMakeFiles/p6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p6.dir/clean

CMakeFiles/p6.dir/depend:
	cd /Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangkoukou/Desktop/cs537/p6 /Users/wangkoukou/Desktop/cs537/p6 /Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug /Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug /Users/wangkoukou/Desktop/cs537/p6/cmake-build-debug/CMakeFiles/p6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p6.dir/depend
