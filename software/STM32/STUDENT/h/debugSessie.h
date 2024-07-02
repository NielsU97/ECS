/******************************************************************************
 * Project        : ES2 Project 3 Debugproject
 * Copyright      : 2010-2015 - H. Arends en E.J Boks
 ******************************************************************************/
/* $Id: debugSessie.h 4014 2020-11-12 17:28:03Z ewout $                             */

#ifndef HANESE_DebugSessie_H
#define HANESE_DebugSessie_H

#include <algdef.h>

//#include "RGTTaak.h"

class DataField
{
public:

	DataField() = default;

	DataField(char const * const,
	          UInt32,
	          UInt32 );

	/*! @brief vergelijk twee datavelden met elkaar en geef oordeel of zij dezelfde inhoud hebben.
	 * @return de velden zijn gelijk (true) of niet (false) */
	bool operator == (const DataField &) const;

	/*! @brief vergelijk twee datavelden met elkaar en geef oordeel of zij dezelfde inhoud hebben.
	 * @return de velden zijn niet gelijk (true) of gelijk (false) */
	bool operator != (const DataField &) const;

	const char * giveName() const;

private:

	static constexpr auto NameSize=20;
	UInt32 dateOfBirth=0;
	char name[NameSize];
	UInt32 telephoneNumber=0;
};

#ifdef USE_STM32412G_DISCOVERY
#include <ESEBoardController.h>
/*! @class De STM32 Controller in de rol van DebugSessie controller */
class DebugController : public ESEBoardController
#elif defined USE_STM32L432Nucleo32
#include <STM32L4xxNucleo32.h>
/*! @class De STM32 Controller in de rol van DebugSessie controller */
class DebugController : public STM32L432Nucleo32
#else
#error "(debugSessie.h) Geen ondersteund bord gedefinieerd"
#endif
{
public:
	/*! @brief De constructor. Init hier de BKUP registers */
	DebugController();

	/*! @brief het testprogramma dat wordt uitgevoerd om de RTC en BKUP funkties te testen. */
	void debugSession();

protected:

	/*! @brief lees een Datafield waarde uit het BKUP register / Read a Datafield value from the BKUP register. */
	DataField read();

	/*! @brief schrijf een DataField naar het BKUP register / Write a DataField to the BKUP register. */
	void write(const DataField &);

private:


	/*! @brief lees een 32 bit waarde uit het BKUP register / Read a 32 bit value from the BKUP register.
   	 *  @param de BKUP register index (0..19)
	 * @return de 8 bit waarde die uit het BKUP register komt. */
	UInt32 readBKUP(const UInt32);

	/*! @brief schrijf een 32 bit waarde naar het BKUP register / Write a 32 bit value to the BKUP register.
 	 *  @param de BKUP register index (0..19)
 	 * @param de 8 bit waarde die geschreven wordt */
	void writeBKUP(const UInt32,
	               const UInt32);

	static constexpr auto rttBufferGrootte=64;
	char rttBuffer[rttBufferGrootte];
};




#endif
