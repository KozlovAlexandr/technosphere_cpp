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
include http/CMakeFiles/http_server.dir/depend.make

# Include the progress variables for this target.
include http/CMakeFiles/http_server.dir/progress.make

# Include the compile flags for this target's objects.
include http/CMakeFiles/http_server.dir/flags.make

http/CMakeFiles/http_server.dir/example/http_server.o: http/CMakeFiles/http_server.dir/flags.make
http/CMakeFiles/http_server.dir/example/http_server.o: ../http/example/http_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object http/CMakeFiles/http_server.dir/example/http_server.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http_server.dir/example/http_server.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/example/http_server.cpp

http/CMakeFiles/http_server.dir/example/http_server.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http_server.dir/example/http_server.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/example/http_server.cpp > CMakeFiles/http_server.dir/example/http_server.i

http/CMakeFiles/http_server.dir/example/http_server.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http_server.dir/example/http_server.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/example/http_server.cpp -o CMakeFiles/http_server.dir/example/http_server.s

# Object files for target http_server
http_server_OBJECTS = \
"CMakeFiles/http_server.dir/example/http_server.o"

# External object files for target http_server
http_server_EXTERNAL_OBJECTS =

http/http_server: http/CMakeFiles/http_server.dir/example/http_server.o
http/http_server: http/CMakeFiles/http_server.dir/build.make
http/http_server: http/libhttp.a
http/http_server: net/libnet.a
http/http_server: tcp/libtcp.a
http/http_server: logger/liblogger.a
http/http_server: http/CMakeFiles/http_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable http_server"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
http/CMakeFiles/http_server.dir/build: http/http_server

.PHONY : http/CMakeFiles/http_server.dir/build

http/CMakeFiles/http_server.dir/clean:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && $(CMAKE_COMMAND) -P CMakeFiles/http_server.dir/cmake_clean.cmake
.PHONY : http/CMakeFiles/http_server.dir/clean

http/CMakeFiles/http_server.dir/depend:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http/CMakeFiles/http_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : http/CMakeFiles/http_server.dir/depend

