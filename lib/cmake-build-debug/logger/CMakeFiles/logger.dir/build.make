# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/alexandr/Downloads/clion-2020.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alexandr/Downloads/clion-2020.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug

# Include any dependencies generated for this target.
include logger/CMakeFiles/logger.dir/depend.make

# Include the progress variables for this target.
include logger/CMakeFiles/logger.dir/progress.make

# Include the compile flags for this target's objects.
include logger/CMakeFiles/logger.dir/flags.make

logger/CMakeFiles/logger.dir/src/BaseLogger.o: logger/CMakeFiles/logger.dir/flags.make
logger/CMakeFiles/logger.dir/src/BaseLogger.o: ../logger/src/BaseLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object logger/CMakeFiles/logger.dir/src/BaseLogger.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/src/BaseLogger.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/BaseLogger.cpp

logger/CMakeFiles/logger.dir/src/BaseLogger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/src/BaseLogger.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/BaseLogger.cpp > CMakeFiles/logger.dir/src/BaseLogger.i

logger/CMakeFiles/logger.dir/src/BaseLogger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/src/BaseLogger.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/BaseLogger.cpp -o CMakeFiles/logger.dir/src/BaseLogger.s

logger/CMakeFiles/logger.dir/src/StderrLogger.o: logger/CMakeFiles/logger.dir/flags.make
logger/CMakeFiles/logger.dir/src/StderrLogger.o: ../logger/src/StderrLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object logger/CMakeFiles/logger.dir/src/StderrLogger.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/src/StderrLogger.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StderrLogger.cpp

logger/CMakeFiles/logger.dir/src/StderrLogger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/src/StderrLogger.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StderrLogger.cpp > CMakeFiles/logger.dir/src/StderrLogger.i

logger/CMakeFiles/logger.dir/src/StderrLogger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/src/StderrLogger.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StderrLogger.cpp -o CMakeFiles/logger.dir/src/StderrLogger.s

logger/CMakeFiles/logger.dir/src/StdoutLogger.o: logger/CMakeFiles/logger.dir/flags.make
logger/CMakeFiles/logger.dir/src/StdoutLogger.o: ../logger/src/StdoutLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object logger/CMakeFiles/logger.dir/src/StdoutLogger.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/src/StdoutLogger.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StdoutLogger.cpp

logger/CMakeFiles/logger.dir/src/StdoutLogger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/src/StdoutLogger.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StdoutLogger.cpp > CMakeFiles/logger.dir/src/StdoutLogger.i

logger/CMakeFiles/logger.dir/src/StdoutLogger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/src/StdoutLogger.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/StdoutLogger.cpp -o CMakeFiles/logger.dir/src/StdoutLogger.s

logger/CMakeFiles/logger.dir/src/FileLogger.o: logger/CMakeFiles/logger.dir/flags.make
logger/CMakeFiles/logger.dir/src/FileLogger.o: ../logger/src/FileLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object logger/CMakeFiles/logger.dir/src/FileLogger.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/src/FileLogger.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/FileLogger.cpp

logger/CMakeFiles/logger.dir/src/FileLogger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/src/FileLogger.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/FileLogger.cpp > CMakeFiles/logger.dir/src/FileLogger.i

logger/CMakeFiles/logger.dir/src/FileLogger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/src/FileLogger.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/FileLogger.cpp -o CMakeFiles/logger.dir/src/FileLogger.s

logger/CMakeFiles/logger.dir/src/Logger.o: logger/CMakeFiles/logger.dir/flags.make
logger/CMakeFiles/logger.dir/src/Logger.o: ../logger/src/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object logger/CMakeFiles/logger.dir/src/Logger.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/src/Logger.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/Logger.cpp

logger/CMakeFiles/logger.dir/src/Logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/src/Logger.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/Logger.cpp > CMakeFiles/logger.dir/src/Logger.i

logger/CMakeFiles/logger.dir/src/Logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/src/Logger.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger/src/Logger.cpp -o CMakeFiles/logger.dir/src/Logger.s

# Object files for target logger
logger_OBJECTS = \
"CMakeFiles/logger.dir/src/BaseLogger.o" \
"CMakeFiles/logger.dir/src/StderrLogger.o" \
"CMakeFiles/logger.dir/src/StdoutLogger.o" \
"CMakeFiles/logger.dir/src/FileLogger.o" \
"CMakeFiles/logger.dir/src/Logger.o"

# External object files for target logger
logger_EXTERNAL_OBJECTS =

logger/liblogger.a: logger/CMakeFiles/logger.dir/src/BaseLogger.o
logger/liblogger.a: logger/CMakeFiles/logger.dir/src/StderrLogger.o
logger/liblogger.a: logger/CMakeFiles/logger.dir/src/StdoutLogger.o
logger/liblogger.a: logger/CMakeFiles/logger.dir/src/FileLogger.o
logger/liblogger.a: logger/CMakeFiles/logger.dir/src/Logger.o
logger/liblogger.a: logger/CMakeFiles/logger.dir/build.make
logger/liblogger.a: logger/CMakeFiles/logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library liblogger.a"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean_target.cmake
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
logger/CMakeFiles/logger.dir/build: logger/liblogger.a

.PHONY : logger/CMakeFiles/logger.dir/build

logger/CMakeFiles/logger.dir/clean:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean.cmake
.PHONY : logger/CMakeFiles/logger.dir/clean

logger/CMakeFiles/logger.dir/depend:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/logger /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/logger/CMakeFiles/logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : logger/CMakeFiles/logger.dir/depend

