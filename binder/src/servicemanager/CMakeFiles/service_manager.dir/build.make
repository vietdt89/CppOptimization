# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/worker/binder/src/servicemanager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/worker/binder/src/servicemanager

# Include any dependencies generated for this target.
include CMakeFiles/service_manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/service_manager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/service_manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/service_manager.dir/flags.make

CMakeFiles/service_manager.dir/service_manager.c.o: CMakeFiles/service_manager.dir/flags.make
CMakeFiles/service_manager.dir/service_manager.c.o: service_manager.c
CMakeFiles/service_manager.dir/service_manager.c.o: CMakeFiles/service_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/worker/binder/src/servicemanager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/service_manager.dir/service_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/service_manager.dir/service_manager.c.o -MF CMakeFiles/service_manager.dir/service_manager.c.o.d -o CMakeFiles/service_manager.dir/service_manager.c.o -c /home/worker/binder/src/servicemanager/service_manager.c

CMakeFiles/service_manager.dir/service_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/service_manager.dir/service_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/worker/binder/src/servicemanager/service_manager.c > CMakeFiles/service_manager.dir/service_manager.c.i

CMakeFiles/service_manager.dir/service_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/service_manager.dir/service_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/worker/binder/src/servicemanager/service_manager.c -o CMakeFiles/service_manager.dir/service_manager.c.s

CMakeFiles/service_manager.dir/binder.c.o: CMakeFiles/service_manager.dir/flags.make
CMakeFiles/service_manager.dir/binder.c.o: binder.c
CMakeFiles/service_manager.dir/binder.c.o: CMakeFiles/service_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/worker/binder/src/servicemanager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/service_manager.dir/binder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/service_manager.dir/binder.c.o -MF CMakeFiles/service_manager.dir/binder.c.o.d -o CMakeFiles/service_manager.dir/binder.c.o -c /home/worker/binder/src/servicemanager/binder.c

CMakeFiles/service_manager.dir/binder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/service_manager.dir/binder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/worker/binder/src/servicemanager/binder.c > CMakeFiles/service_manager.dir/binder.c.i

CMakeFiles/service_manager.dir/binder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/service_manager.dir/binder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/worker/binder/src/servicemanager/binder.c -o CMakeFiles/service_manager.dir/binder.c.s

# Object files for target service_manager
service_manager_OBJECTS = \
"CMakeFiles/service_manager.dir/service_manager.c.o" \
"CMakeFiles/service_manager.dir/binder.c.o"

# External object files for target service_manager
service_manager_EXTERNAL_OBJECTS =

service_manager: CMakeFiles/service_manager.dir/service_manager.c.o
service_manager: CMakeFiles/service_manager.dir/binder.c.o
service_manager: CMakeFiles/service_manager.dir/build.make
service_manager: CMakeFiles/service_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/worker/binder/src/servicemanager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable service_manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/service_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/service_manager.dir/build: service_manager
.PHONY : CMakeFiles/service_manager.dir/build

CMakeFiles/service_manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/service_manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/service_manager.dir/clean

CMakeFiles/service_manager.dir/depend:
	cd /home/worker/binder/src/servicemanager && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/worker/binder/src/servicemanager /home/worker/binder/src/servicemanager /home/worker/binder/src/servicemanager /home/worker/binder/src/servicemanager /home/worker/binder/src/servicemanager/CMakeFiles/service_manager.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/service_manager.dir/depend

