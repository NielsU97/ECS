## Copyright 2011-2017 Hogeschool van Arnhem en Nijmegen
## $Id: CMakeLists.txt 4029 2020-11-27 16:12:13Z ewout $

include_directories(${StudentDir}/support/h)
include_directories(${StudentDir}/h h)

add_compile_definitions(${practicumopdracht})

add_subdirectory(${StudentDir} ${CMAKE_CURRENT_BINARY_DIR}/opdracht)

# vergeet niet om de emwin spullen hier mee te bouwen.
set(SRCS main.cpp ${EmWinSTM32F412GDiscoveryDriverSRCS})

list(APPEND SRCS ${BasisSRCS})
list(SORT SRCS)

add_executable(${PROJEKTNAAM}.elf ${SRCS})

target_link_libraries(${PROJEKTNAAM}.elf  studentspullen RTOSBasisRGT RGTData ${ESE_BSPLib} ${F412GDiscoveryBibliotheken} ${FreeRTOSLibs} )

PostBuildAktie(${PROJEKTNAAM}.elf "STM32 ${PROJEKTNAAM}.elf [${practicumopdracht}] is gemaakt.")
