/******************************************************************************
 * Project        : ES2 Project 3 - Fuzzy Control
 * File           : Fuzzy library
 * Copyright      : 2010-2011 - H. Arends en E.J Boks
 ******************************************************************************
@file 
RGT Controller voor PRJ3PRT

@version $Rev: 3290 $
@author $Author: ewout $ 
                                   
@copyright Copyright 2013-2016 Hogeschool van Arnhem en Nijmegen
         
$Id: RGTData.cpp 3290 2019-01-21 16:32:56Z ewout $
************************************************************************/

#include <RGTData.h>
#include <assert.h>

RGTKommando::RGTKommando(const Kommando cmd,
                         const Spanning setp,
                         const UInt16 aantalPunten,
	                     const UInt16 vertraging,
	                     const float versterking)
{
	assert(cmd < Kommando::Blok);

	(*this)[CmdIndex] = static_cast<UInt8>(cmd);
	(*this)[VersieIndex] = VERSION;

	schrijfIndex(SetPointIndex,setp);
	schrijfIndex(AantalPuntenIndex, aantalPunten);
	schrijfIndex(VertragingIndex,vertraging);
	schrijfIndex(VersterkingIndex,versterking);
}

RGTKommando::RGTKommando(const Kommando cmd,
                         const Spanning setp,
                         const UInt16 aantalPunten,
						 const UInt16 vertraging,
                         const float beginFreq,
                         const float amplitude,
                         const UInt8 aantalPerioden,
                         const float versterking)
{
	assert((cmd==Kommando::Cosinus) || (cmd==Kommando::Blok));

	(*this)[CmdIndex] = static_cast<UInt8>(cmd);
	(*this)[VersieIndex] = VERSION;
	(*this)[AantalPeriodenIndex] = aantalPerioden;

	schrijfIndex(SetPointIndex,setp);
	schrijfIndex(AantalPuntenIndex, aantalPunten);
	schrijfIndex(VertragingIndex,vertraging);
	schrijfIndex(BeginFreqIndex,beginFreq);
	schrijfIndex(AmplitudeIndex,amplitude);
	schrijfIndex(VersterkingIndex,versterking);
}


RGTKommando::RGTKommando(const PIDveld pw,
                         const PIDveld iw,
                         const PIDveld dw)
{
	(*this)[CmdIndex] = static_cast<UInt8>(Kommando::ZetPIDParameters);

	schrijfIndex(PwaardeIndex,pw);
	schrijfIndex(IwaardeIndex,iw);
	schrijfIndex(DwaardeIndex,dw);

	(*this)[VersieIndex] = VERSION;
}

RGTKommando::RGTKommando(const RGTKommando::Kommando cmd)
{
	(*this)[CmdIndex] = static_cast<UInt8>(cmd);
	(*this)[VersieIndex] = VERSION;
}

RGTKommando::RGTKommando(const RGTKommando::RegelaarKeuze regelaarKeuze)
{
	(*this)[CmdIndex] = static_cast<UInt8>(Kommando::ZetRegelaarKeuze);
	(*this)[RegelaarKeuzeIndex] = static_cast<UInt8>(regelaarKeuze);
	(*this)[VersieIndex] = VERSION;
}

RGTKommando::RGTKommando(const ProcesKeuze procesKeuze)
{
	(*this)[CmdIndex] = static_cast<UInt8>(Kommando::ZetProcesKeuze);
	(*this)[ProcesKeuzeIndex] = static_cast<UInt8>(procesKeuze);
	(*this)[VersieIndex] = VERSION;
}


RGTKommando::Kommando RGTKommando::geefCommando() const
{
	const Kommando kommando = static_cast<Kommando>((*this)[CmdIndex]);
	return(kommando);
}

RGTKommando::RegelaarKeuze RGTKommando::geefRegelaarKeuze() const
{
	const auto keuze = static_cast<RegelaarKeuze >((*this)[RegelaarKeuzeIndex]);

	assert(keuze <= RegelaarKeuze::Fuzzy);
	return(keuze);
}

RGTKommando::ProcesKeuze RGTKommando::geefProcesKeuze() const
{
	const auto keuze = static_cast<ProcesKeuze >((*this)[ProcesKeuzeIndex]);
	return(keuze);
}

UInt8 RGTKommando::geefVersie() const
{
	const auto inkomendeVersie = (*this)[VersieIndex];
	return(inkomendeVersie);
}

FoutCode RGTKommando::vergelijkVersies() const
{
	const auto inkomendeVersie = geefVersie();
	const bool gelijk = (RGTKommando::VERSION == inkomendeVersie);

	return((true==gelijk) ? FoutCode::Ok : FoutCode::Fout);
}

UInt16 RGTKommando::geefAantalPunten() const
{
	const auto uit = leesIndexU16(AantalPuntenIndex);
	return(uit);
}

Spanning RGTKommando::geefSetPoint() const
{
	const auto uit = leesIndexFloat(SetPointIndex);
	return(uit);
}

UInt16 RGTKommando::geefVertraging() const
{
	const auto uit = leesIndexU16(VertragingIndex);
	return(uit);
}

