# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/phvera/Documents/InfoFond/projet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phvera/Documents/InfoFond/projet/build

# Include any dependencies generated for this target.
include CMakeFiles/proj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj.dir/flags.make

CMakeFiles/proj.dir/minisat/Solver.cpp.o: CMakeFiles/proj.dir/flags.make
CMakeFiles/proj.dir/minisat/Solver.cpp.o: ../minisat/Solver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/phvera/Documents/InfoFond/projet/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/proj.dir/minisat/Solver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/proj.dir/minisat/Solver.cpp.o -c /home/phvera/Documents/InfoFond/projet/minisat/Solver.cpp

CMakeFiles/proj.dir/minisat/Solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj.dir/minisat/Solver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/phvera/Documents/InfoFond/projet/minisat/Solver.cpp > CMakeFiles/proj.dir/minisat/Solver.cpp.i

CMakeFiles/proj.dir/minisat/Solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj.dir/minisat/Solver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/phvera/Documents/InfoFond/projet/minisat/Solver.cpp -o CMakeFiles/proj.dir/minisat/Solver.cpp.s

CMakeFiles/proj.dir/minisat/Solver.cpp.o.requires:
.PHONY : CMakeFiles/proj.dir/minisat/Solver.cpp.o.requires

CMakeFiles/proj.dir/minisat/Solver.cpp.o.provides: CMakeFiles/proj.dir/minisat/Solver.cpp.o.requires
	$(MAKE) -f CMakeFiles/proj.dir/build.make CMakeFiles/proj.dir/minisat/Solver.cpp.o.provides.build
.PHONY : CMakeFiles/proj.dir/minisat/Solver.cpp.o.provides

CMakeFiles/proj.dir/minisat/Solver.cpp.o.provides.build: CMakeFiles/proj.dir/minisat/Solver.cpp.o

CMakeFiles/proj.dir/main.cpp.o: CMakeFiles/proj.dir/flags.make
CMakeFiles/proj.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/phvera/Documents/InfoFond/projet/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/proj.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/proj.dir/main.cpp.o -c /home/phvera/Documents/InfoFond/projet/main.cpp

CMakeFiles/proj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/phvera/Documents/InfoFond/projet/main.cpp > CMakeFiles/proj.dir/main.cpp.i

CMakeFiles/proj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/phvera/Documents/InfoFond/projet/main.cpp -o CMakeFiles/proj.dir/main.cpp.s

CMakeFiles/proj.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/proj.dir/main.cpp.o.requires

CMakeFiles/proj.dir/main.cpp.o.provides: CMakeFiles/proj.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/proj.dir/build.make CMakeFiles/proj.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/proj.dir/main.cpp.o.provides

CMakeFiles/proj.dir/main.cpp.o.provides.build: CMakeFiles/proj.dir/main.cpp.o

# Object files for target proj
proj_OBJECTS = \
"CMakeFiles/proj.dir/minisat/Solver.cpp.o" \
"CMakeFiles/proj.dir/main.cpp.o"

# External object files for target proj
proj_EXTERNAL_OBJECTS =

proj: CMakeFiles/proj.dir/minisat/Solver.cpp.o
proj: CMakeFiles/proj.dir/main.cpp.o
proj: CMakeFiles/proj.dir/build.make
proj: CMakeFiles/proj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable proj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj.dir/build: proj
.PHONY : CMakeFiles/proj.dir/build

CMakeFiles/proj.dir/requires: CMakeFiles/proj.dir/minisat/Solver.cpp.o.requires
CMakeFiles/proj.dir/requires: CMakeFiles/proj.dir/main.cpp.o.requires
.PHONY : CMakeFiles/proj.dir/requires

CMakeFiles/proj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proj.dir/clean

CMakeFiles/proj.dir/depend:
	cd /home/phvera/Documents/InfoFond/projet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phvera/Documents/InfoFond/projet /home/phvera/Documents/InfoFond/projet /home/phvera/Documents/InfoFond/projet/build /home/phvera/Documents/InfoFond/projet/build /home/phvera/Documents/InfoFond/projet/build/CMakeFiles/proj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj.dir/depend

