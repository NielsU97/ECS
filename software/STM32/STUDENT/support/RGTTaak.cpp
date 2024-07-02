/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
Taken voor PRJ3PRT

@version $Rev: 4227 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2019 Hogeschool van Arnhem en Nijmegen
         
$Id: RGTTaak.cpp 4227 2021-04-20 17:28:46Z ewout $
************************************************************************/

#include <RGTTaak.h>
#include <cmsis_os.h>

#ifdef USE_STM32412G_DISCOVERY
#include <GUI.h>
#endif

#if (defined(InputResponsieOpdracht) )
OpenLoopTask::OpenLoopTask() : RTOSTask("OpenLoopTaak",
                                        1024,
                                        TaakPrio::Taak2,
                                        rgtProces),rgtProces(*this)
{
	Start(); /* deze aanroep moet hier gedaan worden, anders wordt er geen taak aangemaakt. */
}

void OpenLoopTask::Run()
{
#ifdef USE_STM32412G_DISCOVERY
	auto &controller = rgtProces;
	auto gebruikLCD = controller.geefBKUPGebruikLCDKeuze();

	controller.setLED(ESEBoardController::LEDKleur::Blue,
	                  (Schakelaar::Aan == gebruikLCD) ? Schakelaar::Uit : Schakelaar::Aan);
	controller.setLED(ESEBoardController::LEDKleur::Orange,
	                  gebruikLCD);

	/* initialiseer de GUI */
	controller.guiDriver.postOSStartGUIInit();
	
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Opdracht 3 - Open Lus",120,30);
	
	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Druk \"Links\" om te beginnen",120,150);
#else
	GUI_DispStringHCenterAt("Assignment 3 - Open Loop",120,30);
	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Press \"Left\" to start",120,150);
#endif
	
	/* schakel de LEDs aan */
	controller.setLED(STM32BoardController::LEDKleur::Green,
	                  Schakelaar::Aan);
	
	bool wachtOpInstruktie = true;
	
	do
	{
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = controller.wachtOpEenKnop(true);
		
		switch (knop)
		{
			case STM32412gDiscovery::KnopID::Boven:
			{
				gebruikLCD = Schakelaar::Uit;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Aan);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Uit);
#ifdef InterfaceTaalNederlands
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;
			
			case STM32412gDiscovery::KnopID::Onder:
			{
				gebruikLCD = Schakelaar::Aan;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Uit);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Aan);

#ifdef InterfaceTaalNederlands
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;
			
			case STM32412gDiscovery::KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;
			
			default:
				break;
		}
		
		HAL_Delay(250);
		
	} while (true == wachtOpInstruktie);

	controller.zetBKUPGebruikLCDKeuze(gebruikLCD);

#elif defined USE_STM32L432Nucleo32
	const auto gebruikLCD = Schakelaar::Uit;
#endif

	rgtProces.setSampleTime();
	rgtProces.mainLoop(gebruikLCD, true);
}

#endif


#if (defined(PIDControllerOpdracht))
PIDTaak::PIDTaak() : RTOSTask("PIDTaak",
                              512,
                              TaakPrio::Taak2,
                              rgtProces),
                     rgtProces(*this,&pid,&aanUit)
{
	Start();
}

void PIDTaak::Run()
{
#ifdef USE_STM32412G_DISCOVERY
	const auto gebruikLCD = startF412();
#elif defined USE_STM32L432Nucleo32
	const auto gebruikLCD = startL432();
#endif

	rgtProces.setSampleTime(); /* 5 millisecs */
	rgtProces.mainLoop(gebruikLCD, true);
}

Schakelaar PIDTaak::startL432()
{
#if defined USE_STM32L432Nucleo32
	static constexpr auto gebruikLCD = Schakelaar::Uit;
	return(gebruikLCD);
#else
	static constexpr auto gebruikLCD = Schakelaar::Uit;
	return(gebruikLCD);
#endif
}

Schakelaar PIDTaak::startF412()
{
#ifdef USE_STM32412G_DISCOVERY
	auto &controller = rgtProces;
	auto gebruikLCD = controller.geefBKUPGebruikLCDKeuze();

	controller.setLED(ESEBoardController::LEDKleur::Blue,
	                  (Schakelaar::Aan == gebruikLCD) ? Schakelaar::Uit : Schakelaar::Aan);
	controller.setLED(ESEBoardController::LEDKleur::Orange,
	                  gebruikLCD);

	/* initialiseer de GUI */
	controller.guiDriver.postOSStartGUIInit();

	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Opdracht 4-7:PID controller",120,30);

	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Druk \"Links\" om te beginnen",120,150);
#else
	GUI_DispStringHCenterAt("Assignment 2 4-7:PID controller",120,30);
	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Press \"Left\" to start",120,150);
#endif

	/* schakel de LEDs aan */
	controller.setLED(STM32BoardController::LEDKleur::Green,
	                  Schakelaar::Aan);

	bool wachtOpInstruktie = true;

	do
	{
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = controller.wachtOpEenKnop(true);

		switch (knop)
		{
			case STM32412gDiscovery::KnopID::Boven:
			{
				gebruikLCD = Schakelaar::Uit;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Aan);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Uit);
#ifdef InterfaceTaalNederlands
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;

			case STM32412gDiscovery::KnopID::Onder:
			{
				gebruikLCD = Schakelaar::Aan;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Uit);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Aan);

