/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file
RGT Controller API voor PRJ3PRT

@version $Rev: 4294 $
@author $Author: ewout $

@copyright Copyright 2013-2018 Hogeschool van Arnhem en Nijmegen

$Id: RGTBoard.h 4294 2021-06-22 12:51:19Z ewout $
************************************************************************/

#ifndef HANESE_REGELTECHNIEK_H
#define HANESE_REGELTECHNIEK_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <thread.hpp>
#include <RGTData.h>

#ifdef USE_STM32412G_DISCOVERY

#include <ESEBoardController.h>
#ifdef StemWinAanwezig
#include <WM.h>
#include <GRAPH.h>
#include <DIALOG.h>
#endif

/*! @brief De basisklasse voor de regeltechniek microcontroller */
class RGTBoard : public ESEBoardController
{

protected:

	/*! @brief De constructor. */
	RGTBoard();

	/*! @brief Transmit the title, always 30 characters */
	void transmitTitle(const RGTTitel &);

	/*! @brief Stuur de board versie naar de desktop applikatie*/
	void stuurVersie();

	/* voor RGT practicum */
	void transmitData(const RGTData &);
	/* Stuur het restant van de buffer uit aan het einde van een sessie */
	void transmitData();

	void startStopADCenDAC(const Schakelaar );

	RGTKommando wachtOpDesktopCommando();

	/*! @brief deze funktie implementeert de open lus van het proces met argument als invoer .
	 * @param Het sample moment.
	 * @param Het setpoint.
	 * @param de proces input. */
	Spanning openlus(const RGTData::SampleMoment, const Spanning, const Spanning);

	void negeer(const UInt16 aantalPunten, const Spanning setpoint);  /* stuurt negeer patroon terug naar de host */

	static constexpr auto RGTAdcKanaal = ADS131A02::Kanaal::K1;
	static constexpr auto RGTDacKanaal = MAX5136::Kanaal::K1;

	RGTKommando::RegelaarKeuze controllerKeuze = RGTKommando::RegelaarKeuze::OpenLoop;

	float versterking=1.0f;

	Schakelaar verbindingGemaakt = Schakelaar::Uit;
	Schakelaar gebruikLCD = Schakelaar::Uit;
#ifdef StemWinAanwezig
	
	static void dialoogMessageParser(WM_MESSAGE *);
	
	/*! init de grafiek.
	 * @param het aantal meetpunten. */
	void initGrafiekGUI(const UInt32 );
	void sluitGrafiekGUI();
	
	WM_HWIN venster = WM_HWIN_NULL;
	WM_HWIN grafiek = WM_HWIN_NULL;
	TEXT_Handle tekstVeld;

	GRAPH_DATA_Handle invoerDataHandle,procesDataHandle;
	GRAPH_SCALE_Handle guiSchaal;
	
	static constexpr auto GUIMaxDataLengte=1000;
	Int16 guiInvoerData[GUIMaxDataLengte];
	Int16 guiProcesData[GUIMaxDataLengte];
	
	static constexpr auto grafiekGrootte = 240;
	static constexpr auto grafiekOffset = 0;
	
#endif

private:

	enum class BufferKeuze
	{
		Buffer1=0,
		Buffer2
	} vulBuffer = BufferKeuze::Buffer1;

	/* geef de buffer die nu wordt gebruikt bij het vullen van de data */
	RGTDataBuffer &geefHuidigeVulBuffer() const;

	/* geef de buffer die nu wordt gebruikt bij het versturen van de data */
	RGTDataBuffer &geefHuidigeZendBuffer() const;

	/* wissel buffers voor data acquisitie */
	void wisselBuffer();

	RGTDataBuffer txRGTDataBuffer[2]; /* dubbele buffer */
	

};

#elif defined USE_STM32L432Nucleo32
#include <h/STM32L4xxNucleo32.h>
class ESEBoardController : public STM32L432Nucleo32
{
public:
	/*! @brief Constructor.
     * @param de PLL output (SYSCLK) frequentie in MHz. */
	explicit ESEBoardController(const UInt32 klok=80);

