/******************************************************************************
@file
Signaal maken voor PRJ3PRT

@version $Rev: 4227 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2018 Hogeschool van Arnhem en Nijmegen
         
$Id: InputResponsieSessie.cpp 4227 2021-04-20 17:28:46Z ewout $
************************************************************************/

//#error  "(RGTProces.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(RGTProces.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :    Niels Urgert           ******/
/********  Studentnummer :    654746                 ******/

#include <math.h>
#include <string.h>
#include <assert.h>
#include <InputResponsieSessie.h>

#include <PIDControllerSessie.h>
#include <aanUitControllerSessie.h>
#include <fuzzyControllerSessie.h>

#include <stdTaak.h>

#include <RTT/SEGGER_RTT.h>

Spanning RGTProces::impulseInputSignal(const RGTData::SampleMoment n) const
{
	const auto delay = getStartDelay();
    const auto sp = getSetPoint();

    const auto uit = (n == delay) ? sp : 0.0f;

    return uit;
}

Spanning RGTProces::stepInputSignal(const RGTData::SampleMoment n) const
{
	const auto delay = getStartDelay();
    const auto sp = getSetPoint();

    const auto uit = (n >= delay) ? sp : 0.0f;

    return uit;
}

Spanning RGTProces::rampInputSignal(const RGTData::SampleMoment n) const
{
	const auto delay = getStartDelay();
    //const auto sp = getSetPoint();
    const auto uit = (n - delay)/200.0f;

    return uit;
}

Spanning RGTProces::squareWaveInputSignal(const RGTData::SampleMoment n)
{
	const auto coswaarde = cosineInputSignal(n);
    const auto sp = getSetPoint();
    const auto uit = (coswaarde > sp) ? sp : -1.0f*sp;

    return uit;
}

Spanning RGTProces::cosineInputSignal(const RGTData::SampleMoment n)
{
	if (--cosStapper == 0)
	{
		cosStapper=cosStapGrootte;
		cosArg = (cosArgBasis * n);
	}

	const float retWaarde = getSetPoint()+amplitude*cosf(cosArg);

	/* end of example code */
	return(retWaarde);
}

void RGTProces::reset()
{

}


void RGTProces::setSampleTime()
{
	/* Fill out the software to set the proper sampling time.
	 * Please note that for buffering purposes the sample time should be set
	 * equal to 2 Hz or more.
	 * Anything slower will make the GUI programm show a time-out message.
	 * Tip : gebruik de basisklasse om een funktie te vinden om de bemonsteringfrequenctie te zetten......
	 * Advice : use the base class to find a method for setting the sample frequency.... */

#ifdef USE_STM32412G_DISCOVERY
	/* De ADC ads131a02 has a proper function for this. */
	/* wens is 20 Hz ==> 16,384 MHz ..14..  1,17 ..14.. 83 kHz ..4096.. 20,4 Hz */
	//ads131a02.zetSampFreq(ADS131A02::ICLK::ICLK14, ADS131A02::FMOD::FMOD14, ADS131A02::ODR::ODR4096);
	
	/* wens is 200 Hz ==> 16,384 MHz ..14..  1,17 ..2.. 585 kHz ..2048.. 285 Hz */
	ads131a02.zetSampFreq(ADS131A02::ICLK::ICLK14, ADS131A02::FMOD::FMOD2, ADS131A02::ODR::ODR2048);
	
	/* wens is 1000 Hz ==> 16,384 MHz ..6..  2,73 ..6.. 445 kHz ..512.. 888 Hz */
	//ads131a02.zetSampFreq(ADS131A02::ICLK::ICLK6, ADS131A02::FMOD::FMOD6, ADS131A02::ODR::ODR512);
	
	/* wens is 2000 Hz ==> 16,384 MHz ..6..  2,73 ..6.. 445 kHz ..200.. 2,2 kHz */
	//ads131a02.zetSampFreq(ADS131A02::ICLK::ICLK6, ADS131A02::FMOD::FMOD6, ADS131A02::ODR::ODR200);
	/* wens is 10 kHz ==> 16,384 MHz ..4... 4,096 MHz ..2.. 2,048MHz ..200.. 10,240 kHz */
	//ads131a02.zetSampFreq(ADS131A02::ICLK::ICLK4, ADS131A02::FMOD::FMOD2, ADS131A02::ODR::ODR200);

#elif defined USE_STM32L432Nucleo32

#ifdef STM32L432Nucleo32BaudRate
	#if (STM32L432Nucleo32BaudRate==9600)
	ESEBoardController::setSampleTime(50);
#elif (STM32L432Nucleo32BaudRate==115200)
	ESEBoardController::setSampleTime(10);
#endif
#else
	ESEBoardController::setSampleTime(20);
#endif
#endif


}



