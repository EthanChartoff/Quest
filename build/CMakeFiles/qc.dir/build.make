# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/goodman/school/Quest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/goodman/school/Quest/build

# Include any dependencies generated for this target.
include CMakeFiles/qc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qc.dir/flags.make

CMakeFiles/qc.dir/src/io.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/io.c.o: /home/goodman/school/Quest/src/io.c
CMakeFiles/qc.dir/src/io.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/qc.dir/src/io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/io.c.o -MF CMakeFiles/qc.dir/src/io.c.o.d -o CMakeFiles/qc.dir/src/io.c.o -c /home/goodman/school/Quest/src/io.c

CMakeFiles/qc.dir/src/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/io.c > CMakeFiles/qc.dir/src/io.c.i

CMakeFiles/qc.dir/src/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/io.c -o CMakeFiles/qc.dir/src/io.c.s

CMakeFiles/qc.dir/src/lexer/lexer.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/lexer/lexer.c.o: /home/goodman/school/Quest/src/lexer/lexer.c
CMakeFiles/qc.dir/src/lexer/lexer.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/qc.dir/src/lexer/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/lexer/lexer.c.o -MF CMakeFiles/qc.dir/src/lexer/lexer.c.o.d -o CMakeFiles/qc.dir/src/lexer/lexer.c.o -c /home/goodman/school/Quest/src/lexer/lexer.c

CMakeFiles/qc.dir/src/lexer/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/lexer/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/lexer/lexer.c > CMakeFiles/qc.dir/src/lexer/lexer.c.i

CMakeFiles/qc.dir/src/lexer/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/lexer/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/lexer/lexer.c -o CMakeFiles/qc.dir/src/lexer/lexer.c.s

CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o: /home/goodman/school/Quest/src/lexer/lexer_automata.c
CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o -MF CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o.d -o CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o -c /home/goodman/school/Quest/src/lexer/lexer_automata.c

CMakeFiles/qc.dir/src/lexer/lexer_automata.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/lexer/lexer_automata.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/lexer/lexer_automata.c > CMakeFiles/qc.dir/src/lexer/lexer_automata.c.i

CMakeFiles/qc.dir/src/lexer/lexer_automata.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/lexer/lexer_automata.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/lexer/lexer_automata.c -o CMakeFiles/qc.dir/src/lexer/lexer_automata.c.s

CMakeFiles/qc.dir/src/lexer/token.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/lexer/token.c.o: /home/goodman/school/Quest/src/lexer/token.c
CMakeFiles/qc.dir/src/lexer/token.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/qc.dir/src/lexer/token.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/lexer/token.c.o -MF CMakeFiles/qc.dir/src/lexer/token.c.o.d -o CMakeFiles/qc.dir/src/lexer/token.c.o -c /home/goodman/school/Quest/src/lexer/token.c

CMakeFiles/qc.dir/src/lexer/token.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/lexer/token.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/lexer/token.c > CMakeFiles/qc.dir/src/lexer/token.c.i

CMakeFiles/qc.dir/src/lexer/token.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/lexer/token.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/lexer/token.c -o CMakeFiles/qc.dir/src/lexer/token.c.s

CMakeFiles/qc.dir/src/main.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/main.c.o: /home/goodman/school/Quest/src/main.c
CMakeFiles/qc.dir/src/main.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/qc.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/main.c.o -MF CMakeFiles/qc.dir/src/main.c.o.d -o CMakeFiles/qc.dir/src/main.c.o -c /home/goodman/school/Quest/src/main.c

CMakeFiles/qc.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/main.c > CMakeFiles/qc.dir/src/main.c.i

CMakeFiles/qc.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/main.c -o CMakeFiles/qc.dir/src/main.c.s

CMakeFiles/qc.dir/src/parser/grammer.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/grammer.c.o: /home/goodman/school/Quest/src/parser/grammer.c
CMakeFiles/qc.dir/src/parser/grammer.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/qc.dir/src/parser/grammer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/grammer.c.o -MF CMakeFiles/qc.dir/src/parser/grammer.c.o.d -o CMakeFiles/qc.dir/src/parser/grammer.c.o -c /home/goodman/school/Quest/src/parser/grammer.c

CMakeFiles/qc.dir/src/parser/grammer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/grammer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/grammer.c > CMakeFiles/qc.dir/src/parser/grammer.c.i

CMakeFiles/qc.dir/src/parser/grammer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/grammer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/grammer.c -o CMakeFiles/qc.dir/src/parser/grammer.c.s

