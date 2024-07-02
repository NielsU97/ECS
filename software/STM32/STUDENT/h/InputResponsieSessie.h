/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek klasse
 * Copyright      : 2010 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: InputResponsieSessie.h 4009 2020-11-12 14:13:31Z ewout $  
******************************************************************************/

#ifndef HANESE_REGELTECHNIEK_Proces_H
#define HANESE_REGELTECHNIEK_Proces_H

#include <RGTBoard.h>
#include "aanUitControllerSessie.h"

class PIDController;    /* C++ voorwaartse deklaratie/forward declaration */
class FuzzyController;  /* C++ voorwaartse deklaratie/forward declaration */
class StdTaak;          /* C++ voorwaartse deklaratie/forward declaration */

/*! @class De basisklasse voor de StudentInputResponsie ******/
class RGTProces : public RGTBoard
{

public:
	/*! @brief Start een open loop proces */
	explicit RGTProces(StdTaak &);

	/*! @brief start een proces met PID en Aan/Uit Controllers aanwezig */
	explicit RGTProces(StdTaak &,
	                   PIDController * const,
	                   AanUitController * const);

	/*! @brief start een proces met Fuzzy en Aan/Uit Controllers aanwezig */
	explicit RGTProces(StdTaak &,
	                   FuzzyController * const,
	                   AanUitController * const);

	virtual ~RGTProces() = default;

	/*! @brief Met deze funktie wacht de controller  op commandos vanaf de desktop.
	 * @param Use the LCD (true) or the PC applikatie (false)
	 * @param indefinite = true --> endless loop, otherwise signle run */
	virtual void mainLoop(const Switch gebruikLCD,
	                      const bool indefinite);

	/*! @brief geef het aantal meetpunten */
	UInt16 getNumberOfPoints() const;

	/*! @brief Bij het uitvoeren van een responsie, zet de inschakel vertraging */
	void setStartDelay(const RGTData::SampleMoment);

	/*! @brief Geef de ingestelde vertraging */
	RGTData::SampleMoment getStartDelay() const;

	/*! @brief zet het instelpunt.
	 * @note bij een cosinus of blokgolf wordt het instelpunt/2 genomen als basis.
	 * When using square wave or cosine, this/2 is taken as basis for the wave. */
	void setSetPoint(const Spanning amp);

	/*! @brief geef het instelpunt */
	Spanning getSetPoint() const;

	virtual void reset();

	void setSampleTime();

	Schakelaar geefBKUPGebruikLCDKeuze();
	void zetBKUPGebruikLCDKeuze(const Schakelaar);

	RGTKommando::Kommando geefBKUPSignaalKeuze();
	void zetBKUPSignaalKeuze(const RGTKommando::Kommando);

	RGTProcesSelektor geefBKUPProcesKeuze();
	void zetBKUPProcesKeuze(const RGTProcesSelektor proces);

	RGTKommando::RegelaarKeuze geefBKUPRegelaarKeuze();
	void zetBKUPRegelaarKeuze(const RGTKommando::RegelaarKeuze );

	/*! @brief bewaar en vraag op de PID waarden. */
	void geefBKUPPIDWaarden(WFT &,WFT &, WFT &);
	void zetBKUPPIDWaarden(const WFT ,const WFT ,const WFT );

protected:

	/* Note for Non Dutch speaking students :
	 * Spanning = voltage */

	/*! @brief De impulsresponsiefunktie / Impulse Signal generation
     * @param het samplemoment n.
     * @return de waarde in V van de funktie op samplemoment n /
     * the value of the function in V at sample moment n */
	Spanning impulseInputSignal(const RGTData::SampleMoment) const;

	/*! @brief De stapresponsiefunktie / Step Signal generation
	 * @param het samplemoment n.
	 * @return de waarde van de funktie op samplemoment n  /
     * the value of the function in V at sample moment n*/
	Spanning stepInputSignal(const RGTData::SampleMoment) const;

	/*! @brief De hellingresponsiefunktie / Ramp Signal generation
	 * @param het samplemoment n.
	 * @return de waarde van de funktie op samplemoment n  /
     * the value of the function in V at sample moment n*/
	Spanning rampInputSignal(const RGTData::SampleMoment) const;

	/*! @brief De blokgolfresponsiefunktie / Square Wave Signal generation
	 * @param het samplemoment n.
	 * @return de waarde van de funktie op samplemoment n  /
     * the value of the function in V at sample moment n*/
	Spanning squareWaveInputSignal(const RGTData::SampleMoment);

	/*! @brief De cosinusresponsiefunktie / Cosine Signal generation
	 * @param het samplemoment n.
	 * @return de waarde van de funktie op samplemoment n  /
     * the value of the function in V at sample moment n*/
	Spanning cosineInputSignal(const RGTData::SampleMoment);

	/* \/ Do NOT change anything from here \/ */

	/*! @brief zet de ingangspanning in het proces op nul */
	void bereidVoorMeting();

	void bereidVoorPeriodiekeFunktie();

private:

#ifdef USE_STM32412G_DISCOVERY
	void guiToonDesktopStartMededeling();
	void guiToonDesktopVerbondenMededeling();
	void guiToonDesktopStatus(const Schakelaar);
	RGTProcesSelektor guiKiesProces();
	RGTKommando::Kommando guiKiesSignaalVorm();
	RGTKommando::RegelaarKeuze guiKiesRegelaar();
#endif

	/* stuurt negeer patroon terug naar de host */
	void negeer();

	void voerUitResponsie(RGTKommando::Kommando kommando);

	Spanning maakInput(const RGTKommando::Kommando kommando,
	                   const RGTData::SampleMoment);


	UInt16 aantalMeetPunten=1000;
	RGTData::SampleMoment vertraging = 0;

	Spanning setpoint=2.5f;
	float startFrequentie=1.0f, amplitude= 100.0f,freqStapper=1.0f;
	UInt8 numberOfPeriods = 1;

	float cosArgBasis = 0.0f;
	UInt32 cosStapGrootte =  1,cosStapper=0;

	/* Deze waarden worden berekend uit de GUI input, gebruik deze bij
	 * de constructie van de blokgolf.
	 * These values are calculated from the GUI input, use them when
	 * constructing the values for the square wave. */
	UInt32 pointsPerPeriod = 2,pointsPerHalfPeriod=1;

	float cosArg = 0.0f;

	PIDController * pidController = nullptr;
	FuzzyController *fuzzyController = nullptr;
	AanUitController *aanUitController = nullptr;

	StdTaak &mijnTaak;

	static constexpr auto GebruikLCDBKUPVeld = 3;
	static constexpr auto SignaalKeuzeBKUPVeld = GebruikLCDBKUPVeld+1;
	static constexpr auto ProcesKeuzeBKUPVeld = SignaalKeuzeBKUPVeld+1;
	static constexpr auto ProcesRegelaarBKUPVeld = ProcesKeuzeBKUPVeld+1;
	static constexpr auto RegelaarPID_P_BKUPVeld = ProcesRegelaarBKUPVeld+1;
	static constexpr auto RegelaarPID_I_BKUPVeld = RegelaarPID_P_BKUPVeld+1;
	static constexpr auto RegelaarPID_D_BKUPVeld = RegelaarPID_I_BKUPVeld+1;

	static const char *practicumtekst;
};



#endif