/*************** ****************** ATTENTIE : OPMERKING / REMARK *******************************************/
/*************** HIERONDER NIETS MEER DOOR STUDENTEN TE VERANDEREN. *****************************************/
/*************** NOTHING TO BE ALTERED BY STUDENTS FROM HERE.       *****************************************/


/*! @class De basisklasse voor de Open lus en Controller lus proces /
 * The base class for the open loop and Controller loop process ******/
RGTProces::RGTProces(StdTaak &mt) : mijnTaak(mt)
{


#ifdef USE_STM32412G_DISCOVERY
	selekteerProces(STM32BoardController::RGTProcesSelektor::TweedeOrdeProces);
	selekteerADCAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
	selekteerDACAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
#elif defined USE_STM32L432Nucleo32
	/* Niet te doen hier door studenten.    */
	/* Nothing to be done here by students. */
#endif

}

RGTProces::RGTProces( StdTaak &mt,
                      PIDController *const pidc,
                      AanUitController * const auc) : pidController(pidc),
                                                      aanUitController(auc),
                                                      mijnTaak(mt)
{
	assert(nullptr != pidc);
	assert(nullptr != auc);

	/* Zet een hysterese van 0,5 V op */
	aanUitController->zetEigenschap(AanUitController::Eigenschap::Hysterese,0.5f);

#ifdef USE_STM32412G_DISCOVERY
	selekteerProces(STM32BoardController::RGTProcesSelektor::EersteOrdeProces);
	selekteerADCAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
	selekteerDACAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
#elif defined USE_STM32L432Nucleo32
	/* Niet te doen hier door studenten.    */
	/* Nothing to be done here by students. */
#ifndef NDEBUG
	RGTKompaktData kompaktData(1,1.0f,2.0f,3.0f);
	const auto kompaktGelukt = kompaktData.doeZelftest();
	assert(FoutCode::Ok == kompaktGelukt);
#endif
#endif
}

RGTProces::RGTProces( StdTaak &mt,
                      FuzzyController * const fuzzyc,
                      AanUitController * const auc) : fuzzyController(fuzzyc),
                                                      aanUitController(auc),
                                                      mijnTaak(mt)
{
	assert(nullptr != fuzzyc);
	assert(nullptr != auc);

	/* Zet een hysterese van 0,5 V op */
	aanUitController->zetEigenschap(AanUitController::Eigenschap::Hysterese,0.5f);

#ifdef USE_STM32412G_DISCOVERY
	selekteerProces(STM32BoardController::RGTProcesSelektor::EersteOrdeProces);
	selekteerADCAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
	selekteerDACAntiAlias(STM32BoardController::AntiAliasCtrl::AA5kHz);
#elif defined USE_STM32L432Nucleo32
	/* Niet te doen hier door studenten.    */
	/* Nothing to be done here by students. */
#ifndef NDEBUG
	RGTKompaktData kompaktData(1,1.0f,2.0f,3.0f);
	const auto kompaktGelukt = kompaktData.doeZelftest();
	assert(FoutCode::Ok == kompaktGelukt);
#endif
#endif
}

#ifdef InterfaceTaalNederlands
#ifdef InputResponsieOpdracht
const char * RGTProces::practicumtekst = "Opdracht 1 - Open Lus";
#else
const char * RGTProces::practicumtekst = "Opdracht 2-6: PID controller";
#endif
#else
#ifdef InputResponsieOpdracht
	const char * RGTProces::practicumtekst = "Assignment 2 - Open loop";
#else
	const char * RGTProces::practicumtekst = "Assignment 2-6: PID controller";
#endif

#endif