CMakeFiles/qc.dir/src/parser/item_set.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/item_set.c.o: /home/goodman/school/Quest/src/parser/item_set.c
CMakeFiles/qc.dir/src/parser/item_set.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/qc.dir/src/parser/item_set.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/item_set.c.o -MF CMakeFiles/qc.dir/src/parser/item_set.c.o.d -o CMakeFiles/qc.dir/src/parser/item_set.c.o -c /home/goodman/school/Quest/src/parser/item_set.c

CMakeFiles/qc.dir/src/parser/item_set.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/item_set.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/item_set.c > CMakeFiles/qc.dir/src/parser/item_set.c.i

CMakeFiles/qc.dir/src/parser/item_set.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/item_set.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/item_set.c -o CMakeFiles/qc.dir/src/parser/item_set.c.s

CMakeFiles/qc.dir/src/parser/lr_item.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/lr_item.c.o: /home/goodman/school/Quest/src/parser/lr_item.c
CMakeFiles/qc.dir/src/parser/lr_item.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/qc.dir/src/parser/lr_item.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/lr_item.c.o -MF CMakeFiles/qc.dir/src/parser/lr_item.c.o.d -o CMakeFiles/qc.dir/src/parser/lr_item.c.o -c /home/goodman/school/Quest/src/parser/lr_item.c

CMakeFiles/qc.dir/src/parser/lr_item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/lr_item.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/lr_item.c > CMakeFiles/qc.dir/src/parser/lr_item.c.i

CMakeFiles/qc.dir/src/parser/lr_item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/lr_item.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/lr_item.c -o CMakeFiles/qc.dir/src/parser/lr_item.c.s

CMakeFiles/qc.dir/src/parser/non_terminal.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/non_terminal.c.o: /home/goodman/school/Quest/src/parser/non_terminal.c
CMakeFiles/qc.dir/src/parser/non_terminal.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/qc.dir/src/parser/non_terminal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/non_terminal.c.o -MF CMakeFiles/qc.dir/src/parser/non_terminal.c.o.d -o CMakeFiles/qc.dir/src/parser/non_terminal.c.o -c /home/goodman/school/Quest/src/parser/non_terminal.c

CMakeFiles/qc.dir/src/parser/non_terminal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/non_terminal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/non_terminal.c > CMakeFiles/qc.dir/src/parser/non_terminal.c.i

CMakeFiles/qc.dir/src/parser/non_terminal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/non_terminal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/non_terminal.c -o CMakeFiles/qc.dir/src/parser/non_terminal.c.s

CMakeFiles/qc.dir/src/parser/rule.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/rule.c.o: /home/goodman/school/Quest/src/parser/rule.c
CMakeFiles/qc.dir/src/parser/rule.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/qc.dir/src/parser/rule.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/rule.c.o -MF CMakeFiles/qc.dir/src/parser/rule.c.o.d -o CMakeFiles/qc.dir/src/parser/rule.c.o -c /home/goodman/school/Quest/src/parser/rule.c

CMakeFiles/qc.dir/src/parser/rule.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/rule.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/rule.c > CMakeFiles/qc.dir/src/parser/rule.c.i

CMakeFiles/qc.dir/src/parser/rule.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/rule.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/rule.c -o CMakeFiles/qc.dir/src/parser/rule.c.s

CMakeFiles/qc.dir/src/parser/symbol.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/symbol.c.o: /home/goodman/school/Quest/src/parser/symbol.c
CMakeFiles/qc.dir/src/parser/symbol.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/qc.dir/src/parser/symbol.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/symbol.c.o -MF CMakeFiles/qc.dir/src/parser/symbol.c.o.d -o CMakeFiles/qc.dir/src/parser/symbol.c.o -c /home/goodman/school/Quest/src/parser/symbol.c

CMakeFiles/qc.dir/src/parser/symbol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/symbol.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/symbol.c > CMakeFiles/qc.dir/src/parser/symbol.c.i

CMakeFiles/qc.dir/src/parser/symbol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/symbol.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/symbol.c -o CMakeFiles/qc.dir/src/parser/symbol.c.s

CMakeFiles/qc.dir/src/parser/symbol_set.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/parser/symbol_set.c.o: /home/goodman/school/Quest/src/parser/symbol_set.c
CMakeFiles/qc.dir/src/parser/symbol_set.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/qc.dir/src/parser/symbol_set.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/parser/symbol_set.c.o -MF CMakeFiles/qc.dir/src/parser/symbol_set.c.o.d -o CMakeFiles/qc.dir/src/parser/symbol_set.c.o -c /home/goodman/school/Quest/src/parser/symbol_set.c

CMakeFiles/qc.dir/src/parser/symbol_set.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/parser/symbol_set.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/parser/symbol_set.c > CMakeFiles/qc.dir/src/parser/symbol_set.c.i

