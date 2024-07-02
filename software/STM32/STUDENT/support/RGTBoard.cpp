/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
RGT Controller implementatie voor PRJ3PRT

@version $Rev: 3993 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2018 Hogeschool van Arnhem en Nijmegen
         
$Id: RGTBoard.cpp 3993 2020-10-01 16:24:31Z ewout $
************************************************************************/

#include <string.h>
#include <assert.h>
#include <RGTBoard.h>
#include <cmsis_os.h>


#ifdef USE_STM32412G_DISCOVERY

#include <standaardGrafiekVenster.h>

RGTBoard::RGTBoard() : ESEBoardController(96)
{

};

RGTKommando RGTBoard::wachtOpDesktopCommando()
{
	RGTKommando desktopKommando;
	
	/* wacht hier op het kommando */
	ftdi.ontvang(desktopKommando);
	
	return(desktopKommando);
}


void RGTBoard::transmitTitle(const RGTTitel &titel)
{
	ftdi.verstuur(titel);
}

void RGTBoard::transmitData(const RGTData &rgtData)
{
	
	auto &vb = geefHuidigeVulBuffer();
	/* kopieer de data naar de vulbuffer */
	if (true == vb.laadBuffer(rgtData))
	{
		/* vulbuffer wordt nu zendbuffer. */
		wisselBuffer();
		/* stuur de zendbuffer uit. Vullen gaat nu door in de andere buffer. */
		auto &zb = geefHuidigeZendBuffer();
		ftdi.verstuur(zb);
		zb.resetBuffer();
	}
}

void RGTBoard::transmitData()
{
	auto &vb = geefHuidigeVulBuffer();
	if (true == vb.bevatBufferData())
	{
		/* vulbuffer wordt nu zendbuffer. */
		wisselBuffer();
		/* stuur de zendbuffer uit. Vullen gaat nu door in de andere buffer. */
		auto &zb = geefHuidigeZendBuffer();
		ftdi.verstuur(zb);
		zb.resetBuffer();
	}
}


#elif defined USE_STM32L432Nucleo32

#include <STM32L4xxNucleo32.h>
#include <stdTaak.h>
#include <RTT/SEGGER_RTT.h>


ESEBoardController::ESEBoardController(const UInt32 freq) : STM32L432Nucleo32(freq)
{

}

CountingSemaphore ESEBoardController::adcSem;

void ESEBoardController::startStopADC(const Schakelaar stand)
{
	switch(stand)
	{
		case Schakelaar::Aan:
		{
			HAL_TIM_Base_Start(&htim6);
			HAL_ADC_Start_IT(&hadc1);
		}
			break;

		case Schakelaar::Uit:
		{
			HAL_TIM_Base_Stop(&htim6);
			HAL_ADC_Stop_IT(&hadc1);
		}
			break;

		default:
			StopHier();
			break;
	}
}


void ESEBoardController::setSampleTime(const UInt16 msecs)
{
	/* maximaal 6553 milliseconden sample tijd */
	assert(msecs < 6553);

	bemonsteringTijd = msecs;

	assert(bemonsteringTijd != 0);

	/* TIM6 werkt */
	auto * timInit = &(htim6.Init);
	timInit->Prescaler = 8000;
	timInit->CounterMode = TIM_COUNTERMODE_UP;
	timInit->Period = static_cast<UInt16 >(10*msecs);
	timInit->AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	TIM_Base_SetConfig(htim6.Instance,timInit);

}

UInt16 ESEBoardController::getSampleTime() const
{
	assert(bemonsteringTijd != 0);
	return(bemonsteringTijd);
}

void ESEBoardController::startStopDAC(const Schakelaar stand)
{
	switch(stand)
	{
		case Schakelaar::Aan:
		{
			HAL_DAC_Start(&hdac1,RGTDacKanaal);
		}
			break;

		case Schakelaar::Uit:
		{
			HAL_DAC_Stop(&hdac1,RGTDacKanaal);
		}
			break;

		default:
			StopHier();
			break;
	}
}

