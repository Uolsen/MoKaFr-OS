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
CMAKE_COMMAND = "/Users/lukasfrey/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/222.4345.21/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/lukasfrey/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/222.4345.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Mokafr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Mokafr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Mokafr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mokafr.dir/flags.make

CMakeFiles/Mokafr.dir/main.cpp.o: CMakeFiles/Mokafr.dir/flags.make
CMakeFiles/Mokafr.dir/main.cpp.o: ../main.cpp
CMakeFiles/Mokafr.dir/main.cpp.o: CMakeFiles/Mokafr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Mokafr.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Mokafr.dir/main.cpp.o -MF CMakeFiles/Mokafr.dir/main.cpp.o.d -o CMakeFiles/Mokafr.dir/main.cpp.o -c /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/main.cpp

CMakeFiles/Mokafr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mokafr.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/main.cpp > CMakeFiles/Mokafr.dir/main.cpp.i

CMakeFiles/Mokafr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mokafr.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/main.cpp -o CMakeFiles/Mokafr.dir/main.cpp.s

# Object files for target Mokafr
Mokafr_OBJECTS = \
"CMakeFiles/Mokafr.dir/main.cpp.o"

# External object files for target Mokafr
Mokafr_EXTERNAL_OBJECTS =

Mokafr: CMakeFiles/Mokafr.dir/main.cpp.o
Mokafr: CMakeFiles/Mokafr.dir/build.make
Mokafr: CMakeFiles/Mokafr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Mokafr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mokafr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mokafr.dir/build: Mokafr
.PHONY : CMakeFiles/Mokafr.dir/build

CMakeFiles/Mokafr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Mokafr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Mokafr.dir/clean

CMakeFiles/Mokafr.dir/depend:
	cd /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug /Users/lukasfrey/Development/ZCU/OS/MoKaFr-OS/cmake-build-debug/CMakeFiles/Mokafr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Mokafr.dir/depend