CMakeFiles/qc.dir/src/parser/symbol_set.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/parser/symbol_set.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/parser/symbol_set.c -o CMakeFiles/qc.dir/src/parser/symbol_set.c.s

CMakeFiles/qc.dir/src/quest.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/quest.c.o: /home/goodman/school/Quest/src/quest.c
CMakeFiles/qc.dir/src/quest.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/qc.dir/src/quest.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/quest.c.o -MF CMakeFiles/qc.dir/src/quest.c.o.d -o CMakeFiles/qc.dir/src/quest.c.o -c /home/goodman/school/Quest/src/quest.c

CMakeFiles/qc.dir/src/quest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/quest.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/quest.c > CMakeFiles/qc.dir/src/quest.c.i

CMakeFiles/qc.dir/src/quest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/quest.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/quest.c -o CMakeFiles/qc.dir/src/quest.c.s

CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o: /home/goodman/school/Quest/src/utils/DS/generic_set.c
CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o -MF CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o.d -o CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o -c /home/goodman/school/Quest/src/utils/DS/generic_set.c

CMakeFiles/qc.dir/src/utils/DS/generic_set.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/DS/generic_set.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/DS/generic_set.c > CMakeFiles/qc.dir/src/utils/DS/generic_set.c.i

CMakeFiles/qc.dir/src/utils/DS/generic_set.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/DS/generic_set.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/DS/generic_set.c -o CMakeFiles/qc.dir/src/utils/DS/generic_set.c.s

CMakeFiles/qc.dir/src/utils/DS/hashset.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/DS/hashset.c.o: /home/goodman/school/Quest/src/utils/DS/hashset.c
CMakeFiles/qc.dir/src/utils/DS/hashset.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/qc.dir/src/utils/DS/hashset.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/DS/hashset.c.o -MF CMakeFiles/qc.dir/src/utils/DS/hashset.c.o.d -o CMakeFiles/qc.dir/src/utils/DS/hashset.c.o -c /home/goodman/school/Quest/src/utils/DS/hashset.c

CMakeFiles/qc.dir/src/utils/DS/hashset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/DS/hashset.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/DS/hashset.c > CMakeFiles/qc.dir/src/utils/DS/hashset.c.i

CMakeFiles/qc.dir/src/utils/DS/hashset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/DS/hashset.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/DS/hashset.c -o CMakeFiles/qc.dir/src/utils/DS/hashset.c.s

CMakeFiles/qc.dir/src/utils/DS/queue.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/DS/queue.c.o: /home/goodman/school/Quest/src/utils/DS/queue.c
CMakeFiles/qc.dir/src/utils/DS/queue.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/qc.dir/src/utils/DS/queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/DS/queue.c.o -MF CMakeFiles/qc.dir/src/utils/DS/queue.c.o.d -o CMakeFiles/qc.dir/src/utils/DS/queue.c.o -c /home/goodman/school/Quest/src/utils/DS/queue.c

CMakeFiles/qc.dir/src/utils/DS/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/DS/queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/DS/queue.c > CMakeFiles/qc.dir/src/utils/DS/queue.c.i

CMakeFiles/qc.dir/src/utils/DS/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/DS/queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/DS/queue.c -o CMakeFiles/qc.dir/src/utils/DS/queue.c.s

CMakeFiles/qc.dir/src/utils/DS/stack.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/DS/stack.c.o: /home/goodman/school/Quest/src/utils/DS/stack.c
CMakeFiles/qc.dir/src/utils/DS/stack.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object CMakeFiles/qc.dir/src/utils/DS/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/DS/stack.c.o -MF CMakeFiles/qc.dir/src/utils/DS/stack.c.o.d -o CMakeFiles/qc.dir/src/utils/DS/stack.c.o -c /home/goodman/school/Quest/src/utils/DS/stack.c

CMakeFiles/qc.dir/src/utils/DS/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/DS/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/DS/stack.c > CMakeFiles/qc.dir/src/utils/DS/stack.c.i

CMakeFiles/qc.dir/src/utils/DS/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/DS/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/DS/stack.c -o CMakeFiles/qc.dir/src/utils/DS/stack.c.s

CMakeFiles/qc.dir/src/utils/err/err.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/err/err.c.o: /home/goodman/school/Quest/src/utils/err/err.c
CMakeFiles/qc.dir/src/utils/err/err.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building C object CMakeFiles/qc.dir/src/utils/err/err.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/err/err.c.o -MF CMakeFiles/qc.dir/src/utils/err/err.c.o.d -o CMakeFiles/qc.dir/src/utils/err/err.c.o -c /home/goodman/school/Quest/src/utils/err/err.c

