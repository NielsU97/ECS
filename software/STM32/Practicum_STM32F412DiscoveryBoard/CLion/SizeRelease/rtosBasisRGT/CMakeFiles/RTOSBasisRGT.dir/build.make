# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease"

# Include any dependencies generated for this target.
include rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/depend.make
# Include the progress variables for this target.
include rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/progress.make

# Include the compile flags for this target's objects.
include rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/flags.make

rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj: rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/flags.make
rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj: rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/includes_CXX.rsp
rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj: ../../rtosBasisRGT/rtosTaak.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RTOSBasisRGT.dir\rtosTaak.cpp.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\rtosBasisRGT\rtosTaak.cpp"

rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\rtosBasisRGT\rtosTaak.cpp" > CMakeFiles\RTOSBasisRGT.dir\rtosTaak.cpp.i

rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\rtosBasisRGT\rtosTaak.cpp" -o CMakeFiles\RTOSBasisRGT.dir\rtosTaak.cpp.s

# Object files for target RTOSBasisRGT
RTOSBasisRGT_OBJECTS = \
"CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj"

# External object files for target RTOSBasisRGT
RTOSBasisRGT_EXTERNAL_OBJECTS =

rtosBasisRGT/libRTOSBasisRGT.a: rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/rtosTaak.cpp.obj
rtosBasisRGT/libRTOSBasisRGT.a: rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/build.make
rtosBasisRGT/libRTOSBasisRGT.a: rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libRTOSBasisRGT.a"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && $(CMAKE_COMMAND) -P CMakeFiles\RTOSBasisRGT.dir\cmake_clean_target.cmake
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RTOSBasisRGT.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/build: rtosBasisRGT/libRTOSBasisRGT.a
.PHONY : rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/build

rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/clean:
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\RTOSBA~1 && $(CMAKE_COMMAND) -P CMakeFiles\RTOSBasisRGT.dir\cmake_clean.cmake
.PHONY : rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/clean

rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\rtosBasisRGT" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\rtosBasisRGT" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\rtosBasisRGT\CMakeFiles\RTOSBasisRGT.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : rtosBasisRGT/CMakeFiles/RTOSBasisRGT.dir/depend

