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
include map/CMakeFiles/sensor.dir/depend.make

# Include the progress variables for this target.
include map/CMakeFiles/sensor.dir/progress.make

# Include the compile flags for this target's objects.
include map/CMakeFiles/sensor.dir/flags.make

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o: map/CMakeFiles/sensor.dir/flags.make
map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o: /home/boocax/UstarService/src/map/src/gmapping/sensor/rangesensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o -c /home/boocax/UstarService/src/map/src/gmapping/sensor/rangesensor.cpp

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.i"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map/src/gmapping/sensor/rangesensor.cpp > CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.i

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.s"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map/src/gmapping/sensor/rangesensor.cpp -o CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.s

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.requires:

.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.requires

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.provides: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.requires
	$(MAKE) -f map/CMakeFiles/sensor.dir/build.make map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.provides.build
.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.provides

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.provides.build: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o


map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o: map/CMakeFiles/sensor.dir/flags.make
map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o: /home/boocax/UstarService/src/map/src/gmapping/sensor/odometrysensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o -c /home/boocax/UstarService/src/map/src/gmapping/sensor/odometrysensor.cpp

map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.i"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map/src/gmapping/sensor/odometrysensor.cpp > CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.i

map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.s"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map/src/gmapping/sensor/odometrysensor.cpp -o CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.s

map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.requires:

.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.requires

map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.provides: map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.requires
	$(MAKE) -f map/CMakeFiles/sensor.dir/build.make map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.provides.build
.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.provides

map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.provides.build: map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o


map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o: map/CMakeFiles/sensor.dir/flags.make
map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o: /home/boocax/UstarService/src/map/src/gmapping/sensor/rangereading.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o -c /home/boocax/UstarService/src/map/src/gmapping/sensor/rangereading.cpp

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.i"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map/src/gmapping/sensor/rangereading.cpp > CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.i

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.s"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map/src/gmapping/sensor/rangereading.cpp -o CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.s

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.requires:

.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.requires

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.provides: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.requires
	$(MAKE) -f map/CMakeFiles/sensor.dir/build.make map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.provides.build
.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.provides

map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.provides.build: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o


map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o: map/CMakeFiles/sensor.dir/flags.make
map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o: /home/boocax/UstarService/src/map/src/gmapping/sensor/sensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o -c /home/boocax/UstarService/src/map/src/gmapping/sensor/sensor.cpp

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.i"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map/src/gmapping/sensor/sensor.cpp > CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.i

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.s"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map/src/gmapping/sensor/sensor.cpp -o CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.s

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.requires:

.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.requires

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.provides: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.requires
	$(MAKE) -f map/CMakeFiles/sensor.dir/build.make map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.provides.build
.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.provides

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.provides.build: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o


map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o: map/CMakeFiles/sensor.dir/flags.make
map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o: /home/boocax/UstarService/src/map/src/gmapping/sensor/sensorreading.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o -c /home/boocax/UstarService/src/map/src/gmapping/sensor/sensorreading.cpp

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.i"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boocax/UstarService/src/map/src/gmapping/sensor/sensorreading.cpp > CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.i

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.s"
	cd /home/boocax/UstarService/build/map && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boocax/UstarService/src/map/src/gmapping/sensor/sensorreading.cpp -o CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.s

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.requires:

.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.requires

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.provides: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.requires
	$(MAKE) -f map/CMakeFiles/sensor.dir/build.make map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.provides.build
.PHONY : map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.provides

map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.provides.build: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o


# Object files for target sensor
sensor_OBJECTS = \
"CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o" \
"CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o" \
"CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o" \
"CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o" \
"CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o"

# External object files for target sensor
sensor_EXTERNAL_OBJECTS =

/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/build.make
/home/boocax/UstarService/devel/lib/libsensor.so: map/CMakeFiles/sensor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/boocax/UstarService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library /home/boocax/UstarService/devel/lib/libsensor.so"
	cd /home/boocax/UstarService/build/map && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sensor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
map/CMakeFiles/sensor.dir/build: /home/boocax/UstarService/devel/lib/libsensor.so

.PHONY : map/CMakeFiles/sensor.dir/build

map/CMakeFiles/sensor.dir/requires: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangesensor.cpp.o.requires
map/CMakeFiles/sensor.dir/requires: map/CMakeFiles/sensor.dir/src/gmapping/sensor/odometrysensor.cpp.o.requires
map/CMakeFiles/sensor.dir/requires: map/CMakeFiles/sensor.dir/src/gmapping/sensor/rangereading.cpp.o.requires
map/CMakeFiles/sensor.dir/requires: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensor.cpp.o.requires
map/CMakeFiles/sensor.dir/requires: map/CMakeFiles/sensor.dir/src/gmapping/sensor/sensorreading.cpp.o.requires

.PHONY : map/CMakeFiles/sensor.dir/requires

map/CMakeFiles/sensor.dir/clean:
	cd /home/boocax/UstarService/build/map && $(CMAKE_COMMAND) -P CMakeFiles/sensor.dir/cmake_clean.cmake
.PHONY : map/CMakeFiles/sensor.dir/clean

map/CMakeFiles/sensor.dir/depend:
	cd /home/boocax/UstarService/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/boocax/UstarService/src /home/boocax/UstarService/src/map /home/boocax/UstarService/build /home/boocax/UstarService/build/map /home/boocax/UstarService/build/map/CMakeFiles/sensor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : map/CMakeFiles/sensor.dir/depend

