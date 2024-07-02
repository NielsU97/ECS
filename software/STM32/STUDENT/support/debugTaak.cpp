/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
RGT Controller voor PRJ3PRT

@version $Rev: 4004 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2016 Hogeschool van Arnhem en Nijmegen
         
$Id: debugTaak.cpp 4004 2020-10-16 14:51:13Z ewout $
************************************************************************/

#include <debugTaak.h>
#ifdef USE_STM32412G_DISCOVERY
#include <GUI.h>
#include <lcd_log_conf.h>
#endif

#ifdef DebugOpdracht
DebugTask::DebugTask(DebugController &dbg) : RTOSTask("Debug Task", 256, TaakPrio::Taak1,dbg),
                                             controller(dbg)
{
	Start();
}

void DebugTask::Run()
{

#ifdef USE_STM32412G_DISCOVERY

	/* initialiseer de GUI */
	controller.guiDriver.postOSStartGUIInit();

	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Opdracht 1 - Debug",120,30);
	GUI_DispStringHCenterAt("Druk \"Up\" om te beginnen",120,80);
#else
	GUI_DispStringHCenterAt("Assignment 1 - Debug",120,30);
	GUI_DispStringHCenterAt("Press \"Up\" to start",120,80);
#endif
	/* schakel de LEDs aan */
	controller.setLED(STM32BoardController::LEDKleur::AllColours,
	                  Schakelaar::Aan);

	/* Wacht tot de "boven"knop is ingedrukt. */
	controller.wachtOpKnop(STM32BoardController::KnopID::Boven,false);

	/* schakel de leds uit */
	controller.setLED(STM32BoardController::LEDKleur::AllColours,
	                  Schakelaar::Uit);
#endif


	/* doe het testprogramma. */
	controller.debugSession();
}
#endif

