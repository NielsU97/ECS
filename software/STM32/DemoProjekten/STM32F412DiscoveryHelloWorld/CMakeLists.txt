## Copyright 2011-2019 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## ir drs E.J Boks
## $Id: CMakeLists.txt 3662 2019-10-24 15:32:27Z ewout $
 
message("HAN ESE STM32F412G Discovery Hello World.")
message("(c)2016-2020 ir drs E.J Boks")
message("Opleiding Embedded Systems Engineering")
message("Hogeschool van Arnhem en Nijmegen")

# Voer toolchain ontdekking uit VOOR het projekt wordt gezet.
include(${CMAKE_CURRENT_LIST_DIR}/../../STM32Basis/ZetARMCortexMToolchain.cmake)

set(PROJEKTNAAM "stm32f412HelloWorld")

cmake_minimum_required(VERSION 2.8.4)

project(${PROJEKTNAAM})

set(BoardVersie BoardVersie11)

include_directories(h)

option(OverrideGCC_G++ "Gebruik C++ voor C" ON)
option(GebruikHALDrivers "Gebruik STM32 HAL bibliotheek" ON)
option(GebruikFreeRTOS "Gebruik FreeRTOS" OFF)
option(GebruikOOFreeRTOS "Gebruik FreeRTOS Object Oriented" OFF)

set(SoftwareBasisDir ${PROJECT_SOURCE_DIR}/../../..)
set(STM32BasisDir ${SoftwareBasisDir}/STM32/STM32Basis)
include(${STM32BasisDir}/STM32Development.cmake)

# Voeg hier de processor specs eerst in. Deze staan los van discovery.cmake ivm invoegen freertos termen.
include(${CMAKESCRIPTDIR}/STM32F412xG.cmake)
include(${CMAKESCRIPTDIR}/DevBoard/STM32F412GDiscovery.cmake)

include(${STM32BasisDir}/STM32PostSetupDevelopment.cmake)

set(BSPDir ${ThirdParty}/ESE_BSP)
option(ESE_RGT+DSBProcessor "Gebruik de ESE RGT+DSB Processor driver" ON)
option(ESE_DigProcesProcessor "Gebruik de ESE Digitaal Proces Processor driver" OFF)
include(${BSPDir}/ESE_BSP.cmake)

set(SRCS main.cpp controller.cpp)

list(SORT SRCS)

# Doel wordt hier samengesteld.
add_executable(${PROJEKTNAAM}.elf ${SRCS} ${BasisSRCS})

target_link_libraries(${PROJEKTNAAM}.elf ${ESE_BSPLib} ${F412GDiscoveryBibliotheken} )

PostBuildAktie(${PROJEKTNAAM}.elf "STM32 ${PROJEKTNAAM}.elf is gemaakt.")

MaakSeggerSimpelOzoneConfigCortexM4F(${PROJEKTNAAM}.elf STM32F412ZG "${SVDDir}/STM32F412xG.svd")
