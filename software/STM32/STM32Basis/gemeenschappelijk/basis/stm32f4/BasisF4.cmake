## Copyright 2011-2016 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## Ewout Boks
## $Id: BasisF4.cmake 2774 2017-05-11 16:02:04Z ewout $

# ST package voor STM32F4 Discovery board
set(BasisSRCS ../syscalls.cpp term_io.c)

include_directories(${STM32StdPeriphHALGemeenschappelijkDir}/basis)

