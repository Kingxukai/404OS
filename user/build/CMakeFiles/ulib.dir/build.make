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
include CMakeFiles/ulib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ulib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ulib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ulib.dir/flags.make

syscall_ids.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating syscall_ids.h"
	sed -n -e s/__NR_/SYS_/p < /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/arch/riscv/syscall_ids.h.in > /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/syscall_ids.h

CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o: ../lib/arch/riscv/crt.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building ASM object CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/arch/riscv/crt.S

CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.i"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/arch/riscv/crt.S > CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.i

CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.s"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/arch/riscv/crt.S -o CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.s

CMakeFiles/ulib.dir/src/oscomp/clone.s.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/src/oscomp/clone.s.o: ../src/oscomp/clone.s
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building ASM object CMakeFiles/ulib.dir/src/oscomp/clone.s.o"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/ulib.dir/src/oscomp/clone.s.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/clone.s

CMakeFiles/ulib.dir/src/oscomp/clone.s.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/ulib.dir/src/oscomp/clone.s.i"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/clone.s > CMakeFiles/ulib.dir/src/oscomp/clone.s.i

CMakeFiles/ulib.dir/src/oscomp/clone.s.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/ulib.dir/src/oscomp/clone.s.s"
	riscv64-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/src/oscomp/clone.s -o CMakeFiles/ulib.dir/src/oscomp/clone.s.s

CMakeFiles/ulib.dir/lib/main.c.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/main.c.o: ../lib/main.c
CMakeFiles/ulib.dir/lib/main.c.o: CMakeFiles/ulib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ulib.dir/lib/main.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ulib.dir/lib/main.c.o -MF CMakeFiles/ulib.dir/lib/main.c.o.d -o CMakeFiles/ulib.dir/lib/main.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/main.c

CMakeFiles/ulib.dir/lib/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ulib.dir/lib/main.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/main.c > CMakeFiles/ulib.dir/lib/main.c.i

CMakeFiles/ulib.dir/lib/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ulib.dir/lib/main.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/main.c -o CMakeFiles/ulib.dir/lib/main.c.s

CMakeFiles/ulib.dir/lib/stdio.c.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/stdio.c.o: ../lib/stdio.c
CMakeFiles/ulib.dir/lib/stdio.c.o: CMakeFiles/ulib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ulib.dir/lib/stdio.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ulib.dir/lib/stdio.c.o -MF CMakeFiles/ulib.dir/lib/stdio.c.o.d -o CMakeFiles/ulib.dir/lib/stdio.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdio.c

CMakeFiles/ulib.dir/lib/stdio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ulib.dir/lib/stdio.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdio.c > CMakeFiles/ulib.dir/lib/stdio.c.i

CMakeFiles/ulib.dir/lib/stdio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ulib.dir/lib/stdio.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdio.c -o CMakeFiles/ulib.dir/lib/stdio.c.s

CMakeFiles/ulib.dir/lib/stdlib.c.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/stdlib.c.o: ../lib/stdlib.c
CMakeFiles/ulib.dir/lib/stdlib.c.o: CMakeFiles/ulib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ulib.dir/lib/stdlib.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ulib.dir/lib/stdlib.c.o -MF CMakeFiles/ulib.dir/lib/stdlib.c.o.d -o CMakeFiles/ulib.dir/lib/stdlib.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdlib.c

CMakeFiles/ulib.dir/lib/stdlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ulib.dir/lib/stdlib.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdlib.c > CMakeFiles/ulib.dir/lib/stdlib.c.i

CMakeFiles/ulib.dir/lib/stdlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ulib.dir/lib/stdlib.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/stdlib.c -o CMakeFiles/ulib.dir/lib/stdlib.c.s

CMakeFiles/ulib.dir/lib/string.c.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/string.c.o: ../lib/string.c
CMakeFiles/ulib.dir/lib/string.c.o: CMakeFiles/ulib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ulib.dir/lib/string.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ulib.dir/lib/string.c.o -MF CMakeFiles/ulib.dir/lib/string.c.o.d -o CMakeFiles/ulib.dir/lib/string.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/string.c

CMakeFiles/ulib.dir/lib/string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ulib.dir/lib/string.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/string.c > CMakeFiles/ulib.dir/lib/string.c.i

CMakeFiles/ulib.dir/lib/string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ulib.dir/lib/string.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/string.c -o CMakeFiles/ulib.dir/lib/string.c.s

CMakeFiles/ulib.dir/lib/syscall.c.o: CMakeFiles/ulib.dir/flags.make
CMakeFiles/ulib.dir/lib/syscall.c.o: ../lib/syscall.c
CMakeFiles/ulib.dir/lib/syscall.c.o: CMakeFiles/ulib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/ulib.dir/lib/syscall.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ulib.dir/lib/syscall.c.o -MF CMakeFiles/ulib.dir/lib/syscall.c.o.d -o CMakeFiles/ulib.dir/lib/syscall.c.o -c /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/syscall.c

CMakeFiles/ulib.dir/lib/syscall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ulib.dir/lib/syscall.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/syscall.c > CMakeFiles/ulib.dir/lib/syscall.c.i

CMakeFiles/ulib.dir/lib/syscall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ulib.dir/lib/syscall.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wxk/Desktop/404OS/oskernel2023-404os/user/lib/syscall.c -o CMakeFiles/ulib.dir/lib/syscall.c.s

# Object files for target ulib
ulib_OBJECTS = \
"CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o" \
"CMakeFiles/ulib.dir/src/oscomp/clone.s.o" \
"CMakeFiles/ulib.dir/lib/main.c.o" \
"CMakeFiles/ulib.dir/lib/stdio.c.o" \
"CMakeFiles/ulib.dir/lib/stdlib.c.o" \
"CMakeFiles/ulib.dir/lib/string.c.o" \
"CMakeFiles/ulib.dir/lib/syscall.c.o"

# External object files for target ulib
ulib_EXTERNAL_OBJECTS =

libulib.a: CMakeFiles/ulib.dir/lib/arch/riscv/crt.S.o
libulib.a: CMakeFiles/ulib.dir/src/oscomp/clone.s.o
libulib.a: CMakeFiles/ulib.dir/lib/main.c.o
libulib.a: CMakeFiles/ulib.dir/lib/stdio.c.o
libulib.a: CMakeFiles/ulib.dir/lib/stdlib.c.o
libulib.a: CMakeFiles/ulib.dir/lib/string.c.o
libulib.a: CMakeFiles/ulib.dir/lib/syscall.c.o
libulib.a: CMakeFiles/ulib.dir/build.make
libulib.a: CMakeFiles/ulib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C static library libulib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ulib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ulib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ulib.dir/build: libulib.a
.PHONY : CMakeFiles/ulib.dir/build

CMakeFiles/ulib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ulib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ulib.dir/clean

CMakeFiles/ulib.dir/depend: syscall_ids.h
	cd /home/wxk/Desktop/404OS/oskernel2023-404os/user/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wxk/Desktop/404OS/oskernel2023-404os/user /home/wxk/Desktop/404OS/oskernel2023-404os/user /home/wxk/Desktop/404OS/oskernel2023-404os/user/build /home/wxk/Desktop/404OS/oskernel2023-404os/user/build /home/wxk/Desktop/404OS/oskernel2023-404os/user/build/CMakeFiles/ulib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ulib.dir/depend

