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
include SeggerRTT/CMakeFiles/Segger_RTT.dir/depend.make
# Include the progress variables for this target.
include SeggerRTT/CMakeFiles/Segger_RTT.dir/progress.make

# Include the compile flags for this target's objects.
include SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/RTT/SEGGER_RTT.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT.c.lst" -o CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT.c" > CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT.c" -o CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT.c.s

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/RTT/SEGGER_RTT_printf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_printf.c.lst" -o CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT_printf.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT_printf.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_printf.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT_printf.c" > CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT_printf.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_printf.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\RTT\SEGGER_RTT_printf.c" -o CMakeFiles\Segger_RTT.dir\RTT\SEGGER_RTT_printf.c.s

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_GCC.c.lst" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_GCC.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_GCC.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_GCC.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_GCC.c" > CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_GCC.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_GCC.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_GCC.c" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_GCC.c.s

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_IAR.c.lst" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_IAR.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_IAR.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_IAR.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_IAR.c" > CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_IAR.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_IAR.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_IAR.c" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_IAR.c.s

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_KEIL.c.lst" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_KEIL.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_KEIL.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_KEIL.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_KEIL.c" > CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_KEIL.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_KEIL.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_KEIL.c" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_KEIL.c.s

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/flags.make
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj: SeggerRTT/CMakeFiles/Segger_RTT.dir/includes_C.rsp
SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj: C:/Users/niels/Documents/Elektrotechniek/Jaar\ 2/ECS/ECSL/software/STM32/STM32Basis/Segger/Segger_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_SES.c.lst" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_SES.c.obj -c "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_SES.c"

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.i"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_SES.c.lst" -E "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_SES.c" > CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_SES.c.i

SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.s"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && C:\PROGRA~2\GNUARM~1\102021~1.10\bin\AR10B2~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wa,-ahl="C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/SEGGER_RTT_Syscalls_SES.c.lst" -S "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT\Syscalls\SEGGER_RTT_Syscalls_SES.c" -o CMakeFiles\Segger_RTT.dir\Syscalls\SEGGER_RTT_Syscalls_SES.c.s

# Object files for target Segger_RTT
Segger_RTT_OBJECTS = \
"CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj" \
"CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj" \
"CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj" \
"CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj" \
"CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj" \
"CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj"

# External object files for target Segger_RTT
Segger_RTT_EXTERNAL_OBJECTS =

SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/RTT/SEGGER_RTT_printf.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_GCC.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_IAR.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_KEIL.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/Syscalls/SEGGER_RTT_Syscalls_SES.c.obj
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/build.make
SeggerRTT/libSegger_RTT.a: SeggerRTT/CMakeFiles/Segger_RTT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking C static library libSegger_RTT.a"
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && $(CMAKE_COMMAND) -P CMakeFiles\Segger_RTT.dir\cmake_clean_target.cmake
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Segger_RTT.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SeggerRTT/CMakeFiles/Segger_RTT.dir/build: SeggerRTT/libSegger_RTT.a
.PHONY : SeggerRTT/CMakeFiles/Segger_RTT.dir/build

SeggerRTT/CMakeFiles/Segger_RTT.dir/clean:
	cd /d C:\Users\niels\DOCUME~1\ELEKTR~1\JAAR2~1\ECS\ECSL\software\STM32\PRACTI~1\CLion\SIZERE~1\SEGGER~1 && $(CMAKE_COMMAND) -P CMakeFiles\Segger_RTT.dir\cmake_clean.cmake
.PHONY : SeggerRTT/CMakeFiles/Segger_RTT.dir/clean

SeggerRTT/CMakeFiles/Segger_RTT.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\STM32Basis\Segger\Segger_RTT" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\SeggerRTT" "C:\Users\niels\Documents\Elektrotechniek\Jaar 2\ECS\ECSL\software\STM32\Practicum_STM32F412DiscoveryBoard\CLion\SizeRelease\SeggerRTT\CMakeFiles\Segger_RTT.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : SeggerRTT/CMakeFiles/Segger_RTT.dir/depend

