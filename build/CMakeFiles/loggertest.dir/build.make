# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/Desktop/c_projects/calibrazione

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/c_projects/calibrazione/build

# Include any dependencies generated for this target.
include CMakeFiles/loggertest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/loggertest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/loggertest.dir/flags.make

CMakeFiles/loggertest.dir/loggertest.cpp.o: CMakeFiles/loggertest.dir/flags.make
CMakeFiles/loggertest.dir/loggertest.cpp.o: ../loggertest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/loggertest.dir/loggertest.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/loggertest.dir/loggertest.cpp.o -c /home/pi/Desktop/c_projects/calibrazione/loggertest.cpp

CMakeFiles/loggertest.dir/loggertest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/loggertest.dir/loggertest.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/c_projects/calibrazione/loggertest.cpp > CMakeFiles/loggertest.dir/loggertest.cpp.i

CMakeFiles/loggertest.dir/loggertest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/loggertest.dir/loggertest.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/c_projects/calibrazione/loggertest.cpp -o CMakeFiles/loggertest.dir/loggertest.cpp.s

# Object files for target loggertest
loggertest_OBJECTS = \
"CMakeFiles/loggertest.dir/loggertest.cpp.o"

# External object files for target loggertest
loggertest_EXTERNAL_OBJECTS =

loggertest: CMakeFiles/loggertest.dir/loggertest.cpp.o
loggertest: CMakeFiles/loggertest.dir/build.make
loggertest: csvlogger/libcsvlogger.a
loggertest: CMakeFiles/loggertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable loggertest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/loggertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/loggertest.dir/build: loggertest

.PHONY : CMakeFiles/loggertest.dir/build

CMakeFiles/loggertest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/loggertest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/loggertest.dir/clean

CMakeFiles/loggertest.dir/depend:
	cd /home/pi/Desktop/c_projects/calibrazione/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/c_projects/calibrazione /home/pi/Desktop/c_projects/calibrazione /home/pi/Desktop/c_projects/calibrazione/build /home/pi/Desktop/c_projects/calibrazione/build /home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles/loggertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/loggertest.dir/depend
