## Copyright 2011-2017 Hogeschool van Arnhem en Nijmegen
## $Id: CMakeLists.txt 4006 2020-10-16 15:28:45Z ewout $

	include_directories(${StudentDir}/support/h)
	include_directories(${StudentDir}/h h)

	add_compile_definitions(${practicumopdracht})

	add_subdirectory(${StudentDir} ${CMAKE_CURRENT_BINARY_DIR}/opdracht)

	set(SRCS main.cpp)

	list(APPEND SRCS ${BasisSRCS})
	list(SORT SRCS)

	add_executable(${PROJEKTNAAM}.elf ${SRCS})

	target_link_libraries(${PROJEKTNAAM}.elf studentspullen RTOSBasisRGT RGTData ${ESE_BSPLib} ${L432NucleoBibliotheken} ${FreeRTOSLibs} )

	PostBuildAktie(${PROJEKTNAAM}.elf "STM32 ${PROJEKTNAAM}.elf [${practicumopdracht}] is gemaakt.")
