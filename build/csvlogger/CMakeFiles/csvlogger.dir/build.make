# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\c5pas\Desktop\raspberry\prove\delay

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\c5pas\Desktop\raspberry\prove\delay\build

# Include any dependencies generated for this target.
include csvlogger/CMakeFiles/csvlogger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include csvlogger/CMakeFiles/csvlogger.dir/compiler_depend.make

# Include the progress variables for this target.
include csvlogger/CMakeFiles/csvlogger.dir/progress.make

# Include the compile flags for this target's objects.
include csvlogger/CMakeFiles/csvlogger.dir/flags.make

csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj: csvlogger/CMakeFiles/csvlogger.dir/flags.make
csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj: csvlogger/CMakeFiles/csvlogger.dir/includes_CXX.rsp
csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj: C:/Users/c5pas/Desktop/raspberry/prove/delay/csvlogger/CsvLogger.cpp
csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj: csvlogger/CMakeFiles/csvlogger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\c5pas\Desktop\raspberry\prove\delay\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj"
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj -MF CMakeFiles\csvlogger.dir\CsvLogger.cpp.obj.d -o CMakeFiles\csvlogger.dir\CsvLogger.cpp.obj -c C:\Users\c5pas\Desktop\raspberry\prove\delay\csvlogger\CsvLogger.cpp

csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/csvlogger.dir/CsvLogger.cpp.i"
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\c5pas\Desktop\raspberry\prove\delay\csvlogger\CsvLogger.cpp > CMakeFiles\csvlogger.dir\CsvLogger.cpp.i

csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/csvlogger.dir/CsvLogger.cpp.s"
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\c5pas\Desktop\raspberry\prove\delay\csvlogger\CsvLogger.cpp -o CMakeFiles\csvlogger.dir\CsvLogger.cpp.s

# Object files for target csvlogger
csvlogger_OBJECTS = \
"CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj"

# External object files for target csvlogger
csvlogger_EXTERNAL_OBJECTS =

csvlogger/libcsvlogger.a: csvlogger/CMakeFiles/csvlogger.dir/CsvLogger.cpp.obj
csvlogger/libcsvlogger.a: csvlogger/CMakeFiles/csvlogger.dir/build.make
csvlogger/libcsvlogger.a: csvlogger/CMakeFiles/csvlogger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\c5pas\Desktop\raspberry\prove\delay\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcsvlogger.a"
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && $(CMAKE_COMMAND) -P CMakeFiles\csvlogger.dir\cmake_clean_target.cmake
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\csvlogger.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
csvlogger/CMakeFiles/csvlogger.dir/build: csvlogger/libcsvlogger.a
.PHONY : csvlogger/CMakeFiles/csvlogger.dir/build

csvlogger/CMakeFiles/csvlogger.dir/clean:
	cd /d C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger && $(CMAKE_COMMAND) -P CMakeFiles\csvlogger.dir\cmake_clean.cmake
.PHONY : csvlogger/CMakeFiles/csvlogger.dir/clean

csvlogger/CMakeFiles/csvlogger.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\c5pas\Desktop\raspberry\prove\delay C:\Users\c5pas\Desktop\raspberry\prove\delay\csvlogger C:\Users\c5pas\Desktop\raspberry\prove\delay\build C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger C:\Users\c5pas\Desktop\raspberry\prove\delay\build\csvlogger\CMakeFiles\csvlogger.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : csvlogger/CMakeFiles/csvlogger.dir/depend

