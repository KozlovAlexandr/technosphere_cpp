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
include http/CMakeFiles/http.dir/depend.make

# Include the progress variables for this target.
include http/CMakeFiles/http.dir/progress.make

# Include the compile flags for this target's objects.
include http/CMakeFiles/http.dir/flags.make

http/CMakeFiles/http.dir/src/http_server.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/src/http_server.o: ../http/src/http_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object http/CMakeFiles/http.dir/src/http_server.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/src/http_server.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_server.cpp

http/CMakeFiles/http.dir/src/http_server.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/src/http_server.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_server.cpp > CMakeFiles/http.dir/src/http_server.i

http/CMakeFiles/http.dir/src/http_server.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/src/http_server.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_server.cpp -o CMakeFiles/http.dir/src/http_server.s

http/CMakeFiles/http.dir/src/http_connection.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/src/http_connection.o: ../http/src/http_connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object http/CMakeFiles/http.dir/src/http_connection.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/src/http_connection.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_connection.cpp

http/CMakeFiles/http.dir/src/http_connection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/src/http_connection.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_connection.cpp > CMakeFiles/http.dir/src/http_connection.i

http/CMakeFiles/http.dir/src/http_connection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/src/http_connection.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http_connection.cpp -o CMakeFiles/http.dir/src/http_connection.s

http/CMakeFiles/http.dir/src/http.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/src/http.o: ../http/src/http.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object http/CMakeFiles/http.dir/src/http.o"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/src/http.o -c /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http.cpp

http/CMakeFiles/http.dir/src/http.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/src/http.i"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http.cpp > CMakeFiles/http.dir/src/http.i

http/CMakeFiles/http.dir/src/http.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/src/http.s"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http/src/http.cpp -o CMakeFiles/http.dir/src/http.s

# Object files for target http
http_OBJECTS = \
"CMakeFiles/http.dir/src/http_server.o" \
"CMakeFiles/http.dir/src/http_connection.o" \
"CMakeFiles/http.dir/src/http.o"

# External object files for target http
http_EXTERNAL_OBJECTS =

http/libhttp.a: http/CMakeFiles/http.dir/src/http_server.o
http/libhttp.a: http/CMakeFiles/http.dir/src/http_connection.o
http/libhttp.a: http/CMakeFiles/http.dir/src/http.o
http/libhttp.a: http/CMakeFiles/http.dir/build.make
http/libhttp.a: http/CMakeFiles/http.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libhttp.a"
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && $(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean_target.cmake
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
http/CMakeFiles/http.dir/build: http/libhttp.a

.PHONY : http/CMakeFiles/http.dir/build

http/CMakeFiles/http.dir/clean:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http && $(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean.cmake
.PHONY : http/CMakeFiles/http.dir/clean

http/CMakeFiles/http.dir/depend:
	cd /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/http /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http /home/alexandr/CLionProjects/Sphere/sphere_cpp/lib/cmake-build-debug/http/CMakeFiles/http.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : http/CMakeFiles/http.dir/depend
