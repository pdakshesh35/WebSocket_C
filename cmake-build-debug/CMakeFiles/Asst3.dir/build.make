# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /private/var/folders/l1/g2nddtd974d45x_z2zyj9y6r0000gn/T/AppTranslocation/149D9060-A0D0-486B-9821-149EE959227F/d/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /private/var/folders/l1/g2nddtd974d45x_z2zyj9y6r0000gn/T/AppTranslocation/149D9060-A0D0-486B-9821-149EE959227F/d/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dakshpatel/Documents/Rutgers/C/Asst3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Asst3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Asst3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Asst3.dir/flags.make

CMakeFiles/Asst3.dir/client.c.o: CMakeFiles/Asst3.dir/flags.make
CMakeFiles/Asst3.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Asst3.dir/client.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Asst3.dir/client.c.o   -c /Users/dakshpatel/Documents/Rutgers/C/Asst3/client.c

CMakeFiles/Asst3.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Asst3.dir/client.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dakshpatel/Documents/Rutgers/C/Asst3/client.c > CMakeFiles/Asst3.dir/client.c.i

CMakeFiles/Asst3.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Asst3.dir/client.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dakshpatel/Documents/Rutgers/C/Asst3/client.c -o CMakeFiles/Asst3.dir/client.c.s

CMakeFiles/Asst3.dir/client.c.o.requires:

.PHONY : CMakeFiles/Asst3.dir/client.c.o.requires

CMakeFiles/Asst3.dir/client.c.o.provides: CMakeFiles/Asst3.dir/client.c.o.requires
	$(MAKE) -f CMakeFiles/Asst3.dir/build.make CMakeFiles/Asst3.dir/client.c.o.provides.build
.PHONY : CMakeFiles/Asst3.dir/client.c.o.provides

CMakeFiles/Asst3.dir/client.c.o.provides.build: CMakeFiles/Asst3.dir/client.c.o


# Object files for target Asst3
Asst3_OBJECTS = \
"CMakeFiles/Asst3.dir/client.c.o"

# External object files for target Asst3
Asst3_EXTERNAL_OBJECTS =

Asst3: CMakeFiles/Asst3.dir/client.c.o
Asst3: CMakeFiles/Asst3.dir/build.make
Asst3: CMakeFiles/Asst3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Asst3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Asst3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Asst3.dir/build: Asst3

.PHONY : CMakeFiles/Asst3.dir/build

CMakeFiles/Asst3.dir/requires: CMakeFiles/Asst3.dir/client.c.o.requires

.PHONY : CMakeFiles/Asst3.dir/requires

CMakeFiles/Asst3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Asst3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Asst3.dir/clean

CMakeFiles/Asst3.dir/depend:
	cd /Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dakshpatel/Documents/Rutgers/C/Asst3 /Users/dakshpatel/Documents/Rutgers/C/Asst3 /Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug /Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug /Users/dakshpatel/Documents/Rutgers/C/Asst3/cmake-build-debug/CMakeFiles/Asst3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Asst3.dir/depend

