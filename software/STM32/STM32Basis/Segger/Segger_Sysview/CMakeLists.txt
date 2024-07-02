## Boombaard generated CMakelists add_library file
## File generated on : 2018-11-18 21:00:20.
## (c)2001-2018 Hogeschool van Arnhem en Nijmegen
## ir drs E.J Boks, opleiding Elektrotechniek/ESE
## $Id: boombaardvenster.cpp 8532 2017-12-04 19:07:15Z oldenburgh $

# Het absolute pad voor dit CMakeLists.txt bestand is : “/Users/ese/vakken/ti_cp/regeltechniek/practicum/rgtpracticum/software/STM32/STM32Basis/Segger/Segger_Sysview”
set(LibName SEGGER_Sysview)

set(SRCS )
set(SrcPath0 ${CMAKE_CURRENT_SOURCE_DIR}/../config)
set(SrcPath1 ${CMAKE_CURRENT_SOURCE_DIR}/.)
set(SrcPath2 ${CMAKE_CURRENT_SOURCE_DIR}/../Segger_RTT/RTT)
set(AllIncludeDirs ${SrcPath0} ${SrcPath2} . )
include_directories(${AllIncludeDirs})


list(APPEND SRCS SEGGER_SYSVIEW.c )
foreach(SRC ${SRCS0})
	list(APPEND SRCS ${SRCS0Path}/${SRC})
endforeach(SRC)


list(SORT SRCS)

add_library(${LibName} STATIC ${SRCS})
## This library can now be included in any build by using “add_subdirectory( the_path_to_this_lib )”.