void ESEBoardController::zetDAC(const Spanning sp)
{
	static constexpr auto DACConv = MaxDAC/DACRef;

	const auto waarde = static_cast<UInt16>(DACConv*sp);
	if (HAL_OK != HAL_DAC_SetValue(&hdac1,RGTDacKanaal,DAC_ALIGN_12B_R,waarde))
	{
		StopHier();
	}
	else
	{
		/* doe een SW trigger */
		SET_BIT(hdac1.Instance->SWTRIGR, DAC_SWTRIGR_SWTRIG1);
	}
}

Spanning ESEBoardController::leesADC()
{
	/* wacht tot een conversie gedaan is */
#ifndef FreeRTOSGebruikt
	while (false == isrSem[sem(Semafoor::Rx)]);
#else
	isrSem[sem(Semafoor::ADC)].Take();
#endif

	const auto adcWaarde = HAL_ADC_GetValue(&hadc1);

	static constexpr auto ADCConv = DACRef/MaxDAC;

	const auto uit = (ADCConv*adcWaarde*boardKompensatieFaktor);

	return(uit);
}

void ESEBoardController::selekteerProces(const ESEBoardController::RGTProcesSelektor proces)
{
	static constexpr auto eersteOrdeKomp = 1.0f;  //* niet meer met deler weerstand : 5.0f/3.0f;
	static constexpr auto tweedeOrdeKomp = 1.0f;

	boardKompensatieFaktor = ((RGTProcesSelektor::EersteOrdeProces == proces) ? eersteOrdeKomp : tweedeOrdeKomp);

}



/**
* @brief This function handles ADC1 global interrupt.
*/
extern "C" void ADC1_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&ESEBoardController::hadc1);

	static constexpr auto index = STM32L432Nucleo32::sem(STM32L432Nucleo32::Semafoor::ADC);
#ifndef FreeRTOSGebruikt
	STM32L432Nucleo32::isrSem[index] = true;
#else
	auto &sem = STM32L432Nucleo32::isrSem[index];
	STM32L432Nucleo32::isrSemafoorAfhandeling(sem);
#endif
}



RGTBoard::RGTBoard() : ESEBoardController()
{

}

RGTKommando RGTBoard::wachtOpDesktopCommando()
{
	RGTKommando desktopKommando alignas(UInt32);

	/* wacht hier op het kommando */
	SEGGER_RTT_WriteString(0,"(RGTProces::wachtOpDesktopCommando) wacht op desktop kommando.\n");
	receive(BoardUART::UART2,desktopKommando);
	SEGGER_RTT_WriteString(0,"(RGTProces::wachtOpDesktopCommando) kommando ontvangen.\n");
	return(desktopKommando);
}


void RGTBoard::transmitTitle(const RGTTitel &titel)
{
	send(BoardUART::UART2,titel);
}

void RGTBoard::transmitData(const RGTData &rgtData)
{
	auto &vb = geefHuidigeVulBuffer();
	/* kopieer de data naar de vulbuffer */
	if (true == vb.laadBuffer(rgtData))
	{
		/* vulbuffer wordt nu zendbuffer. */
		wisselBuffer();
		SEGGER_RTT_WriteString(0,"(RGTBoard::transmitData) Data wordt verzonden.\n");
		/* stuur de zendbuffer uit. Vullen gaat nu door in de andere buffer. */
		auto &zb = geefHuidigeZendBuffer();
		send(BoardUART::UART2,zb);
		zb.resetBuffer();
	}
}

void RGTBoard::transmitData()
{
	auto &vb = geefHuidigeVulBuffer();
	if (true == vb.bevatBufferData())
	{
		/* vulbuffer wordt nu zendbuffer. */
		wisselBuffer();
		SEGGER_RTT_WriteString(0,"(RGTBoard::transmitData) Laatste data wordt verzonden.\n");
		/* stuur de zendbuffer uit. Vullen gaat nu door in de andere buffer. */
		auto &zb = geefHuidigeZendBuffer();
		send(BoardUART::UART2,zb);
		zb.resetBuffer();
	}
}

