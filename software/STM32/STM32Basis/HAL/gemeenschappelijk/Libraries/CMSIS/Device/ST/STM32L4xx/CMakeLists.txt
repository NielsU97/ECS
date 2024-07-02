## Copyright 2011-2018 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 3116 2018-10-26 15:16:52Z ewout $

if(NOT StartupCode)
	message(FATAL_ERROR "StartupCode moet wijzen naar het goede startup.s bestand.")
else()
	file(GLOB CoreSupport Source/Templates/*.c)
	message(STATUS "ARM CMSIS support voor STM32L4xx wordt toegevoegd.")
	set(SRCS ${CoreSupport} ${StartupCode})
list(SORT SRCS)

MaakLib(CMSISFIRMWARE "${SRCS}")
endif(NOT StartupCode)