void RGTProces::mainLoop(const Schakelaar opLCD,
                         const bool oneindig)
{
	if (Schakelaar::Aan == opLCD)
		SEGGER_RTT_WriteString(0,"(RGTProces::mainLoop) met GUI.\n");
	else
		SEGGER_RTT_WriteString(0,"(RGTProces::mainLoop) zonder GUI.\n");
	//ads131a02.zelfTest();
	//transmitTitle("Dit is een teststring.");
	//ftdi.verstuurByte('G');
	//transmitTitle("Am 5. April 1978 erließ H. die Führung an ...");
#ifdef USE_STM32412G_DISCOVERY
	gebruikLCD = opLCD;
#endif

	// Repeat always
	while(true == oneindig)
	{
		RGTKommando rgtKommando;
		RGTKommando::Kommando kommando;

#ifdef USE_STM32412G_DISCOVERY
		if (Schakelaar::Aan == gebruikLCD)
		{
			sluitGrafiekGUI();
			
			/* 1. Kies het proces. */
			const auto proceskeuze = guiKiesProces();
			selekteerProces(proceskeuze);
			
			/* 2. Kies de signaalvorm */
			kommando = guiKiesSignaalVorm();

#if (defined(PIDControllerOpdracht))
			/* kies de controllervorm */
			controllerKeuze = guiKiesRegelaar();
			
			if (RGTKommando::RegelaarKeuze::PID == controllerKeuze)
			{
				if (nullptr != pidController)
				{
					WFT p,i,d;
					geefBKUPPIDWaarden(p,i,d);
					if (0.0f == p)
						p = 1.0f;  /* in ieder geval */
					
					pidController->zetPID(p,i,d);
				}
			}
#endif
			/* begin de aktie */
			GUI_Clear();
			initGrafiekGUI(aantalMeetPunten);
			startStopADCenDAC(Schakelaar::Aan);
		}
		else
#endif
		{
#ifdef USE_STM32412G_DISCOVERY
			if (Schakelaar::Uit == verbindingGemaakt)
			{
				knipperBlauwLED(KnipperLEDStand::Stop);
				guiToonDesktopStartMededeling();
			}
			else
			{
				knipperBlauwLED(KnipperLEDStand::Middel);
				guiToonDesktopVerbondenMededeling();
			}
#endif

			rgtKommando = wachtOpDesktopCommando();
			// voor test : rgtKommando = RGTKommando(RGTKommando::Kommando::Stap,2.0f,1000,0);
			kommando = rgtKommando.geefCommando();
		}

		if (kommando < RGTKommando::Kommando::ZetRegelaarKeuze)
		{
#ifdef USE_STM32412G_DISCOVERY
			knipperBlauwLED(KnipperLEDStand::Snel);
#endif
			if (Schakelaar::Uit == gebruikLCD)
			{
				setpoint = rgtKommando.geefSetPoint();
				aantalMeetPunten = rgtKommando.geefAantalPunten();
				vertraging = rgtKommando.geefVertraging();
				versterking = rgtKommando.geefVersterking();
			}
			else
			{
				setpoint = 3.0f;
				aantalMeetPunten = 250;
				vertraging = 25;
				versterking = 1.0f;
				zetBKUPSignaalKeuze(kommando);
			}
		}

		switch(kommando)
		{
			// ------------------------------------------------------------------------
			// OPEN LOOP
			// ------------------------------------------------------------------------
			case RGTKommando::Kommando::Stap:
			case RGTKommando::Kommando::Impuls:
			case RGTKommando::Kommando::Helling:
			{
				/* laat weten dat we beginnen */
				const StdTaak::StdMsg nieuwBericht(TaakPrio::Taak2,
				                                   TaakPrio::Taak1,
				                                   MsgType::StartStopGedrukt);
				mijnTaak.stuurBericht(nieuwBericht);

#ifdef USE_STM32412G_DISCOVERY
				if (Schakelaar::Uit == gebruikLCD)
					guiToonDesktopStatus(Schakelaar::Aan);
#endif
				SEGGER_RTT_WriteString(0,"(RGTProces::mainLoop) stap/impuls/helling kommando.\n");
				voerUitResponsie(kommando);
				/* laat weten dat we stoppen */
				mijnTaak.stuurBericht(nieuwBericht);
				bereidVoorMeting(); /* alvast voor de volgende keer */
			}
				break;

			case RGTKommando::Kommando::Blok:
			case RGTKommando::Kommando::Cosinus:
			{
				/* laat weten dat we beginnen */
				const StdTaak::StdMsg nieuwBericht(TaakPrio::Taak2,
				                                   TaakPrio::Taak1,
				                                   MsgType::StartStopGedrukt);
				mijnTaak.stuurBericht(nieuwBericht);

				if (Schakelaar::Uit == gebruikLCD)
				{
					startFrequentie = rgtKommando.geefStartFreq();
					amplitude = rgtKommando.geefAmplitude();
					numberOfPeriods = rgtKommando.geefAantalPerioden();
#ifdef USE_STM32412G_DISCOVERY
					guiToonDesktopStatus(Schakelaar::Aan);
#endif
				}
				else
				{
					startFrequentie = 1.0f;
					amplitude = 2.0f;
					setpoint = 2.5f;
					numberOfPeriods = 3;
				}

				SEGGER_RTT_WriteString(0,"(RGTProces::mainLoop) blok/cosinus kommando.\n");

				voerUitResponsie(kommando);

				/* laat weten dat we stoppen */
				mijnTaak.stuurBericht(nieuwBericht);
				bereidVoorMeting(); /* alvast voor de volgende keer */
			}
				break;

			case RGTKommando::Kommando::ZetProcesKeuze:
			{

				const auto keuze =  rgtKommando.geefProcesKeuze();
				/* direkte mapping bestaat hier maar kijk uit !*/
				const auto procesKeuze = static_cast<ESEBoardController::RGTProcesSelektor>(keuze);

				selekteerProces(procesKeuze);
				zetBKUPProcesKeuze(procesKeuze);
			}
				break;

			case RGTKommando::Kommando::GeefVersie:
			{
				stuurVersie();

				if (Schakelaar::Uit == verbindingGemaakt)
				{
					verbindingGemaakt = Schakelaar::Aan;
					/* laat weten dat we verbinding hebben. */
					const StdTaak::StdMsg nieuwBericht(TaakPrio::Taak2,
					                                   TaakPrio::Taak1,
					                                   MsgType::VerbindingGemaakt);
					mijnTaak.stuurBericht(nieuwBericht);

					startStopADCenDAC(Schakelaar::Aan);

					bereidVoorMeting();
				}
			}
				break;

			case RGTKommando::Kommando::GaSlapen:
			{
				if (Schakelaar::Aan == verbindingGemaakt)
				{
					verbindingGemaakt = Schakelaar::Uit;
					/* laat weten dat we geen verbinding meer hebben. */
					const StdTaak::StdMsg nieuwBericht(TaakPrio::Taak2,
					                                   TaakPrio::Taak1,
					                                   MsgType::VerbindingLosgemaakt);
					mijnTaak.stuurBericht(nieuwBericht);

					startStopADCenDAC(Schakelaar::Uit);
				}
			}
				break;

			case RGTKommando::Kommando::ZetRegelaarKeuze:
			{
				controllerKeuze = rgtKommando.geefRegelaarKeuze();
				zetBKUPRegelaarKeuze(controllerKeuze);
			}
				break;

			case RGTKommando::Kommando::ZetPIDParameters:
			{
				if(nullptr != pidController)
				{
#ifdef PIDControllerOpdracht
					controllerKeuze = RGTKommando::RegelaarKeuze::PID;
					
					const WFT pw = rgtKommando.geefPwaarde();
					const WFT iw = rgtKommando.geefIwaarde();
					const WFT dw = rgtKommando.geefDwaarde();
					zetBKUPPIDWaarden(pw,iw,dw);
					
					pidController->zetPID(pw, iw, dw);
#endif
				}
			}
				break;

			case RGTKommando::Kommando::ZetFuzzyParameters:
			{

			}
				break;

			case RGTKommando::Kommando::ZetOnOffParameters:
			{

			}
				break;

			case RGTKommando::Kommando::Leeg:
			{
				/* doe hier niets */
			}
				break;

			default:
				StopHier();
				break;
		}

	}

}