#ifdef InterfaceTaalNederlands
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;

			case STM32412gDiscovery::KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;

			default:
				break;
		}

		HAL_Delay(250);

	} while (true == wachtOpInstruktie);

	controller.zetBKUPGebruikLCDKeuze(gebruikLCD);
	return(gebruikLCD);
#else
	static constexpr auto gebruikLCD = Schakelaar::Uit;
	return(gebruikLCD);
#endif
}


#elif (defined(FuzzyOpdracht))
FuzzyTaak::FuzzyTaak() : RTOSTask("FuzzyTaak",
                              512,
                              TaakPrio::Taak2,
                              rgtProces),
                     rgtProces(*this,&fuzzy,&aanUit)
{
	Start();
}

void FuzzyTaak::Run()
{
#ifdef USE_STM32412G_DISCOVERY
	auto &controller = rgtProces;
	auto gebruikLCD = controller.geefBKUPGebruikLCDKeuze();

	controller.setLED(ESEBoardController::LEDKleur::Blue,
	                  (Schakelaar::Aan == gebruikLCD) ? Schakelaar::Uit : Schakelaar::Aan);
	controller.setLED(ESEBoardController::LEDKleur::Orange,
	                  gebruikLCD);

	/* initialiseer de GUI */
	controller.guiDriver.postOSStartGUIInit();

	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Opdracht 4-7:Fuzzy controller",120,30);

	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Druk \"Links\" om te beginnen",120,150);
#else
	GUI_DispStringHCenterAt("Assignment 2 4-7:Fuzzy controller",120,30);
	GUI_SetFont(&GUI_FontComic18B_1);
	GUI_SetTextMode( ((Schakelaar::Aan == gebruikLCD )? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
	GUI_SetTextMode( ((Schakelaar::Uit == gebruikLCD) ? GUI_TM_NORMAL : GUI_TM_REV));
	GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_DispStringHCenterAt("Press \"Left\" to start",120,150);
#endif

	/* schakel de LEDs aan */
	controller.setLED(STM32BoardController::LEDKleur::Green,
	                  Schakelaar::Aan);

	bool wachtOpInstruktie = true;

	do
	{
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = controller.wachtOpEenKnop(true);

		switch (knop)
		{
			case STM32412gDiscovery::KnopID::Boven:
			{
				gebruikLCD = Schakelaar::Uit;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Aan);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Uit);
#ifdef InterfaceTaalNederlands
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;

			case STM32412gDiscovery::KnopID::Onder:
			{
				gebruikLCD = Schakelaar::Aan;
				controller.setLED(STM32BoardController::LEDKleur::Blue,
				                  Schakelaar::Uit);
				controller.setLED(STM32BoardController::LEDKleur::Orange,
				                  Schakelaar::Aan);

#ifdef InterfaceTaalNederlands
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Druk \"Boven\" voor Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Druk \"Onder\" voor LCD",120,110);
#else
				GUI_SetTextMode(GUI_TM_NORMAL);
				GUI_DispStringHCenterAt("Press \"Up\" for Desktop",120,80);
				GUI_SetTextMode( GUI_TM_REV);
				GUI_DispStringHCenterAt("Press \"Down\" for LCD",120,110);
#endif
			};
				break;

			case STM32412gDiscovery::KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;

			default:
				break;
		}

		HAL_Delay(250);

	} while (true == wachtOpInstruktie);

	controller.zetBKUPGebruikLCDKeuze(gebruikLCD);

#elif defined USE_STM32L432Nucleo32
	const auto gebruikLCD = Schakelaar::Uit;
#endif

	rgtProces.setSampleTime(); /* 5 millisecs */
	rgtProces.mainLoop(gebruikLCD, true);
}
#endif

LedBlinkTask::LedBlinkTask() : StdTaak("LED Blink task",
                                       256,
                                       TaakPrio::Taak1)
{
	Start();
}

[[noreturn]] void LedBlinkTask::Run()
{
	UInt32 knipperTijd = 0;

	BSP_LED_On(LED_GREEN);  /* begin met led aan */

	FOREVER
	{
		const auto nieuw = wachtOpBericht(knipperTijd);

		if (FoutCode::Ok == nieuw)
		{
			const auto type = geefType();

			switch(type)
			{
				case MsgType::VerbindingGemaakt:
					knipperTijd=1000;
					BSP_LED_Toggle(LED_GREEN);
					break;
				case MsgType::VerbindingLosgemaakt:
					BSP_LED_On(LED_GREEN);
					knipperTijd=0;
					break;
				case MsgType::StartStopGedrukt:
				{
					knipperTijd = ((1000 == knipperTijd) ? 250 : 1000);
					BSP_LED_Toggle(LED_GREEN);
				}
					break;
				default:
					break;
			}
		}
		else
		{
			BSP_LED_Toggle(LED_GREEN);
		}


	}
}
