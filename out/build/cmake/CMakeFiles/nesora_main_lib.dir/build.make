# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake

# Include any dependencies generated for this target.
include CMakeFiles/nesora_main_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nesora_main_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nesora_main_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nesora_main_lib.dir/flags.make

CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o: CMakeFiles/nesora_main_lib.dir/flags.make
CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o: /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/Nesora.cpp
CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o: CMakeFiles/nesora_main_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o -MF CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o.d -o CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o -c /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/Nesora.cpp

CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/Nesora.cpp > CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.i

CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/Nesora.cpp -o CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.s

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o: CMakeFiles/nesora_main_lib.dir/flags.make
CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o: /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraInterpreter.cpp
CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o: CMakeFiles/nesora_main_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o -MF CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o.d -o CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o -c /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraInterpreter.cpp

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraInterpreter.cpp > CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.i

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraInterpreter.cpp -o CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.s

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o: CMakeFiles/nesora_main_lib.dir/flags.make
CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o: /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraStringFormat.cpp
CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o: CMakeFiles/nesora_main_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o -MF CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o.d -o CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o -c /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraStringFormat.cpp

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraStringFormat.cpp > CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.i

CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/src/Nesora/NesoraStringFormat.cpp -o CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.s

# Object files for target nesora_main_lib
nesora_main_lib_OBJECTS = \
"CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o" \
"CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o" \
"CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o"

# External object files for target nesora_main_lib
nesora_main_lib_EXTERNAL_OBJECTS =

libnesora_main_lib.a: CMakeFiles/nesora_main_lib.dir/src/Nesora/Nesora.cpp.o
libnesora_main_lib.a: CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraInterpreter.cpp.o
libnesora_main_lib.a: CMakeFiles/nesora_main_lib.dir/src/Nesora/NesoraStringFormat.cpp.o
libnesora_main_lib.a: CMakeFiles/nesora_main_lib.dir/build.make
libnesora_main_lib.a: CMakeFiles/nesora_main_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libnesora_main_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/nesora_main_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nesora_main_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nesora_main_lib.dir/build: libnesora_main_lib.a
.PHONY : CMakeFiles/nesora_main_lib.dir/build

CMakeFiles/nesora_main_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nesora_main_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nesora_main_lib.dir/clean

CMakeFiles/nesora_main_lib.dir/depend:
	cd /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake /Users/muchosp/Documents/MucchoSP/音諳/音諳プロジェクト/Nesora-mkm/out/build/cmake/CMakeFiles/nesora_main_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/nesora_main_lib.dir/depend