#ifdef USE_STM32412G_DISCOVERY
void RGTProces::guiToonDesktopStartMededeling()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum", 120, 8);
	GUI_DispStringHCenterAt(practicumtekst, 120, 30);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Start de Desktop applikatie", 120, 55);
#else
	GUI_DispStringHCenterAt("Start the Desktop application", 120, 55);
#endif
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringHCenterAt("\"RGTControl\"", 120, 100);
}

void RGTProces::guiToonDesktopVerbondenMededeling()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum", 120, 8);
	GUI_DispStringHCenterAt(practicumtekst, 120, 30);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Verbonden met de Desktop", 120, 55);
#else
	GUI_DispStringHCenterAt("Connected to the Desktop", 120, 55);
#endif
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringHCenterAt("\"RGTControl\"", 120, 100);
}

void RGTProces::guiToonDesktopStatus(const Schakelaar stand)
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum", 120, 8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt(practicumtekst, 120, 30);
	
	static const char *melding = ((Schakelaar::Uit == stand) ?
	                              "Het systeem wacht op een kommando" :
	                              "Het systeem is bezig .......");
#else
	
	GUI_DispStringHCenterAt(practicumtekst,120,30);

	static const char *melding = ((Schakelaar::Uit == stand) ?
	                              "The system waits for a command" :
	                              "The systeem is busy .......");
#endif
	
	GUI_DispStringHCenterAt(melding, 120, 55);
}

RGTProces::RGTProcesSelektor RGTProces::guiKiesProces()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt(practicumtekst,120,30);
	GUI_DispStringHCenterAt("Kies het proces:",120,55);
#else
	GUI_DispStringHCenterAt(practicumtekst,120,30);
	GUI_DispStringHCenterAt("Select the process:",120,55);
#endif
	
	GUI_SetFont(&GUI_Font16_1);
	
	bool wachtOpInstruktie = true;
	auto proceskeuze = static_cast<UInt32>(geefBKUPProcesKeuze());
	do
	{

#ifdef InterfaceTaalNederlands
		static const char *kommandosteksten[] =
			{ "Eerste orde proces","Tweede orde proces","Digitaal proces" };
#else
		static const char *kommandosteksten[] =
		{ "First order process","Second order process","Digital process" };
#endif
		UInt32 i=0;
		for (auto tekst : kommandosteksten)
		{
			GUI_SetTextMode((i == proceskeuze) ? GUI_TM_REV : GUI_TM_NORMAL);
			GUI_DispStringHCenterAt(tekst,120,100+(20*i));
			i++;
		}
		
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = wachtOpEenKnop(true);
		
		switch (knop)
		{
			case KnopID::Boven:
			{
				if (0 != proceskeuze)
					proceskeuze--;
				else
					proceskeuze = static_cast<UInt32>(RGTProcesSelektor::DigProces);
				
			};
				break;
			
			case KnopID::Onder:
			{
				if (proceskeuze != static_cast<UInt32>(RGTProcesSelektor::DigProces))
					proceskeuze++;
				else
					proceskeuze = static_cast<UInt32>(RGTProcesSelektor::EersteOrdeProces);
			};
				break;
			
			case KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;
			
			default:
				break;
		}
		
		HAL_Delay(250);
		
	} while (true == wachtOpInstruktie);
	
	const auto antwoord = static_cast<RGTProcesSelektor>(proceskeuze);
	zetBKUPProcesKeuze(antwoord);
	return(antwoord);
}

