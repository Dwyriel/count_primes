# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dwyriel/Code/CPP/count_primes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dwyriel/Code/CPP/count_primes/build

# Include any dependencies generated for this target.
include CMakeFiles/count_primes.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/count_primes.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/count_primes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/count_primes.dir/flags.make

CMakeFiles/count_primes.dir/src/Logger.cpp.o: CMakeFiles/count_primes.dir/flags.make
CMakeFiles/count_primes.dir/src/Logger.cpp.o: ../src/Logger.cpp
CMakeFiles/count_primes.dir/src/Logger.cpp.o: CMakeFiles/count_primes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dwyriel/Code/CPP/count_primes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/count_primes.dir/src/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/count_primes.dir/src/Logger.cpp.o -MF CMakeFiles/count_primes.dir/src/Logger.cpp.o.d -o CMakeFiles/count_primes.dir/src/Logger.cpp.o -c /home/dwyriel/Code/CPP/count_primes/src/Logger.cpp

CMakeFiles/count_primes.dir/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/count_primes.dir/src/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dwyriel/Code/CPP/count_primes/src/Logger.cpp > CMakeFiles/count_primes.dir/src/Logger.cpp.i

CMakeFiles/count_primes.dir/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/count_primes.dir/src/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dwyriel/Code/CPP/count_primes/src/Logger.cpp -o CMakeFiles/count_primes.dir/src/Logger.cpp.s

CMakeFiles/count_primes.dir/src/main.cpp.o: CMakeFiles/count_primes.dir/flags.make
CMakeFiles/count_primes.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/count_primes.dir/src/main.cpp.o: CMakeFiles/count_primes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dwyriel/Code/CPP/count_primes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/count_primes.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/count_primes.dir/src/main.cpp.o -MF CMakeFiles/count_primes.dir/src/main.cpp.o.d -o CMakeFiles/count_primes.dir/src/main.cpp.o -c /home/dwyriel/Code/CPP/count_primes/src/main.cpp

CMakeFiles/count_primes.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/count_primes.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dwyriel/Code/CPP/count_primes/src/main.cpp > CMakeFiles/count_primes.dir/src/main.cpp.i

CMakeFiles/count_primes.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/count_primes.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dwyriel/Code/CPP/count_primes/src/main.cpp -o CMakeFiles/count_primes.dir/src/main.cpp.s

# Object files for target count_primes
count_primes_OBJECTS = \
"CMakeFiles/count_primes.dir/src/Logger.cpp.o" \
"CMakeFiles/count_primes.dir/src/main.cpp.o"

# External object files for target count_primes
count_primes_EXTERNAL_OBJECTS =

count_primes: CMakeFiles/count_primes.dir/src/Logger.cpp.o
count_primes: CMakeFiles/count_primes.dir/src/main.cpp.o
count_primes: CMakeFiles/count_primes.dir/build.make
count_primes: CMakeFiles/count_primes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dwyriel/Code/CPP/count_primes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable count_primes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/count_primes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/count_primes.dir/build: count_primes
.PHONY : CMakeFiles/count_primes.dir/build

CMakeFiles/count_primes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/count_primes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/count_primes.dir/clean

CMakeFiles/count_primes.dir/depend:
	cd /home/dwyriel/Code/CPP/count_primes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dwyriel/Code/CPP/count_primes /home/dwyriel/Code/CPP/count_primes /home/dwyriel/Code/CPP/count_primes/build /home/dwyriel/Code/CPP/count_primes/build /home/dwyriel/Code/CPP/count_primes/build/CMakeFiles/count_primes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/count_primes.dir/depend

