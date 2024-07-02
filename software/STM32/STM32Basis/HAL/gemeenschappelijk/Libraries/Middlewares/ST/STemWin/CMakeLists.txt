## Copyright 2011-2016 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: CMakeLists.txt 2626 2017-03-23 16:36:14Z ewout $

message(STATUS "ST (Segger) EmWin Bibliotheek (STemWin) toegevoegd.")

if(NOT GebruikFreeRTOS)
	add_definitions(-DOS_SUPPORT=0)
	set(SRCS OS/GUI_X.c)
else(NOT GebruikFreeRTOS)
	add_definitions(-DOS_SUPPORT=1)
	set(SRCS OS/GUI_X_OS.c)
endif(NOT GebruikFreeRTOS)

list(SORT SRCS)

include_directories(inc)

MaakLib(STemWinOSLib "${SRCS}")