PIDveld RGTKommando::geefPwaarde() const
{
	const auto uit = leesIndexFloat(PwaardeIndex);
	return(uit);
}

PIDveld RGTKommando::geefIwaarde() const
{
	const auto uit = leesIndexFloat(IwaardeIndex);
	return(uit);
}

PIDveld RGTKommando::geefDwaarde() const
{
	const auto uit = leesIndexFloat(DwaardeIndex);
	return(uit);
}


Spanning RGTKommando::geefVersterking() const
{
	const auto uit = leesIndexFloat(VersterkingIndex);
	return(uit);
}

float RGTKommando::geefStartFreq() const
{
	const auto uit = leesIndexFloat(BeginFreqIndex);
	return(uit);
}

float RGTKommando::geefAmplitude() const
{
	const auto uit = leesIndexFloat(AmplitudeIndex);
	return(uit);
}

UInt8 RGTKommando::geefAantalPerioden() const
{
	const auto aantalPerioden = (*this)[AantalPeriodenIndex];
	return(aantalPerioden);
}


UInt16 RGTKommando::leesIndexU16(const UInt32 index) const
{
	assert(index < grootte);

	UInt16 uit;
	auto const * const bron = &((*this)[index]);
	auto * bestemming = reinterpret_cast<UInt8 *>(&uit);
	memcpy(bestemming,bron,sizeof(decltype(uit)));
	return(uit);
}

void RGTKommando::schrijfIndex(const UInt32 index, const UInt16 waarde)
{
	assert(index < grootte);

	auto const * bron = reinterpret_cast<const UInt8 *>(&waarde);
	auto * bestemming = &((*this)[index]);
	memcpy(bestemming,bron,sizeof(decltype(waarde)));
}

float RGTKommando::leesIndexFloat(const UInt32 index) const
{
	assert(index < grootte);

	float uit;
	auto const * const bron = &((*this)[index]);
	auto * bestemming = reinterpret_cast<UInt8 *>(&uit);
	memcpy(bestemming,bron,sizeof(decltype(uit)));
	return(uit);
}

void RGTKommando::schrijfIndex( const UInt32 index,const float waarde)
{
	assert(index < grootte);

	auto const * bron = reinterpret_cast<const UInt8 *>(&waarde);
	auto * bestemming = &((*this)[index]);
	memcpy(bestemming,bron,sizeof(decltype(waarde)));
}



RGTTitel::RGTTitel(char const *const titel) : FixedDataPakket(reinterpret_cast<const UInt8 *>(titel))
{
#ifndef NDEBUG
	const auto lengte = strlen(titel);
	assert(lengte <= grootte);
#endif
	/* forceer een newline op de laatste plaats */
	data[grootte-1]='\n';
}

char const *const RGTTitel::geefTitel() const
{
	return(reinterpret_cast<char const *>(data));
}


RGTVolledigData::RGTVolledigData(const SampleMoment nm,
                 const Spanning mv,
                 const Spanning rv,
                 const Spanning cv) : n(nm),measurementValue(mv),
                                   referenceValue(rv),
                                   controlValue(cv)
{

};


/** kompakte versie */
RGTKompaktData::RGTKompaktData(const SampleMoment nm,
                               const Spanning mv,
                               const Spanning rv,
                               const Spanning cv) : n(nm),measurementValue(konverteerSpanning(mv)),
                                                    referenceValue(konverteerSpanning(rv)),
                                                    controlValue(konverteerSpanning(cv))
{

}

Spanning RGTKompaktData::geefMeting() const
{
	const auto uit = konverteerFixedPoint(measurementValue);
	return(uit);
}

Spanning RGTKompaktData::geefReferentie() const
{
	const auto uit = konverteerFixedPoint(referenceValue);
	return(uit);
}

Spanning RGTKompaktData::geefSetpoint() const
{
	const auto uit = konverteerFixedPoint(controlValue);
	return(uit);
}

UInt16 RGTKompaktData::konverteerSpanning(const Spanning &u)
{
	static constexpr UInt8 geheelGrens = 0b00001111;
	const auto geheel = (geheelGrens & static_cast<UInt8>(u));
	const auto fraktie = static_cast<UInt16>((u-geheel)*fraktieBereik);

	const UInt16 uit = (geheel<<12)+fraktie;

	return(uit);
}

Spanning RGTKompaktData::konverteerFixedPoint(const UInt16 &fpw)
{
	const UInt16 geheel = fpw>>12;
	const UInt16 fraktie = (fraktieBereik & fpw);
	const Spanning u = static_cast<Spanning >(geheel) + static_cast<Spanning >(fraktie)/fraktieBereik;
	return(u);
};

FoutCode RGTKompaktData::doeZelftest()
{
	static constexpr Spanning uTest = 3.45678f;

	const auto fpTest = konverteerSpanning(uTest);
	const auto uUitkomst = konverteerFixedPoint(fpTest);

	static constexpr auto nauwkeurigheid = 1.0f/4096;
	const auto residu = fabs(uTest-uUitkomst);
	const auto retkode = ((residu < nauwkeurigheid) ? FoutCode::Ok : FoutCode::Fout);
	return(retkode);
}






