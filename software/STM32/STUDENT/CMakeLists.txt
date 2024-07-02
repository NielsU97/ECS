## Boombaard generated CMakelists add_library file
## File generated on : 2018-02-28 11:13:27.

# define minimum cmake version.
cmake_minimum_required(VERSION 3.10.4)

# The absolute path for this CMakeLists.txt file is : "C:\Users\ewout\home\vakken\ti_cp\regeltechniek\practicum\rgtpracticum\software\STM32\RGT+DSB_Board\practicum\regeltechniek"
set(LibName studentspullen)

set(SrcPath0 ${CMAKE_CURRENT_SOURCE_DIR}/h)
set(SrcPath1 ${CMAKE_CURRENT_SOURCE_DIR}/.)

set(AllIncludeDirs ${SrcPath0} )
include_directories(${AllIncludeDirs})


if (${practicumopdracht} STREQUAL "DebugOpdracht")
	message(STATUS "Debugpracticum wordt gebouwd.")
	message(STATUS "Debug assignment is being built.")
	set(opdracht debugpracticum)

	set(SRCS debugSessie.cpp support/debugTaak.cpp)

else(${practicumopdracht} STREQUAL "DebugOpdracht")

	set(SRCS InputResponsieSessie.cpp support/RGTTaak.cpp support/RGTBoard.cpp)

	if((${practicumopdracht} STREQUAL "InputResponsieOpdracht") )
		message(STATUS "Regeltechniek [inputresponsie] wordt gebouwd.")
		message(STATUS "Control Engineering [input response] assignment is being built.")
	elseif((${practicumopdracht} STREQUAL "PIDControllerOpdracht"))
		message(STATUS "Regeltechniek [PID controller] wordt gebouwd.")
		message(STATUS "Control Engineering [PID controller] assignment is being built.")
		set(opdracht regeltechniek)
		list(APPEND SRCS PIDControllerSessie.cpp aanUitControllerSessie.cpp)
	elseif((${practicumopdracht} STREQUAL "FuzzyOpdracht"))
		message(STATUS "Regeltechniek [Fuzzy] wordt gebouwd.")
		message(STATUS "Control Engineering [Fuzzy] assignment is being built.")
		set(opdracht regeltechniek)
		list(APPEND SRCS fuzzyControllerSessie.cpp aanUitControllerSessie.cpp)
	endif()

endif(${practicumopdracht} STREQUAL "DebugOpdracht")

list(SORT SRCS)

add_library(${LibName} STATIC ${SRCS})
## This library can now be included in any build by using "add_subdirectory( the_path_to_this_lib )".