RGTKommando::Kommando RGTProces::guiKiesSignaalVorm()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
	GUI_DispStringHCenterAt(practicumtekst,120,30);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Kies de signaalvorm:",120,55);
#else
	GUI_DispStringHCenterAt("Select the signal:",120,55);
#endif
	
	GUI_SetFont(&GUI_Font16_1);
	
	bool wachtOpInstruktie = true;
	auto kommandokeuze = static_cast<UInt32>(geefBKUPSignaalKeuze());
	do
	{

#ifdef InterfaceTaalNederlands
		static const char *kommandosteksten[] =
			{ "Stap","Helling","Impuls","Blok","Cosinus"};
#else
		static const char *kommandosteksten[] =
		{ "Step","Slope","Impulse","Rectangular","Cosine"};
#endif
		UInt32 i=0;
		for (auto tekst : kommandosteksten)
		{
			GUI_SetTextMode((i == kommandokeuze) ? GUI_TM_REV : GUI_TM_NORMAL);
			GUI_DispStringHCenterAt(tekst,120,100+(20*i));
			i++;
		}
		
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = wachtOpEenKnop(true);
		
		switch (knop)
		{
			case KnopID::Boven:
			{
				if (0 != kommandokeuze)
					kommandokeuze--;
				else
					kommandokeuze = static_cast<UInt32>(RGTKommando::Kommando::Cosinus);
				
			};
				break;
			
			case KnopID::Onder:
			{
				if (kommandokeuze != static_cast<UInt32>(RGTKommando::Kommando::Cosinus))
					kommandokeuze++;
				else
					kommandokeuze = static_cast<UInt32>(RGTKommando::Kommando::Stap);
			};
				break;
			
			case KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;
			
			default:
				break;
		}
		
		HAL_Delay(250);
		
	} while (true == wachtOpInstruktie);
	
	const auto antwoord = static_cast<RGTKommando::Kommando>(kommandokeuze);
	zetBKUPSignaalKeuze(antwoord);
	return(antwoord);
}

RGTKommando::RegelaarKeuze RGTProces::guiKiesRegelaar()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringHCenterAt("ESE ECSL practicum",120,8);
	GUI_DispStringHCenterAt(practicumtekst,120,30);
#ifdef InterfaceTaalNederlands
	GUI_DispStringHCenterAt("Kies de regelaar:",120,55);
#else
	GUI_DispStringHCenterAt("Select the controller:",120,55);
#endif
	
	GUI_SetFont(&GUI_Font16_1);
	
	bool wachtOpInstruktie = true;
	auto regelaarkeuze = static_cast<UInt32>(geefBKUPRegelaarKeuze());
	do
	{
		
		/* OpenLoop,
		OnOff,
		PID,
		Fuzzy */
#ifdef InterfaceTaalNederlands
		static const char *kommandosteksten[] =
			{ "Open Lus","Aan-Uit","PID","Fuzzy"};
#else
		static const char *kommandosteksten[] =
		{ "Open Loop","On-Off","PID","Fuzzy"};
#endif
		UInt32 i=0;
		for (auto tekst : kommandosteksten)
		{
			GUI_SetTextMode((i == regelaarkeuze) ? GUI_TM_REV : GUI_TM_NORMAL);
			GUI_DispStringHCenterAt(tekst,120,100+(20*i));
			i++;
		}
		
		/* Wacht tot een knop is ingedrukt. */
		const auto knop = wachtOpEenKnop(true);
		
		switch (knop)
		{
			case KnopID::Boven:
			{
				if (0 != regelaarkeuze)
					regelaarkeuze--;
				else
					regelaarkeuze = static_cast<UInt32>(RGTKommando::RegelaarKeuze::Fuzzy);
				
			};
				break;
			
			case KnopID::Onder:
			{
				if (regelaarkeuze != static_cast<UInt32>(RGTKommando::RegelaarKeuze::Fuzzy))
					regelaarkeuze++;
				else
					regelaarkeuze = static_cast<UInt32>(RGTKommando::RegelaarKeuze::OpenLoop);
			};
				break;
			
			case KnopID::Links:
			{
				wachtOpInstruktie = false;
			};
				break;
			
			default:
				break;
		}
		
		HAL_Delay(250);
		
	} while (true == wachtOpInstruktie);
	
	const auto antwoord = static_cast<RGTKommando::RegelaarKeuze >(regelaarkeuze);
	zetBKUPRegelaarKeuze(antwoord);
	return(antwoord);
}
#endif /* F412 discovery. */

