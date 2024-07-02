## Boombaard generated CMakelists add_library file
## File generated on : 2018-02-28 11:12:56.

# define minimum cmake version.
cmake_minimum_required(VERSION 3.10.4)

# The absolute path for this CMakeLists.txt file is : "C:\Users\ewout\home\vakken\ti_cp\regeltechniek\practicum\rgtpracticum\software\STM32\RGT+DSB_Board\practicum\rtosBasisRGT"
set(LibName RTOSBasisRGT)

set(SrcPath0 ${CMAKE_CURRENT_SOURCE_DIR}/h)
set(SrcPath1 ${CMAKE_CURRENT_SOURCE_DIR}/.)

set(AllIncludeDirs ${SrcPath0} )
include_directories(${AllIncludeDirs})

set(SRCS  rtosTaak.cpp)

list(SORT SRCS)

add_library(${LibName} STATIC ${SRCS})
## This library can now be included in any build by using "add_subdirectory( the_path_to_this_lib )".