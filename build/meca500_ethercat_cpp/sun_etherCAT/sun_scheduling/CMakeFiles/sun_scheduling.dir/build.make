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
include meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/depend.make

# Include the progress variables for this target.
include meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/progress.make

# Include the compile flags for this target's objects.
include meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/flags.make

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.o: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/flags.make
meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.o: ../meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/src/scheduling.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.o"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sun_scheduling.dir/src/scheduling.c.o -c /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/src/scheduling.c

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sun_scheduling.dir/src/scheduling.c.i"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/src/scheduling.c > CMakeFiles/sun_scheduling.dir/src/scheduling.c.i

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sun_scheduling.dir/src/scheduling.c.s"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/src/scheduling.c -o CMakeFiles/sun_scheduling.dir/src/scheduling.c.s

# Object files for target sun_scheduling
sun_scheduling_OBJECTS = \
"CMakeFiles/sun_scheduling.dir/src/scheduling.c.o"

# External object files for target sun_scheduling
sun_scheduling_EXTERNAL_OBJECTS =

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/libsun_scheduling.a: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/src/scheduling.c.o
meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/libsun_scheduling.a: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/build.make
meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/libsun_scheduling.a: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/c_projects/calibrazione/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsun_scheduling.a"
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && $(CMAKE_COMMAND) -P CMakeFiles/sun_scheduling.dir/cmake_clean_target.cmake
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sun_scheduling.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/build: meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/libsun_scheduling.a

.PHONY : meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/build

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/clean:
	cd /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling && $(CMAKE_COMMAND) -P CMakeFiles/sun_scheduling.dir/cmake_clean.cmake
.PHONY : meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/clean

meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/depend:
	cd /home/pi/Desktop/c_projects/calibrazione/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/c_projects/calibrazione /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling /home/pi/Desktop/c_projects/calibrazione/build /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling /home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : meca500_ethercat_cpp/sun_etherCAT/sun_scheduling/CMakeFiles/sun_scheduling.dir/depend