CMakeFiles/qc.dir/src/utils/err/err.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/err/err.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/err/err.c > CMakeFiles/qc.dir/src/utils/err/err.c.i

CMakeFiles/qc.dir/src/utils/err/err.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/err/err.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/err/err.c -o CMakeFiles/qc.dir/src/utils/err/err.c.s

CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o: /home/goodman/school/Quest/src/utils/lexer_DFA/lexer_DFA.c
CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building C object CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o -MF CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o.d -o CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o -c /home/goodman/school/Quest/src/utils/lexer_DFA/lexer_DFA.c

CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/lexer_DFA/lexer_DFA.c > CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.i

CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/lexer_DFA/lexer_DFA.c -o CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.s

CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o: CMakeFiles/qc.dir/flags.make
CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o: /home/goodman/school/Quest/src/utils/lexer_DFA/transitions.c
CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o: CMakeFiles/qc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building C object CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o -MF CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o.d -o CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o -c /home/goodman/school/Quest/src/utils/lexer_DFA/transitions.c

CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/goodman/school/Quest/src/utils/lexer_DFA/transitions.c > CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.i

CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/goodman/school/Quest/src/utils/lexer_DFA/transitions.c -o CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.s

# Object files for target qc
qc_OBJECTS = \
"CMakeFiles/qc.dir/src/io.c.o" \
"CMakeFiles/qc.dir/src/lexer/lexer.c.o" \
"CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o" \
"CMakeFiles/qc.dir/src/lexer/token.c.o" \
"CMakeFiles/qc.dir/src/main.c.o" \
"CMakeFiles/qc.dir/src/parser/grammer.c.o" \
"CMakeFiles/qc.dir/src/parser/item_set.c.o" \
"CMakeFiles/qc.dir/src/parser/lr_item.c.o" \
"CMakeFiles/qc.dir/src/parser/non_terminal.c.o" \
"CMakeFiles/qc.dir/src/parser/rule.c.o" \
"CMakeFiles/qc.dir/src/parser/symbol.c.o" \
"CMakeFiles/qc.dir/src/parser/symbol_set.c.o" \
"CMakeFiles/qc.dir/src/quest.c.o" \
"CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o" \
"CMakeFiles/qc.dir/src/utils/DS/hashset.c.o" \
"CMakeFiles/qc.dir/src/utils/DS/queue.c.o" \
"CMakeFiles/qc.dir/src/utils/DS/stack.c.o" \
"CMakeFiles/qc.dir/src/utils/err/err.c.o" \
"CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o" \
"CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o"

# External object files for target qc
qc_EXTERNAL_OBJECTS =

qc: CMakeFiles/qc.dir/src/io.c.o
qc: CMakeFiles/qc.dir/src/lexer/lexer.c.o
qc: CMakeFiles/qc.dir/src/lexer/lexer_automata.c.o
qc: CMakeFiles/qc.dir/src/lexer/token.c.o
qc: CMakeFiles/qc.dir/src/main.c.o
qc: CMakeFiles/qc.dir/src/parser/grammer.c.o
qc: CMakeFiles/qc.dir/src/parser/item_set.c.o
qc: CMakeFiles/qc.dir/src/parser/lr_item.c.o
qc: CMakeFiles/qc.dir/src/parser/non_terminal.c.o
qc: CMakeFiles/qc.dir/src/parser/rule.c.o
qc: CMakeFiles/qc.dir/src/parser/symbol.c.o
qc: CMakeFiles/qc.dir/src/parser/symbol_set.c.o
qc: CMakeFiles/qc.dir/src/quest.c.o
qc: CMakeFiles/qc.dir/src/utils/DS/generic_set.c.o
qc: CMakeFiles/qc.dir/src/utils/DS/hashset.c.o
qc: CMakeFiles/qc.dir/src/utils/DS/queue.c.o
qc: CMakeFiles/qc.dir/src/utils/DS/stack.c.o
qc: CMakeFiles/qc.dir/src/utils/err/err.c.o
qc: CMakeFiles/qc.dir/src/utils/lexer_DFA/lexer_DFA.c.o
qc: CMakeFiles/qc.dir/src/utils/lexer_DFA/transitions.c.o
qc: CMakeFiles/qc.dir/build.make
qc: CMakeFiles/qc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/goodman/school/Quest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Linking C executable qc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qc.dir/build: qc
.PHONY : CMakeFiles/qc.dir/build

CMakeFiles/qc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qc.dir/clean

CMakeFiles/qc.dir/depend:
	cd /home/goodman/school/Quest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/goodman/school/Quest /home/goodman/school/Quest /home/goodman/school/Quest/build /home/goodman/school/Quest/build /home/goodman/school/Quest/build/CMakeFiles/qc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qc.dir/depend

