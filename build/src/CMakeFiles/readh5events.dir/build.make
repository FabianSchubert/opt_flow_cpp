# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /its/home/fs388/repos/opt_flow_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /its/home/fs388/repos/opt_flow_cpp/build

# Include any dependencies generated for this target.
include src/CMakeFiles/readh5events.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/readh5events.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/readh5events.dir/flags.make

src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.o: src/CMakeFiles/readh5events.dir/flags.make
src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.o: ../src/ReadH5Events.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/its/home/fs388/repos/opt_flow_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.o"
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/readh5events.dir/ReadH5Events.cpp.o -c /its/home/fs388/repos/opt_flow_cpp/src/ReadH5Events.cpp

src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readh5events.dir/ReadH5Events.cpp.i"
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /its/home/fs388/repos/opt_flow_cpp/src/ReadH5Events.cpp > CMakeFiles/readh5events.dir/ReadH5Events.cpp.i

src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readh5events.dir/ReadH5Events.cpp.s"
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /its/home/fs388/repos/opt_flow_cpp/src/ReadH5Events.cpp -o CMakeFiles/readh5events.dir/ReadH5Events.cpp.s

# Object files for target readh5events
readh5events_OBJECTS = \
"CMakeFiles/readh5events.dir/ReadH5Events.cpp.o"

# External object files for target readh5events
readh5events_EXTERNAL_OBJECTS =

src/libreadh5events.a: src/CMakeFiles/readh5events.dir/ReadH5Events.cpp.o
src/libreadh5events.a: src/CMakeFiles/readh5events.dir/build.make
src/libreadh5events.a: src/CMakeFiles/readh5events.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/its/home/fs388/repos/opt_flow_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libreadh5events.a"
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && $(CMAKE_COMMAND) -P CMakeFiles/readh5events.dir/cmake_clean_target.cmake
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readh5events.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/readh5events.dir/build: src/libreadh5events.a

.PHONY : src/CMakeFiles/readh5events.dir/build

src/CMakeFiles/readh5events.dir/clean:
	cd /its/home/fs388/repos/opt_flow_cpp/build/src && $(CMAKE_COMMAND) -P CMakeFiles/readh5events.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/readh5events.dir/clean

src/CMakeFiles/readh5events.dir/depend:
	cd /its/home/fs388/repos/opt_flow_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /its/home/fs388/repos/opt_flow_cpp /its/home/fs388/repos/opt_flow_cpp/src /its/home/fs388/repos/opt_flow_cpp/build /its/home/fs388/repos/opt_flow_cpp/build/src /its/home/fs388/repos/opt_flow_cpp/build/src/CMakeFiles/readh5events.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/readh5events.dir/depend

