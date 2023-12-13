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
include meca500_ethercat_cpp/CMakeFiles/robot-test.dir/depend.make

# Include the progress variables for this target.
include meca500_ethercat_cpp/CMakeFiles/robot-test.dir/progress.make

# Include the compile flags for this target's objects.
include meca500_ethercat_cpp/CMakeFiles/robot-test.dir/flags.make

meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.o: meca500_ethercat_cpp/CMakeFiles/robot-test.dir/flags.make
meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.o: ../meca500_ethercat_cpp/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.o"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robot-test.dir/test.cpp.o -c /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/test.cpp

meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot-test.dir/test.cpp.i"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/test.cpp > CMakeFiles/robot-test.dir/test.cpp.i

meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot-test.dir/test.cpp.s"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/test.cpp -o CMakeFiles/robot-test.dir/test.cpp.s

# Object files for target robot-test
robot__test_OBJECTS = \
"CMakeFiles/robot-test.dir/test.cpp.o"

# External object files for target robot-test
robot__test_EXTERNAL_OBJECTS =

meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/CMakeFiles/robot-test.dir/test.cpp.o
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/CMakeFiles/robot-test.dir/build.make
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/libmeca500_driver.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/sun_etherCAT/sun_controller/libsun_controller.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/sun_etherCAT/sun_slave/libsun_slave.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/sun_etherCAT/sun_ethercat_master/libsun_ethercat_master.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/sun_etherCAT/SOEM/libsoem.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/libsun_scheduling.a
meca500_ethercat_cpp/robot-test: meca500_ethercat_cpp/CMakeFiles/robot-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable robot-test"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robot-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
meca500_ethercat_cpp/CMakeFiles/robot-test.dir/build: meca500_ethercat_cpp/robot-test

.PHONY : meca500_ethercat_cpp/CMakeFiles/robot-test.dir/build

meca500_ethercat_cpp/CMakeFiles/robot-test.dir/clean:
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp && $(CMAKE_COMMAND) -P CMakeFiles/robot-test.dir/cmake_clean.cmake
.PHONY : meca500_ethercat_cpp/CMakeFiles/robot-test.dir/clean

meca500_ethercat_cpp/CMakeFiles/robot-test.dir/depend:
	cd /home/pi/Desktop/c_projects/calibrazione/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/c_projects/calibrazione /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp /home/pi/Desktop/c_projects/calibrazione/build /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/CMakeFiles/robot-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : meca500_ethercat_cpp/CMakeFiles/robot-test.dir/depend
