/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
RTOS taak voor debug practicum en regeltechniek practicum

@version $Rev: 3172 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2016 Hogeschool van Arnhem en Nijmegen
         
$Id: rtosTaak.cpp 3172 2018-11-16 09:27:14Z ewout $
************************************************************************/

#include <rtosTaak.h>

RTOSTask::RTOSTask(const std::string &naam,
                   const UInt16 stackGrootte,
                   const TaakPrio prioriteit,
                   STM32L432Nucleo32 &nuuk) : StdTaak(naam,stackGrootte,
                                                        prioriteit),nucleo(nuuk)
{

}


