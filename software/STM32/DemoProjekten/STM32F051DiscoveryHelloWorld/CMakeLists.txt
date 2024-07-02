## Copyright 2011-2018 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 3235 2018-12-01 11:06:13Z ewout $

message("HAN ESE STM32F051 Discovery LEDs demo.")
message("(c)2011-2018 ir drs E.J Boks")
message("Opleiding Embedded Systems Engineering")
message("Hogeschool van Arnhem en Nijmegen")

set(PROJEKTNAAM "STM32F051DiscoveryDemo")

cmake_minimum_required(VERSION 2.8.4)

# Voer toolchain ontdekking uit VOOR het projekt wordt gezet.
include(${CMAKE_CURRENT_LIST_DIR}/../../STM32Basis/ZetARMCortexMToolchain.cmake)

project(${PROJEKTNAAM})

option(OverrideGCC_G++ "Gebruik C++ voor C" ON)

include_directories(config)

option(GebruikHALDrivers "Gebruik STM32 HAL bibliotheek" ON)

set(SoftwareBasisDir ${PROJECT_SOURCE_DIR}/../../..)
set(STM32BasisDir ${SoftwareBasisDir}/STM32/STM32Basis)
include(${STM32BasisDir}/STM32Development.cmake)

# Discovery heeft 8 MHz
add_definitions(-DHSE_VALUE=8000000)
include_directories(h ${F0DISCOVERYDIR})

# Zet kommentaar om de niet gebruikte processor ... hangt van het bord af.
# Oudere STM32 borden gebruiken de STM32F051R8
include(${CMAKESCRIPTDIR}/STM32F051.cmake)
# Modernere STM32 Borden gebruiken de STM32F030R8
#include(${CMAKESCRIPTDIR}/STM32F051.cmake)

include(${CMAKESCRIPTDIR}/DevBoard/STM32F0308Discovery.cmake)
include(${STM32BasisDir}/STM32PostSetupDevelopment.cmake)

include_directories(h)
set(SRCS main.cpp)

list(APPEND SRCS ${BasisSRCS})
list(SORT SRCS)

add_executable(${PROJEKTNAAM}.elf ${SRCS})

# Maak een Segger Ozone jdebug bestand
# Zet kommentaar om de niet gebruikte processor ... hangt van het bord af.
MaakSeggerSimpelOzoneConfigCortexM0(${PROJEKTNAAM}.elf STM32F051R8 "${SVDDir}/STM32F0x1.svd")
#MaakSeggerSimpelOzoneConfigCortexM0(${PROJEKTNAAM}.elf STM32F030R8 "${SVDDir}/STM32F0x1.svd")

# Doel wordt hier samengesteld.
target_link_libraries(${PROJEKTNAAM}.elf ${STM32F0308DiscoveryBibliotheken})

PostBuildAktie(${PROJEKTNAAM}.elf "STM32 ${PROJEKTNAAM}.elf is gemaakt.")
