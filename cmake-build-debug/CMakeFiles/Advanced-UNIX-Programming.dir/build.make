# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Advanced-UNIX-Programming.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Advanced-UNIX-Programming.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Advanced-UNIX-Programming.dir/flags.make

CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.obj: CMakeFiles/Advanced-UNIX-Programming.dir/flags.make
CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.obj: ../netstat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Advanced-UNIX-Programming.dir\netstat.cpp.obj -c "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\netstat.cpp"

CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\netstat.cpp" > CMakeFiles\Advanced-UNIX-Programming.dir\netstat.cpp.i

CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\netstat.cpp" -o CMakeFiles\Advanced-UNIX-Programming.dir\netstat.cpp.s

CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.obj: CMakeFiles/Advanced-UNIX-Programming.dir/flags.make
CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.obj: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Advanced-UNIX-Programming.dir\test.cpp.obj -c "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\test.cpp"

CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\test.cpp" > CMakeFiles\Advanced-UNIX-Programming.dir\test.cpp.i

CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\test.cpp" -o CMakeFiles\Advanced-UNIX-Programming.dir\test.cpp.s

# Object files for target Advanced-UNIX-Programming
Advanced__UNIX__Programming_OBJECTS = \
"CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.obj" \
"CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.obj"

# External object files for target Advanced-UNIX-Programming
Advanced__UNIX__Programming_EXTERNAL_OBJECTS =

Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/netstat.cpp.obj
Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/test.cpp.obj
Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/build.make
Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/linklibs.rsp
Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/objects1.rsp
Advanced-UNIX-Programming.exe: CMakeFiles/Advanced-UNIX-Programming.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Advanced-UNIX-Programming.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Advanced-UNIX-Programming.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Advanced-UNIX-Programming.dir/build: Advanced-UNIX-Programming.exe

.PHONY : CMakeFiles/Advanced-UNIX-Programming.dir/build

CMakeFiles/Advanced-UNIX-Programming.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Advanced-UNIX-Programming.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Advanced-UNIX-Programming.dir/clean

CMakeFiles/Advanced-UNIX-Programming.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming" "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming" "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug" "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug" "D:\03NCTU\02\01Advanced UNIX Programming\03HW\Advanced-UNIX-Programming\cmake-build-debug\CMakeFiles\Advanced-UNIX-Programming.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Advanced-UNIX-Programming.dir/depend