	/*! @brief set the sampling time in millisecs */
	void setSampleTime(const UInt16 );

	UInt16 getSampleTime() const;

	/*! @brief Start and stop the ADC and DAC.
	 * @note Schakelaar is a synonym for Switch.
	 */
	void startStopADC(const Schakelaar );
	void startStopDAC(const Schakelaar );

	/*! @brief not to be used by students */
	void zetDAC(const Spanning );
	Spanning leesADC();

	enum class RGTProcesSelektor
	{
		EersteOrdeProces=0b00,
		TweedeOrdeProces=0b10
	};

	void selekteerProces(const RGTProcesSelektor );

	static CountingSemaphore adcSem;

protected:

	/* The STM32L432 DAC is 12 bits large and has a reference voltage of 3.32 V */
	static constexpr auto MaxDAC = (1<<12)-1;
	static constexpr auto DACRef = 3.32f;

	/* Het STM32L432 board heeft een 3/5 verzwakkingfaktor ivm opamp op 5V.
	 * Deze moet na meting in software worden gekompenseerd. */
	float boardKompensatieFaktor = 1.0f;

	Schakelaar verbindingGemaakt = Schakelaar::Uit;
	static constexpr Schakelaar gebruikLCD = Schakelaar::Uit;

private:
	/* de bemonsteringtijd in milliseconden. */
	UInt16 bemonsteringTijd = 0;

	static constexpr auto RGTAdcKanaal = 0;
	static constexpr auto RGTDacKanaal = DAC_CHANNEL_1;
};

/*! @brief De basisklasse voor de regeltechniek microcontroller.
 * @brief The Base class for control systems microcontroller.
 * @note Nothing to be done or used here by ESE students. */
class RGTBoard : public ESEBoardController
{

protected:

	/*! @brief De constructor. */
	RGTBoard();

	/*! @brief Transmit the title, always 30 characters */
	void transmitTitle(const RGTTitel &);

	/*! @brief Stuur de board versie naar de desktop applikatie*/
	void stuurVersie();

	/* voor RGT practicum */

	/* Stuur de data gebuffered uit */
	void transmitData(const RGTData &);
	/* Stuur het restant van de buffer uit aan het einde van een sessie */
	void transmitData();

	void startStopADCenDAC(const Schakelaar );

	RGTKommando wachtOpDesktopCommando();

	/*! @brief deze funktie implementeert de open lus van het proces met argument als invoer .
	 * @param Het sample moment.
	 * @param Het setpoint.
	 * @param de proces input. */
	Spanning openlus(const RGTData::SampleMoment, const Spanning, const Spanning);

	RGTKommando::RegelaarKeuze controllerKeuze = RGTKommando::RegelaarKeuze::OpenLoop;
	float versterking=1.0f;

private:

	enum class BufferKeuze
	{
		Buffer1=0,
		Buffer2
	} vulBuffer = BufferKeuze::Buffer1;

	/* wissel buffers voor data acquisitie */
	void wisselBuffer();

#ifdef USE_STM32412G_DISCOVERY
	/* geef de buffer die nu wordt gebruikt bij het vullen van de data */
	RGTDataBuffer & geefHuidigeVulBuffer() const;

	/* geef de buffer die nu wordt gebruikt bij het versturen van de data */
	RGTDataBuffer &geefHuidigeZendBuffer() const;

	RGTDataBuffer txRGTDataBuffer[2]; /* dubbele buffer */

#elif defined USE_STM32L432Nucleo32

	/* geef de buffer die nu wordt gebruikt bij het vullen van de data */
	RGTDataBuffer & geefHuidigeVulBuffer() const;

	/* geef de buffer die nu wordt gebruikt bij het versturen van de data */
	RGTDataBuffer &geefHuidigeZendBuffer() const;

	RGTDataBuffer txRGTDataBuffer[2]; /* dubbele buffer */

#endif


};


#else
#error "(RGTBoard.h) Geen ondersteund bord gedefinieerd"
#endif

#endif
