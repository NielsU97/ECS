## Boombaard generated CMakelists add_library file
## File generated on : 2018-06-08 15:01:41.
## (c)2001-2018 Hogeschool van Arnhem en Nijmegen
## ir drs E.J Boks, opleiding Elektrotechniek/ESE
## $Id: boombaardvenster.cpp 8532 2017-12-04 19:07:15Z oldenburgh $


# define minimum cmake version.
cmake_minimum_required(VERSION 3.10.4)

# The absolute path for this FindFTDI2XXX.cmake file is : “/Users/ese/vakken/ti_cp/regeltechniek/practicum/rgtpracticum/software/rgtData”
set(LibName RGTData)

set(SrcPath0 ${CMAKE_CURRENT_SOURCE_DIR}/h)
set(SrcPath1 ${CMAKE_CURRENT_SOURCE_DIR}/.)

set(AllIncludeDirs ${SrcPath0} )
include_directories(${AllIncludeDirs})

set(SRCS RGTData.cpp )

list(SORT SRCS)

add_library(${LibName} STATIC ${SRCS})
## This library can now be included in any build by using “add_subdirectory( the_path_to_this_lib )”.