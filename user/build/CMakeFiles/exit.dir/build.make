# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/wxk/Desktop/404OS/oskernel2023-404os/user

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wxk/Desktop/404OS/oskernel2023-404os/user/build

# Include any dependencies generated for this target.
include CMakeFiles/exit.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exit.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exit.dir/flags.make

CMakeFiles/exit.dir/src/oscomp/exit.c.o: CMakeFiles/exit.dir/flags.make
CMakeFiles/exit.dir/src/oscomp/exit.c.o: ../src/oscomp/exit.c
CMakeFiles/exit.dir/src/oscomp/exit.c.o: CMakeFiles/exit.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/exit.dir/src/oscomp/exit.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/exit.dir/src/oscomp/exit.c.o -MF CMakeFiles/exit.dir/src/oscomp/exit.c.o.d -o CMakeFiles/exit.dir/src/oscomp/exit.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/exit.c

CMakeFiles/exit.dir/src/oscomp/exit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exit.dir/src/oscomp/exit.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/exit.c > CMakeFiles/exit.dir/src/oscomp/exit.c.i

CMakeFiles/exit.dir/src/oscomp/exit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exit.dir/src/oscomp/exit.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/exit.c -o CMakeFiles/exit.dir/src/oscomp/exit.c.s

# Object files for target exit
exit_OBJECTS = \
"CMakeFiles/exit.dir/src/oscomp/exit.c.o"

# External object files for target exit
exit_EXTERNAL_OBJECTS =

riscv64/exit: CMakeFiles/exit.dir/src/oscomp/exit.c.o
riscv64/exit: CMakeFiles/exit.dir/build.make
riscv64/exit: libulib.a
riscv64/exit: CMakeFiles/exit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable riscv64/exit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exit.dir/link.txt --verbose=$(VERBOSE)
	mkdir -p asm
	riscv64-unknown-elf-objdump -d -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/build/riscv64/exit > asm/exit.asm
	mkdir -p bin
	riscv64-unknown-elf-objcopy -O binary /home/wxk/Desktop/404OS/oskernel2023-404os/user/build/riscv64/exit bin/exit.bin --set-section-flags .bss=alloc,load,contents

# Rule to build all files generated by this target.
CMakeFiles/exit.dir/build: riscv64/exit
.PHONY : CMakeFiles/exit.dir/build

CMakeFiles/exit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exit.dir/clean

CMakeFiles/exit.dir/depend:
	cd /home/wxk/Desktop/404OS/oskernel2023-404os/user/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wxk/Desktop/404OS/oskernel2023-404os/user /home/wxk/Desktop/404OS/oskernel2023-404os/user /home/wxk/Desktop/404OS/oskernel2023-404os/user/build /home/wxk/Desktop/404OS/oskernel2023-404os/user/build /home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles/exit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exit.dir/depend