Spanning RGTProces::maakInput(const RGTKommando::Kommando kommando,
                              const RGTData::SampleMoment n)
{
	Spanning inputValue;
	switch (kommando)
	{
		case RGTKommando::Kommando::Stap:
			inputValue = stepInputSignal(n);
			break;
		case RGTKommando::Kommando::Impuls:
			inputValue = impulseInputSignal(n);
			break;
		case RGTKommando::Kommando::Helling:
			inputValue = rampInputSignal(n);
			break;
		case RGTKommando::Kommando::Blok:
			inputValue = squareWaveInputSignal(n);
			break;
		case RGTKommando::Kommando::Cosinus:
			inputValue = cosineInputSignal(n);
			break;
		default:
			StopHier();
			inputValue = 0.0f;
			break;
	}

	return(inputValue);
}

void RGTProces::voerUitResponsie(const RGTKommando::Kommando kommando)
{
	assert(kommando <= RGTKommando::Kommando::Cosinus);

	if ((kommando == RGTKommando::Kommando::Blok) ||
	    (kommando == RGTKommando::Kommando::Cosinus))
		bereidVoorPeriodiekeFunktie();

	RGTData::SampleMoment n = 0, j = getNumberOfPoints();

	switch (controllerKeuze)
	{
		case RGTKommando::RegelaarKeuze::OpenLoop:
		{
			SEGGER_RTT_WriteString(0,"(RGTProces::voerUitResponsie) Start responsie.\n");
			if (Schakelaar::Uit == gebruikLCD)
			{
#ifdef InterfaceTaalNederlands
				static char const *const teksten[] = {"Open lus stapresponsie",
				                                      "Open lus hellingresponsie",
				                                      "Open lus impulsresponsie",
				                                      "Open lus blokgolfresponsie",
				                                      "Open lus cosinusresponsie"};
#else
				static char const *const teksten[] = {"Open loop step response",
				                                      "Open loop slope response",
				                                      "Open loop impulse response",
				                                      "Open loop rect wave response",
				                                      "Open loop cosine response"};
#endif

				const auto index = static_cast<UInt32>(kommando);
				const RGTTitel titel(teksten[index]);
				transmitTitle(titel);
			}

			/* wacht 300 ms voor sync met de desktop. */
			mijnTaak.wacht(300);

			do
			{
				const auto inputValue = maakInput(kommando,n);
				openlus(n, inputValue, inputValue);
				n++;
			} while (--j != 0);
		}

			break;

		case RGTKommando::RegelaarKeuze::PID:
		{
#ifdef PIDControllerOpdracht
			if (Schakelaar::Uit == gebruikLCD)
			{
#ifdef InterfaceTaalNederlands
				static char const *const teksten[] = {"PID stapresponsie",
				                                      "PID hellingresponsie",
				                                      "PID impulsresponsie",
				                                      "PID blokgolfresponsie",
				                                      "PID cosinusresponsie"};
#else
				static char const * const teksten[] = { "PID step response",
														"PID slope response",
														"PID impulse response",
														"PID rectangular wave response",
														"PID cosine response" };
#endif
				const auto index = static_cast<UInt32>(kommando);
				const RGTTitel titel(teksten[index]);
				transmitTitle(titel);
			}

			/* wacht 300 ms voor sync met de desktop. */
			mijnTaak.wacht(300);


			Spanning meetwaarde = 0.0f;
			
			do
			{
				const auto inputValue = maakInput(kommando,n);
				assert(nullptr != pidController);
				const Spanning controleWaarde = pidController->pidFunktie(inputValue,
				                                                           meetwaarde);
				
				meetwaarde = openlus(n, inputValue,controleWaarde);
				n++;
			} while (--j != 0);
			
			pidController->reset();
#else
			negeer(); /* stuur negeer patroon. */
#endif
		}
			break;

		case RGTKommando::RegelaarKeuze::OnOff:
		{
#if (defined(PIDControllerOpdracht) || defined(FuzzyOpdracht))
			if (Schakelaar::Uit == gebruikLCD)
			{
#ifdef InterfaceTaalNederlands
				static char const *const teksten[] = {"Aan-Uit stapresponsie",
				                                      "Aan-Uit hellingresponsie",
				                                      "Aan-Uit impulsresponsie",
				                                      "Aan-Uit blokgolfresponsie",
				                                      "Aan-Uit cosinusresponsie"};
#else
				static char const * const teksten[] = { "On-Off step response",
														"On-Off slope response",
														"On-Off impulse response",
														"On-Off rectangular wave response",
														"On-Off cosine response" };
#endif
				const auto index = static_cast<UInt32>(kommando);
				const RGTTitel titel(teksten[index]);
				transmitTitle(titel);
			}

			/* wacht 300 ms voor sync met de desktop. */
			mijnTaak.wacht(300);


			Spanning meetwaarde = 0.0f;
			
			do
			{
				const auto inputValue = maakInput(kommando,n);
				assert(nullptr != aanUitController);
				const Spanning controleWaarde = aanUitController->aanUitFunktie(inputValue,
				                                                                 meetwaarde);
				
				meetwaarde = openlus(n, inputValue,controleWaarde);
				n++;
			} while (--j != 0);

#else
			negeer(); /* stuur negeer patroon. */
#endif
		}
			break;

		case RGTKommando::RegelaarKeuze::Fuzzy:
		{
#ifdef FuzzyOpdracht
			if (Schakelaar::Uit == gebruikLCD)
			{
#ifdef InterfaceTaalNederlands
				static char const *const teksten[] = {"Fuzzy stapresponsie",
				                                      "Fuzzy hellingresponsie",
				                                      "Fuzzy impulsresponsie",
				                                      "Fuzzy blokgolfresponsie",
				                                      "Fuzzy cosinusresponsie"};
#else
				static char const * const teksten[] = { "Fuzzy step response",
														"Fuzzy slope response",
														"Fuzzy impulse response",
														"Fuzzy rectangular wave response",
														"Fuzzy cosine response" };
#endif
				const auto index = static_cast<UInt32>(kommando);
				const RGTTitel titel(teksten[index]);
				transmitTitle(titel);
			}
			Spanning meetwaarde = 0.0f;

			do
			{
				const auto inputValue = maakInput(kommando,n);
				assert(nullptr != fuzzyController);
				const Spanning controleWaarde = fuzzyController->fuzzyFunktie(inputValue,
				                                                                 meetwaarde);

				meetwaarde = openlus(n, inputValue,controleWaarde);
				n++;
			} while (--j != 0);

#else
			negeer(); /* stuur negeer patroon. */
#endif
		}
			break;

		default:
			negeer(); /* stuur negeer patroon. */
			/* de rest nog in te vullen */
			break;
	}
}

