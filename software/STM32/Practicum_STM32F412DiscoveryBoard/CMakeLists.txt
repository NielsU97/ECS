## Copyright 2011-2019 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 4294 2021-06-22 12:51:19Z ewout $

set(PROJEKTNAAM "RGTpracticum")

set(BoardVersie BoardVersie11)

cmake_minimum_required(VERSION 3.10.4)

# Voer toolchain ontdekking uit VOOR het projekt wordt gezet.
include(${CMAKE_CURRENT_LIST_DIR}/../STM32Basis/ZetARMCortexMToolchain.cmake)

project(${PROJEKTNAAM})

set(RGTSoftwareBasisDir ${PROJECT_SOURCE_DIR}/../..)
include(${RGTSoftwareBasisDir}/RGT.cmake)

include(${STM32BasisDir}/STM32Development.cmake)

option(STM32F412GDiscoveryMetGUI "Gebruik Segger GUI Driver" ON)
option(GebruikFreeRTOS "Gebruik FreeRTOS Driver" ON)
option(GebruikOOFreeRTOS "GebruikFreeRTOS OO Driver" ON)

include_directories(config)
include_directories(${RGTSoftwareBasisDir}/algemeen/h)

include(${CMAKESCRIPTDIR}/STM32F412xG.cmake)
include(${FreeRTOSDir}/FreeRTOS.cmake)
include(${CMAKESCRIPTDIR}/DevBoard/STM32F412GDiscovery.cmake)
include(${STM32BasisDir}/STM32PostSetupDevelopment.cmake)

set(BSPDir ${ThirdParty}/ESE_BSP)
option(ESE_RGT+DSBProcessor "Gebruik de ESE RGT+DSB processor" ON)
include(${BSPDir}/ESE_BSP.cmake)

set(BasisSRCS ${STM32StdPeriphHALGemeenschappelijkDir}/basis/syscalls.cpp)

MaakSeggerSimpelOzoneConfigCortexM4F(${PROJEKTNAAM}.elf STM32F412ZG "${SVDDir}/STM32F412xG.svd")

# De spullen voor implementatie van FreeRTOS in onze toepassing
include_directories(rtosBasisRGT/h)
add_subdirectory(rtosBasisRGT)

# Gemeenschappelijke bestanden tussen Desktop en STM32
add_subdirectory(../../rgtData ${CMAKE_CURRENT_BINARY_DIR}/RGTData)
include_directories(../../rgtData/h)

add_subdirectory(toepassing)

