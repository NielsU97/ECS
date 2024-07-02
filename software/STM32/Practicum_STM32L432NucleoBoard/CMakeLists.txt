## Copyright 2011-2017 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 3999 2020-10-16 14:48:51Z ewout $

set(PROJEKTNAAM "RGTpracticum")

set(BoardVersie BoardVersie11)

cmake_minimum_required(VERSION 3.10.4)

# Voer toolchain ontdekking uit VOOR het projekt wordt gezet.
include(${CMAKE_CURRENT_LIST_DIR}/../STM32Basis/ZetARMCortexMToolchain.cmake)

project(${PROJEKTNAAM})

set(RGTSoftwareBasisDir ${PROJECT_SOURCE_DIR}/../..)

include(${RGTSoftwareBasisDir}/RGT.cmake)
include(${STM32BasisDir}/STM32Development.cmake)

include_directories(h config)
include_directories(${RGTSoftwareBasisDir}/algemeen/h)

include(${STM32BasisDir}/STM32Development.cmake)
include(${CMAKESCRIPTDIR}/STM32L432KC.cmake)
include(${FreeRTOSDir}/FreeRTOS.cmake)

if(STM32L432Nucleo32BaudRate)
	message(STATUS "Microcontroller baud rate is nu ${STM32L432Nucleo32BaudRate} bps.")
	add_definitions(-DSTM32L432Nucleo32BaudRate=${STM32L432Nucleo32BaudRate})
else(STM32L432Nucleo32BaudRate)
	message(STATUS "Microcontroller baud rate is nu standaard 115200 bps.")
endif(STM32L432Nucleo32BaudRate)

include(${CMAKESCRIPTDIR}/DevBoard/STM32L432Nucleo32.cmake)
include(${STM32BasisDir}/STM32PostSetupDevelopment.cmake)

set(BasisSRCS ${STM32StdPeriphHALGemeenschappelijkDir}/basis/syscalls.cpp)

MaakSeggerSimpelOzoneConfigCortexM4F(${PROJEKTNAAM}.elf STM32L432KC "${SVDDir}/STM32L4x2.svd")

include_directories(rtosBasisRGT/h)
add_subdirectory(rtosBasisRGT)

# Gemeenschappelijke bestanden tussen Desktop en STM32
add_subdirectory(../../rgtData ${CMAKE_CURRENT_BINARY_DIR}/RGTData)
include_directories(../../rgtData/h)

add_subdirectory(toepassing)