void RGTProces::bereidVoorMeting()
{
#ifdef USE_STM32412G_DISCOVERY
	max5136.zetSpanning(RGTDacKanaal, 0.0f);
	if (Schakelaar::Aan == gebruikLCD)
		startStopADCenDAC(Schakelaar::Uit);
#elif defined USE_STM32L432Nucleo32
	zetDAC(0.0f);
#endif
}

void RGTProces::bereidVoorPeriodiekeFunktie()
{
	pointsPerPeriod = aantalMeetPunten/(numberOfPeriods);
	pointsPerHalfPeriod = pointsPerPeriod/2;
	cosStapGrootte = static_cast<UInt32>(pointsPerHalfPeriod*startFrequentie/(100.0f));

	/* begrens op het minimum */
	if (cosStapGrootte==0)
		cosStapGrootte=1;

	cosStapper=cosStapGrootte;

	cosArgBasis = PI/pointsPerHalfPeriod;
	cosArg = 0.0f;
}

UInt16 RGTProces::getNumberOfPoints() const
{
	return(aantalMeetPunten);
}

void RGTProces::setStartDelay(const RGTData::SampleMoment aantal)
{
	assert(aantal< aantalMeetPunten);
	vertraging = aantal;
}

RGTData::SampleMoment RGTProces::getStartDelay() const
{
	return(vertraging);
}

void RGTProces::setSetPoint(const Spanning amp)
{
	setpoint = amp;

}

Spanning RGTProces::getSetPoint() const
{
	return(setpoint);
}

