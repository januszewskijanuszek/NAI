# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\s22638\Downloads\NAI-main\lab7\part2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/part2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/part2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/part2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/part2.dir/flags.make

CMakeFiles/part2.dir/main.cpp.obj: CMakeFiles/part2.dir/flags.make
CMakeFiles/part2.dir/main.cpp.obj: CMakeFiles/part2.dir/includes_CXX.rsp
CMakeFiles/part2.dir/main.cpp.obj: ../main.cpp
CMakeFiles/part2.dir/main.cpp.obj: CMakeFiles/part2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/part2.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/part2.dir/main.cpp.obj -MF CMakeFiles\part2.dir\main.cpp.obj.d -o CMakeFiles\part2.dir\main.cpp.obj -c C:\Users\s22638\Downloads\NAI-main\lab7\part2\main.cpp

CMakeFiles/part2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/part2.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\s22638\Downloads\NAI-main\lab7\part2\main.cpp > CMakeFiles\part2.dir\main.cpp.i

CMakeFiles/part2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/part2.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\s22638\Downloads\NAI-main\lab7\part2\main.cpp -o CMakeFiles\part2.dir\main.cpp.s

# Object files for target part2
part2_OBJECTS = \
"CMakeFiles/part2.dir/main.cpp.obj"

# External object files for target part2
part2_EXTERNAL_OBJECTS =

part2.exe: CMakeFiles/part2.dir/main.cpp.obj
part2.exe: CMakeFiles/part2.dir/build.make
part2.exe: C:/Users/s22638/Downloads/NAI-main/lab7/opencv-4.x/cmake-build-release/lib/libopencv_highgui460.dll.a
part2.exe: C:/Users/s22638/Downloads/NAI-main/lab7/opencv-4.x/cmake-build-release/lib/libopencv_videoio460.dll.a
part2.exe: C:/Users/s22638/Downloads/NAI-main/lab7/opencv-4.x/cmake-build-release/lib/libopencv_imgcodecs460.dll.a
part2.exe: C:/Users/s22638/Downloads/NAI-main/lab7/opencv-4.x/cmake-build-release/lib/libopencv_imgproc460.dll.a
part2.exe: C:/Users/s22638/Downloads/NAI-main/lab7/opencv-4.x/cmake-build-release/lib/libopencv_core460.dll.a
part2.exe: CMakeFiles/part2.dir/linklibs.rsp
part2.exe: CMakeFiles/part2.dir/objects1.rsp
part2.exe: CMakeFiles/part2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable part2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\part2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/part2.dir/build: part2.exe
.PHONY : CMakeFiles/part2.dir/build

CMakeFiles/part2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\part2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/part2.dir/clean

CMakeFiles/part2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\s22638\Downloads\NAI-main\lab7\part2 C:\Users\s22638\Downloads\NAI-main\lab7\part2 C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug C:\Users\s22638\Downloads\NAI-main\lab7\part2\cmake-build-debug\CMakeFiles\part2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/part2.dir/depend

