/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
RTOS taak voor debug practicum en regeltechniek practicum

@version $Rev: 3187 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2016 Hogeschool van Arnhem en Nijmegen
         
$Id: rtosTaak.cpp 3187 2018-11-18 15:24:08Z ewout $
************************************************************************/

#include <rtosTaak.h>


RTOSTask::RTOSTask(const std::string &naam,
                   const UInt16 stackGrootte,
                   const TaakPrio prioriteit,
                   ESEBoardController &ese) : StdTaak(naam,stackGrootte,
                                                      prioriteit),eseBoardController(ese)
{

}


