/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek klasse
 * Copyright      : 2010 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: RGTData.h 3683 2019-11-05 10:53:25Z ewout $  
******************************************************************************/

#ifndef HANESE_REGELTECHNIEK_RGTData_H
#define HANESE_REGELTECHNIEK_RGTData_H

#include <algdef.h>
#include <dataPakket.h>

using Spanning = float;
using PIDveld = float;

/*! @class Dit is een container voor een desktop opdracht voor het RGT board. */
static constexpr auto RGTKommandoGrootte = 4*sizeof(UInt8)+2*sizeof(UInt16)+2*sizeof(Spanning)+3*sizeof(PIDveld);

class RGTKommando : public FixedDataPakket<UInt8,RGTKommandoGrootte>
{
public:

	static constexpr auto VERSION = '4';

	/*! @brief Constructor voor ontvangst */
	RGTKommando() = default;

	enum class Kommando : UInt8
	{
		Stap=0,     /* zes signalen */
		Helling,
		Impuls,

		Blok,
		Cosinus,

		ZetRegelaarKeuze,
		ZetProcesKeuze,

		ZetOnOffParameters,
		ZetFuzzyParameters,
		ZetPIDParameters,    /* zet parameters */

		GeefVersie,
		GaSlapen,

		AntwoordNaarDesktop,
		Leeg,
		Laatste
	};

	/*! @brief Constructor voor keuze van een signaal : stap,impuls,helling of blok
	 *
	 * @param cmd : Het commando.
	 * @param sp  : Het setpoint
	 * @param Het aantal datapunten.
	 * @param de startvertraging
	 * @param de versterkingfaktor.
	 */
	RGTKommando(const Kommando cmd,
	            const Spanning setp,
	            const UInt16 ap,
	            const UInt16,
	            const float );

	/*! @brief Constructor voor keuze van een signaal : cosinus en cosinus sweep.
	 * @param cmd : Het commando.
	 * @param sp  : Het setpoint
	 * @param Het aantal datapunten.
	 * @param de startvertraging
	 * @param de frequentie.
	 * @param de amplitude van de cosinus
	 * @param Het aantal perioden in de cosinus.
	 * @param de versterkingfaktor.
	 */
	explicit RGTKommando(const Kommando cmd,
	                     const Spanning setp,
	                     const UInt16,
	                     const UInt16,
	                     const float,
	                     const float,
	                     const UInt8,
	                     const float);

	/*! @brief Constructor voor verzending van een kommando naar desktop :
	 *
	 * @param cmd : Het Kommando. 	 */
	explicit RGTKommando(const Kommando cmd);

	/*! @brief Constructor voor keuze van PID en verzending van PID instellingen
	 *
	 * @param cmd : Het commando.
	 * @param sp  : Het setpoint
	 * @param v  : De versie.
	 */
	RGTKommando(const PIDveld pw,
	            const PIDveld iw,
	            const PIDveld dw);


	enum class RegelaarKeuze : UInt8
	{
		OpenLoop,
		OnOff,
		PID,
		Fuzzy
	};

	/*! @brief Een kommando om de keuze voor de regelaar door te geven. */
	explicit RGTKommando(const RegelaarKeuze);

	enum class ProcesKeuze : UInt8
	{
		EersteOrde,
		TweedeOrde,
		Digitaal
	};

	explicit RGTKommando(const ProcesKeuze );

	Kommando geefCommando() const;

	RegelaarKeuze geefRegelaarKeuze() const;
	ProcesKeuze geefProcesKeuze() const;
	UInt8 geefVersie() const;

	Spanning geefSetPoint() const;
	UInt16 geefVertraging() const;

	PIDveld geefPwaarde() const;
	PIDveld geefIwaarde() const;
	PIDveld geefDwaarde() const;

	Spanning geefVersterking() const;

	UInt16 geefAantalPunten() const;

	float geefStartFreq() const;
	float geefAmplitude() const;
	UInt8 geefAantalPerioden() const;

	/* vergelijk de inkomende versie met de hier gecompileerde versie */
	FoutCode vergelijkVersies() const;

private:

	UInt16 leesIndexU16(const UInt32 index) const;
	void schrijfIndex(const UInt32, const UInt16);

	float leesIndexFloat(const UInt32 index) const;
	void schrijfIndex(const UInt32, const float);

	static constexpr auto CmdIndex=0;
	static constexpr auto VersieIndex  = CmdIndex + sizeof(UInt8);
	static constexpr auto AantalPeriodenIndex = VersieIndex+sizeof(UInt8);
	static constexpr auto ReserveIndex = AantalPeriodenIndex+sizeof(UInt8);

	static constexpr auto AantalPuntenIndex = ReserveIndex+sizeof(UInt8);
	static constexpr auto RegelaarKeuzeIndex = AantalPuntenIndex;
	static constexpr auto ProcesKeuzeIndex = RegelaarKeuzeIndex;

	static constexpr auto VertragingIndex = AantalPuntenIndex + sizeof(UInt16);

	static constexpr auto SetPointIndex= VertragingIndex + sizeof(UInt16);

	static constexpr auto PwaardeIndex = SetPointIndex+sizeof(Spanning);
	static constexpr auto BeginFreqIndex = PwaardeIndex;