/* Gemeenschappelijk */
void RGTProces::negeer()
{
#ifdef InterfaceTaalNederlands
	static char const * const negeerTekst = "Nu niet in gebruik";
#else
	static char const *const negeerTekst = "Now not in use";
#endif
	const RGTTitel titel(negeerTekst);
	transmitTitle(titel);

	/* stuur het paasei */
	static constexpr auto paaseiOffset=1.5f;
	static constexpr auto paaseiOndergrens=0.0f;
	static constexpr auto paaseiBovengrens=3.0f;
#ifdef USE_STM32412G_DISCOVERY
	const auto bt = 20;
#else
	const auto bt = getSampleTime();
#endif
	auto spGroeiFaktor = (10.0f*2.0f*paaseiOffset)/aantalMeetPunten;
	auto mwGroeiFaktor = -1.0f*spGroeiFaktor;

	auto sp = 0.0f,mw = 2*paaseiOffset;
	auto n=0;
	auto j = aantalMeetPunten;

	do
	{
		const auto e = paaseiOffset; //sp-mw;

#ifdef USE_STM32412G_DISCOVERY
		if (Schakelaar::Uit == gebruikLCD)
	{
		/* bouw het data objekt dat naar de PC terug gaat */
		const RGTData rgtData(n, mw,sp,e);
		transmitData(rgtData);
	}
	else
	{
		const auto guiInvoerWaarde = static_cast<Int16>(grafiekGrootte * sp / 5.0f);
		const auto guiMeetWaarde = static_cast<Int16>(grafiekGrootte * mw / 5.0f);
		GRAPH_DATA_YT_AddValue(invoerDataHandle, guiInvoerWaarde);
		GRAPH_DATA_YT_AddValue(procesDataHandle, guiMeetWaarde);
		GUI_Exec();
	}
#elif defined USE_STM32L432Nucleo32
		/* bouw het data objekt dat naar de PC terug gaat */
		/* * @param n : Het samplemoment.
* @param mv  : de meetwaarde.
* @param rv  : de regelwaarde (setpoint).
* @param cv  : de controle waarde  (proces input). */

		const RGTData rgtData(n, mw,sp,e);
		transmitData(rgtData);
#endif
		sp += spGroeiFaktor;
		if ((sp>paaseiBovengrens) || (sp<paaseiOndergrens))
			spGroeiFaktor *= -1.0f;

		mw += mwGroeiFaktor;
		if ((mw>paaseiBovengrens) || (mw<paaseiOndergrens))
			mwGroeiFaktor *= -1.0f;

		n++;

		mijnTaak.wacht(bt);  /* wacht tussen de virtuele metingen de bemonsteringtijd. */

	} while (--j != 0);

	transmitData();  /* stuur het restant van de buffer uit */
}


Schakelaar RGTProces::geefBKUPGebruikLCDKeuze()
{
	const auto stand = static_cast<Schakelaar>(backupGeheugenLezen(GebruikLCDBKUPVeld));
	return(stand);
}

void RGTProces::zetBKUPGebruikLCDKeuze(const Schakelaar stand)
{
	const auto s = static_cast<UInt32>(stand);
	backupGeheugenOpslaan(GebruikLCDBKUPVeld,s);
}

ESEBoardController::RGTProcesSelektor RGTProces::geefBKUPProcesKeuze()
{
	const auto stand = static_cast<ESEBoardController::RGTProcesSelektor>(backupGeheugenLezen(ProcesKeuzeBKUPVeld));
	return(stand);
}

void RGTProces::zetBKUPProcesKeuze(const ESEBoardController::RGTProcesSelektor proces)
{
	const auto s = static_cast<UInt32>(proces);
	backupGeheugenOpslaan(ProcesKeuzeBKUPVeld,s);
}

RGTKommando::Kommando RGTProces::geefBKUPSignaalKeuze()
{
	const auto stand = static_cast<RGTKommando::Kommando>(backupGeheugenLezen(SignaalKeuzeBKUPVeld));
	return(stand);
}

void RGTProces::zetBKUPSignaalKeuze(const RGTKommando::Kommando kommando)
{
	const auto s = static_cast<UInt32>(kommando);
	backupGeheugenOpslaan(SignaalKeuzeBKUPVeld,s);
}

RGTKommando::RegelaarKeuze RGTProces::geefBKUPRegelaarKeuze()
{
	const auto stand = static_cast<RGTKommando::RegelaarKeuze>(backupGeheugenLezen(ProcesRegelaarBKUPVeld));
	return(stand);
}

void RGTProces::zetBKUPRegelaarKeuze(const RGTKommando::RegelaarKeuze keuze)
{
	const auto s = static_cast<UInt32>(keuze);
	backupGeheugenOpslaan(ProcesRegelaarBKUPVeld,s);
}

void RGTProces::geefBKUPPIDWaarden(WFT &p, WFT &i, WFT &d)
{
	p = static_cast<WFT>(backupGeheugenLezen(RegelaarPID_P_BKUPVeld));
	i = static_cast<WFT>(backupGeheugenLezen(RegelaarPID_I_BKUPVeld));
	d = static_cast<WFT>(backupGeheugenLezen(RegelaarPID_D_BKUPVeld));
}

void RGTProces::zetBKUPPIDWaarden(const WFT p, const WFT i, const WFT d)
{
	auto waarde = static_cast<UInt32>(p);
	backupGeheugenOpslaan(RegelaarPID_P_BKUPVeld,waarde);

	waarde = static_cast<UInt32>(i);
	backupGeheugenOpslaan(RegelaarPID_I_BKUPVeld,waarde);

	waarde = static_cast<UInt32>(d);
	backupGeheugenOpslaan(RegelaarPID_D_BKUPVeld,waarde);
}