#endif



Spanning RGTBoard::openlus(const RGTData::SampleMoment n,
                           const Spanning setpoint,
                           const Spanning procesInput)
{
	Spanning meetSpanning;
#ifdef USE_STM32412G_DISCOVERY
	ads131a02.wachtOpDataReady();
	
	/* haal de data op uit de ADC */
	ads131a02.laadConversieData();
	/* konverteer naar floating point */
	meetSpanning = ads131a02.konverteer(RGTAdcKanaal);
	
	// Control the process with new calculated control value
	max5136.zetSpanning(RGTDacKanaal, procesInput);

#elif defined USE_STM32L432Nucleo32
	meetSpanning = leesADC();
	zetDAC(procesInput);

#endif
	
	const Spanning versterkteMeetSpanning = versterking * meetSpanning;

#ifdef USE_STM32412G_DISCOVERY
	if (Schakelaar::Uit == gebruikLCD)
	{
		/* bouw het data objekt dat naar de PC terug gaat */
		const RGTData rgtData(n, versterkteMeetSpanning, setpoint, procesInput);
		transmitData(rgtData);
	}
	else
	{
		const auto guiInvoerWaarde = static_cast<Int16>(grafiekGrootte * procesInput / 5.0f);
		const auto guiMeetWaarde = static_cast<Int16>(grafiekGrootte * versterkteMeetSpanning / 5.0f);
		GRAPH_DATA_YT_AddValue(invoerDataHandle, guiInvoerWaarde);
		GRAPH_DATA_YT_AddValue(procesDataHandle, guiMeetWaarde);
		GUI_Exec();
	}
#elif defined USE_STM32L432Nucleo32
	/* bouw het data objekt dat naar de PC terug gaat */
	const RGTData rgtData(n, versterkteMeetSpanning, setpoint, procesInput);
	transmitData(rgtData);
#endif

	return (meetSpanning);
}

void RGTBoard::stuurVersie()
{
	/* stuur versie terug, zoals Hugo heeft voorgesteld. */
	const RGTKommando antwoord(RGTKommando::Kommando::AntwoordNaarDesktop);

#ifdef USE_STM32412G_DISCOVERY
	ftdi.verstuur(antwoord);
#elif defined USE_STM32L432Nucleo32
	send(BoardUART::UART2,antwoord);
#endif
}


void RGTBoard::startStopADCenDAC(const Schakelaar schakelaar)
{

#ifdef USE_STM32412G_DISCOVERY
	
	if (Schakelaar::Aan == schakelaar)
	{
		/* voor debug */
		max5136.start(RGTDacKanaal);
		max5136.zetSpanning(RGTDacKanaal, 0.0f, true);
		
		ads131a02.start();
		
	}
	else
	{
		max5136.zetSpanning(RGTDacKanaal, 0.0f, true);
		max5136.reset();
		max5136.stop(RGTDacKanaal);
		
		ads131a02.stop();
		
	}
#elif defined USE_STM32L432Nucleo32
	startStopADC(schakelaar);
	startStopDAC(schakelaar);
#else
#error "(RGTBoard::startStopADCenDAC) Geen ondersteund bord gedefinieerd"
#endif
}



void RGTBoard::wisselBuffer()
{
	vulBuffer = ((BufferKeuze::Buffer1==vulBuffer) ?
	             BufferKeuze::Buffer2 : BufferKeuze::Buffer1);
}


RGTDataBuffer & RGTBoard::geefHuidigeVulBuffer() const
{
	const auto index = static_cast<Teller>(vulBuffer);
	auto & buf = const_cast<RGTDataBuffer &>(txRGTDataBuffer[index]);
	return(buf);
}

