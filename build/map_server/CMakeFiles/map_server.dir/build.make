# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/boocax/UstarService/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/boocax/UstarService/build

# Include any dependencies generated for this target.
include map_server/CMakeFiles/map_server.dir/depend.make

# Include the progress variables for this target.
include map_server/CMakeFiles/map_server.dir/progress.make

# Include the compile flags for this target's objects.
include map_server/CMakeFiles/map_server.dir/flags.make

map_server/CMakeFiles/map_server.dir/src/main.cpp.o: map_server/CMakeFiles/map_server.dir/flags.make
map_server/CMakeFiles/map_server.dir/src/main.cpp.o: /home/boocax/UstarService/src/map_server/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object map_server/CMakeFiles/map_server.dir/src/main.cpp.o"
	cd /home/boocax/UstarService/build/map_server && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/map_server.dir/src/main.cpp.o -c /home/boocax/UstarService/src/map_server/src/main.cpp

map_server/CMakeFiles/map_server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/map_server.dir/src/main.cpp.i"
	cd /home/boocax/UstarService/build/map_server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map_server/src/main.cpp > CMakeFiles/map_server.dir/src/main.cpp.i

map_server/CMakeFiles/map_server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/map_server.dir/src/main.cpp.s"
	cd /home/boocax/UstarService/build/map_server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map_server/src/main.cpp -o CMakeFiles/map_server.dir/src/main.cpp.s

map_server/CMakeFiles/map_server.dir/src/main.cpp.o.requires:

.PHONY : map_server/CMakeFiles/map_server.dir/src/main.cpp.o.requires

map_server/CMakeFiles/map_server.dir/src/main.cpp.o.provides: map_server/CMakeFiles/map_server.dir/src/main.cpp.o.requires
	$(MAKE) -f map_server/CMakeFiles/map_server.dir/build.make map_server/CMakeFiles/map_server.dir/src/main.cpp.o.provides.build
.PHONY : map_server/CMakeFiles/map_server.dir/src/main.cpp.o.provides

map_server/CMakeFiles/map_server.dir/src/main.cpp.o.provides.build: map_server/CMakeFiles/map_server.dir/src/main.cpp.o


# Object files for target map_server
map_server_OBJECTS = \
"CMakeFiles/map_server.dir/src/main.cpp.o"

# External object files for target map_server
map_server_EXTERNAL_OBJECTS =

/home/boocax/UstarService/devel/lib/map_server/map_server: map_server/CMakeFiles/map_server.dir/src/main.cpp.o
/home/boocax/UstarService/devel/lib/map_server/map_server: map_server/CMakeFiles/map_server.dir/build.make
/home/boocax/UstarService/devel/lib/map_server/map_server: /home/boocax/UstarService/devel/lib/libmap_server_image_loader.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libroscpp.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libtf2.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librostime.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libcpp_common.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libBulletDynamics.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libLinearMath.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libBulletSoftBody.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libSDLmain.a
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libSDL.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libSDL_image.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libroscpp.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libtf2.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/librostime.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /opt/ros/kinetic/lib/libcpp_common.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/boocax/UstarService/devel/lib/map_server/map_server: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/boocax/UstarService/devel/lib/map_server/map_server: map_server/CMakeFiles/map_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/boocax/UstarService/devel/lib/map_server/map_server"
	cd /home/boocax/UstarService/build/map_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/map_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
map_server/CMakeFiles/map_server.dir/build: /home/boocax/UstarService/devel/lib/map_server/map_server

.PHONY : map_server/CMakeFiles/map_server.dir/build

map_server/CMakeFiles/map_server.dir/requires: map_server/CMakeFiles/map_server.dir/src/main.cpp.o.requires

.PHONY : map_server/CMakeFiles/map_server.dir/requires

map_server/CMakeFiles/map_server.dir/clean:
	cd /home/boocax/UstarService/build/map_server && $(CMAKE_COMMAND) -P CMakeFiles/map_server.dir/cmake_clean.cmake
.PHONY : map_server/CMakeFiles/map_server.dir/clean

map_server/CMakeFiles/map_server.dir/depend:
	cd /home/boocax/UstarService/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/boocax/UstarService/src /home/boocax/UstarService/src/map_server /home/boocax/UstarService/build /home/boocax/UstarService/build/map_server /home/boocax/UstarService/build/map_server/CMakeFiles/map_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : map_server/CMakeFiles/map_server.dir/depend

