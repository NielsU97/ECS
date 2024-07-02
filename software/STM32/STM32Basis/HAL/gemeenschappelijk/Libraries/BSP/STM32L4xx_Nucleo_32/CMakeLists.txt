## Boombaard generated CMakelists add_library file
## File generated on : 2018-10-26 15:51:00.

# define minimum cmake version.
cmake_minimum_required(VERSION 3.10.4)

# The absolute path for this CMakeLists.txt file is : "C:\Users\ewout\home\vakken\algemeen\software\STM32\STM32Basis\HAL\gemeenschappelijk\Libraries\BSP\STM32L4xx_Nucleo_32"
set(LibName STM32L4xxNucleo32Basis)

set(SrcPath0 ${CMAKE_CURRENT_SOURCE_DIR}/h)
set(SrcPath1 ${CMAKE_CURRENT_SOURCE_DIR}/.)

set(AllIncludeDirs ${SrcPath0} . )
include_directories(${AllIncludeDirs})

set(SRCS stm32l4xx_nucleo_32.c STM32L4xxNucleo32.cpp )

list(SORT SRCS)

add_library(${LibName} OBJECT ${SRCS})
## This library can now be included in any build by using "add_subdirectory( the_path_to_this_lib )".