RGTDataBuffer &RGTBoard::geefHuidigeZendBuffer() const
{
	const auto index = static_cast<Teller>((BufferKeuze::Buffer1==vulBuffer) ?
	                                       BufferKeuze::Buffer2 : BufferKeuze::Buffer1);
	auto & buf = const_cast<RGTDataBuffer &>(txRGTDataBuffer[index]);
	return(buf);
}



#ifdef StemWinAanwezig
void RGTBoard::dialoogMessageParser(WM_MESSAGE * pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_INIT_DIALOG:
			/* niets */
			break;
		case WM_NOTIFY_PARENT:
		
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

void RGTBoard::initGrafiekGUI(const UInt32 aantalMeetPunten)
{
	if (WM_HWIN_NULL != grafiek)
		WM_ShowWindow(grafiek);
	else
	{
//		static const GUI_WIDGET_CREATE_INFO grafiekDialoogData[] =
//			{
//				{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0,
//					0, 0, grafiekGrootte, grafiekGrootte, 0, 0x0, 0 },
//				{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0,
//					0, 0, grafiekGrootte, grafiekGrootte, 0, 0x0, 0 }
//			};
//
//		static constexpr auto DialoogDataHoeveelheid = GUI_COUNTOF(grafiekDialoogData);
//
		grafiek = GRAPH_CreateEx(0, 0, grafiekGrootte, grafiekGrootte,
			WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_GRAPH0);

		GRAPH_SetColor(grafiek,GUI_WHITE,GRAPH_CI_BK);
		GRAPH_SetColor(grafiek,GUI_GRAY,GRAPH_CI_BORDER);
		GRAPH_SetColor(grafiek,GUI_DARKGRAY,GRAPH_CI_GRID);
		
		GRAPH_SetGridVis(grafiek,1);
		
//		venster = GUI_CreateDialogBox(grafiekDialoogData,
//		                              DialoogDataHoeveelheid,
//		                              RGTBoard::dialoogMessageParser,
//		                              WM_HBKWIN, 0, 0);
//		grafiek = WM_GetDialogItem(venster, ID_GRAPH_0);
		
		invoerDataHandle = GRAPH_DATA_YT_Create(GUI_BLUE, GUIMaxDataLengte, guiInvoerData, aantalMeetPunten);
		procesDataHandle = GRAPH_DATA_YT_Create(GUI_DARKGREEN, GUIMaxDataLengte, guiProcesData, aantalMeetPunten);
		
		for (auto &handle : { invoerDataHandle,procesDataHandle})
		{
			GRAPH_AttachData(grafiek, handle);
			GRAPH_DATA_YT_SetOffY(handle, grafiekOffset);
		}
		
		guiSchaal = GRAPH_SCALE_Create(20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);
		static constexpr auto ySchaalFaktor = 5.0f/grafiekGrootte;
		GRAPH_SCALE_SetFactor(guiSchaal,ySchaalFaktor);
		GRAPH_AttachScale(grafiek, guiSchaal);
		GRAPH_SetBorder(grafiek,20,0,0,0);

#ifdef InterfaceTaalNederlands
		static const char *melding = "Druk een toets";
#else
		static const char *melding = "Press a button";
#endif
		tekstVeld =  TEXT_CreateEx(50,200,180,20,grafiek,
				WM_CF_HIDE,0,GUI_ID_TEXT0,melding);

		TEXT_SetFont(tekstVeld,&GUI_FontComic24B_1);
		TEXT_SetTextColor(tekstVeld,GUI_DARKMAGENTA);
	}
}

void RGTBoard::sluitGrafiekGUI()
{
	if (WM_HWIN_NULL != grafiek)
	{
		WM_ShowWindow(tekstVeld);
		GUI_Exec();
		wachtOpEenKnop(true);
		WM_HideWindow(tekstVeld);

		for (auto &handle : {invoerDataHandle, procesDataHandle})
		{
			GRAPH_DATA_YT_Clear(handle);
		}
		WM_HideWindow(grafiek);
		//WM_DeleteWindow(grafiek);
		//WM_DeleteWindow(venster);
		GUI_Exec();
	}



}

#endif