	static constexpr auto IwaardeIndex = PwaardeIndex+sizeof(PIDveld);
	static constexpr auto AmplitudeIndex = IwaardeIndex;

	static constexpr auto DwaardeIndex = IwaardeIndex+sizeof(PIDveld);

	/* proces uitvoer versterking faktor */
	static constexpr auto VersterkingIndex =  DwaardeIndex+sizeof(PIDveld);

};

static constexpr auto TitelGrootte = 30;
class RGTTitel : public FixedDataPakket<UInt8,TitelGrootte>
{
public:
	/*! @brief Constructor voor ontvangst */
	RGTTitel() = default;

	explicit RGTTitel(char const * const );

	char const * const geefTitel() const;

};

/*! @class Dit is een container met floating point voor regeltechniek data */
class RGTVolledigData
{
public:

	/*! @brief voor ontvangst. */
	RGTVolledigData() = default;


	using SampleMoment = UInt32;

	/*! @brief Constructor voor RGTData.
	 * @param n : Het samplemoment.
	 * @param mv  : de meetwaarde.
	 * @param rv  : de regelwaarde (setpoint).
	 * @param cv  : de controle waarde  (proces input).
	 */
	explicit RGTVolledigData(const SampleMoment,
	                         const Spanning mv,
	                         const Spanning rv,
	                         const Spanning cv);


	SampleMoment n;
	UInt32 reserveWaarde=0;
	Spanning measurementValue;
	Spanning referenceValue;
	Spanning controlValue;

	/* payload bestaat uit : 2 long (4 bytes) = 8bytes  + 3 floats (4 bytes) = 12 bytes = 24 bytes */

};

/*! @class Dit is een container met floating point voor regeltechniek data */
class RGTKompaktData
{
public:

	/*! @brief voor ontvangst. */
	RGTKompaktData() = default;

	using SampleMoment = UInt16;

	/*! @brief Constructor voor RGTData.
	 * @param n : Het samplemoment.
	 * @param mv  : de meetwaarde.
	 * @param rv  : de regelwaarde (setpoint).
	 * @param cv  : de controle waarde  (proces input).
	 */
	explicit RGTKompaktData(const SampleMoment,
	                        const Spanning mv,
	                        const Spanning rv,
	                        const Spanning cv);

	Spanning geefMeting() const;
	Spanning geefReferentie() const;
	Spanning geefSetpoint() const;

	FoutCode doeZelftest();

	SampleMoment n;

private:

	static UInt16 konverteerSpanning(const Spanning &);
	static Spanning konverteerFixedPoint(const UInt16 &);

	/* formaat = Q4.12 , dit voldoet voor de STM32L432 ADC en DAC.
	 * De STM32F412 heeft een 24 bit ADC en 16 bit DAC, gebruik deze klasse daar voor niet. */
	UInt16 measurementValue;
	UInt16 referenceValue;
	UInt16 controlValue;

	/* payload bestaat uit : 4 unsigned short ints (2 bytes) = 8 bytes */

	/* Q4.12 : 12 bits = 3 nibbles van 0xf */
	static constexpr UInt16 fraktieBereik = 0xfff;

};

static constexpr UInt32 RGTDataBufferGrootte=10;

template<typename ttype>
class RGTProtoDataBuffer : public VerzendOntvangBuffer<UInt8,RGTDataBufferGrootte*sizeof(ttype)>
{
public:

	using RGTVZBuffer = VerzendOntvangBuffer<UInt8,RGTDataBufferGrootte*sizeof(ttype)> ;

	RGTProtoDataBuffer() = default;

	/*! @brief vind een object in de databuffer */
	ttype & operator [] (const UInt32 index)
	{
		const auto plek = index*sizeof(ttype);
		auto & dref = reinterpret_cast<ttype &>(RGTVZBuffer::operator[](plek));
		return(dref);
	};

	/* buf management */
	/*! @brief laad data in de buffer en verhoog de bufferteller */
	bool laadBuffer(const ttype &veld)
	{
		assert(false == isBufferVol());

		(*this).operator [] (bufTeller++) = veld;

		return(isBufferVol());
	};

	/* haal een waarde uit de buffer */
	bool haalUitBuffer(ttype& veld)
	{
		assert(false == isBufferVol());

		veld = (*this).operator [] (bufTeller++);

		return(isBufferVol());
	};

	/* geef aan of de buffer vol is */
	bool bevatBufferData() const
	{
		return(0 != bufTeller);
	};

	/* geef aan of de buffer vol is */
	bool isBufferVol() const
	{
		return(bufTeller == RGTDataBufferGrootte);
	};

	/* zet de bufferteller naar nul */
	void resetBuffer()
	{
		bufTeller=0;
		RGTVZBuffer::reset();
	};

private:
	UInt32 bufTeller=0;
};

using RGTVolledigDataBuffer = RGTProtoDataBuffer<RGTVolledigData>;
using RGTKompaktDataBuffer = RGTProtoDataBuffer<RGTKompaktData>;

#ifdef USE_STM32412G_DISCOVERY
	using RGTData = RGTVolledigData;
	using RGTDataBuffer = RGTVolledigDataBuffer;
#elif defined USE_STM32L432Nucleo32
	using RGTData = RGTKompaktData;
	using RGTDataBuffer = RGTKompaktDataBuffer;
#endif

#endif
