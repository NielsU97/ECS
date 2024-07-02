## Copyright 2011-2016 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 2626 2017-03-23 16:36:14Z ewout $

message(STATUS "STM32F4xx Utilities Driver wordt toegevoegd.")

FILE (GLOB_RECURSE SRCS *.c)
include_directories()

list(SORT SRCS)

add_library(UtilitiesLib ${SRCS})





