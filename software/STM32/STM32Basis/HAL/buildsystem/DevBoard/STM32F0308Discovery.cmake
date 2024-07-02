#************************************************************************
# CMake script om STM32F0308 Discovery software te compileren.
# Copyright 2004-2018 Hogeschool van Arnhem en Nijmegen
# Opleiding Embedded Systems Engineering
# $Id: STM32F0308Discovery.cmake 3235 2018-12-01 11:06:13Z ewout $
#************************************************************************

add_definitions(-DUSE_DiscoverySTM32F0308)

set(STM32F0308BSPDir ${BSPDir}/STM32F0308-Discovery)

include_directories(${STM32F0308BSPDir} ${STM32F0308BSPDir}/h ${UtilitiesDir} ${ComponentsDir})

#add_subdirectory(${ComponentsDir} ${CMAKE_CURRENT_BINARY_DIR}/Components)
add_subdirectory(${STM32F0308BSPDir} ${CMAKE_CURRENT_BINARY_DIR}/STM32F0308DiscoveryBSPLib)

add_library(DiscoverySTM32F0308 $<TARGET_OBJECTS:STM32F0308-Discovery> )

set(STM32F0308DiscoveryStdBibliotheken ESEBasisLib SEGGER_Sysview Segger_RTT DiscoverySTM32F0308
    STM32F0xx_HAL_Driver AlgemeenLib CMSISFIRMWARE)

set(STM32F0308DiscoveryBibliotheken ${STM32F0308DiscoveryStdBibliotheken})

