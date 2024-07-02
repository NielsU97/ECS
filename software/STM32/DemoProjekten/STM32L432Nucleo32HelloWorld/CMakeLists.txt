## Copyright 2011-2019 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 3236 2018-12-01 13:17:01Z ewout $

message("HAN ESE STM32L432Nucleo32 Discovery Hello World (Bare Metal versie).")
message("(c)2016-2019 ir drs E.J Boks")
message("Opleiding Embedded Systems Engineering")
message("Hogeschool van Arnhem en Nijmegen")

set(PROJEKTNAAM "STM32L432HelloWorld")

cmake_minimum_required(VERSION 2.8.4)

# Voer toolchain ontdekking uit VOOR het projekt wordt gezet.
include(${CMAKE_CURRENT_LIST_DIR}/../../STM32Basis/ZetARMCortexMToolchain.cmake)

project(${PROJEKTNAAM})

option(OverrideGCC_G++ "Gebruik C++ voor C" ON)
option(GebruikHALDrivers "Gebruik STM32 HAL bibliotheek" ON)
option(GebruikFreeRTOS "Gebruik FreeRTOS" OFF)
option(GebruikOOFreeRTOS "Gebruik FreeRTOS Object Oriented" OFF)

set(SoftwareBasisDir ${PROJECT_SOURCE_DIR}/../../..)
set(STM32BasisDir ${SoftwareBasisDir}/STM32/STM32Basis)

include_directories(h config)

include(${STM32BasisDir}/STM32Development.cmake)
include(${CMAKESCRIPTDIR}/STM32L432KC.cmake)
include(${CMAKESCRIPTDIR}/DevBoard/STM32L432Nucleo32.cmake)

include(${STM32BasisDir}/STM32PostSetupDevelopment.cmake)

include_directories(h)
set(SRCS main.cpp)

list(APPEND SRCS ${BasisSRCS})
list(SORT SRCS)

add_executable(${PROJEKTNAAM}.elf ${SRCS})

target_link_libraries(${PROJEKTNAAM}.elf ${L432NucleoBibliotheken} )

PostBuildAktie(${PROJEKTNAAM}.elf "STM32 ${PROJEKTNAAM}.elf is gemaakt.")

MaakSeggerSimpelOzoneConfigCortexM4F(${PROJEKTNAAM}.elf STM32L432KC "${SVDDir}/STM32L4x2.svd")

