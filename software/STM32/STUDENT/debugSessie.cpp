/******************************************************************************
@file
Debug sessie voor PRJ3PRT

@version $Rev: 4029 $
@author $Author: ewout $

@copyright Copyright 2013-2020 Opleiding Embedded Systems Engineering, Hogeschool van Arnhem en Nijmegen

$Id: debugSessie.cpp 4029 2020-11-27 16:12:13Z ewout $
************************************************************************/

//#error  "(debugSessie.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(debugSessie.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :    Niels Urgert           ******/
/********  Studentnummer :    654746                 ******/

#include "h/debugSessie.h"
#include <cmsis_os.h>
#include <RTT/SEGGER_RTT.h>
#ifdef USE_STM32412G_DISCOVERY
#include <GUI.h>
#endif
void DebugController::writeBKUP(const UInt32 index,
                                const UInt32 value)
{
    HAL_PWR_EnableBkUpReg();

    RTC_HandleTypeDef RtcHandle;
    RtcHandle.Instance = RTC;
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&RtcHandle, index, value);
    HAL_PWR_DisableBkUpAccess();

}

UInt32 DebugController::readBKUP(const UInt32 index)
{
    RTC_HandleTypeDef RtcHandle;
    RtcHandle.Instance = RTC;
    return HAL_RTCEx_BKUPRead(&RtcHandle, index);

}

void DebugController::write(const DataField &field)
{
    const auto grootte = sizeof(DataField);
    const auto aantal = grootte/ sizeof(UInt32);

    auto *ptr = (UInt32 *)&field;

    for (unsigned i =0; i <aantal; i++)
    {
        writeBKUP(i, *(ptr++));
    }
}

DataField DebugController::read()
{
    DataField data;

    const auto grootte = sizeof(DataField);
    const auto aantal = grootte/ sizeof(UInt32);

    auto *ptr = (UInt32 *)&data;

    for (unsigned i =0; i <aantal; i++)
    {
        *(ptr++) = readBKUP(i);
    }

    return(data);
}

/*********** Beste studenten, hieronder hoeft niets te worden veranderd.
 *********** Dear studentes, nothing needs to be altered from here.
*/

#ifdef USE_STM32412G_DISCOVERY
DebugController::DebugController() : ESEBoardController(96)
{
	SEGGER_RTT_ConfigUpBuffer(0, "RTT Buffer", rttBuffer,
	                          rttBufferGrootte, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
}
#elif defined USE_STM32L432Nucleo32

DebugController::DebugController() : STM32L432Nucleo32(80)
{
	SEGGER_RTT_ConfigUpBuffer(0, "RTT Buffer", rttBuffer,
	                          rttBufferGrootte,
	                          SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
}


#else
#error "(debugSessie.cpp) Geen ondersteund bord gedefinieerd"
#endif


void DebugController::debugSession()
{
	UInt32 attempts=9;

	do
	{
		/* read data from BKUP */
		const auto data(read());

#ifdef InterfaceTaalNederlands
		static char const * const teststring = "ESE is echt geweldig!";
#else
		static char const * const teststring = "ESE is really cool!";
#endif
		/* The real data */
		const DataField echteData(teststring,200669,1234567);

#ifdef USE_STM32412G_DISCOVERY
		GUI_SetFont(&GUI_Font16_1);
		GUI_Clear();
#endif
		/* Controleer of de data uit BKUP overeenkomt met de echte data/
		 * Confirm that the data from BKUP corresponds to the real data. */
		if (data != echteData)
		{
			setLED(LEDKleur::Green, Schakelaar::Uit);
			setLED(LEDKleur::Orange, Schakelaar::Aan);

			/* Data that was read from backup was wrong! */
			/* Write the good data to the backup register.  */
#ifdef InterfaceTaalNederlands
			static const char *melding = "De string kwam NIET overeen met de inhoud van het BKUP register.\n";
#else
			static const char *melding = "The string did NOT match the BKUP register contents.\n";
#endif
			SEGGER_RTT_WriteString(0,melding);
#ifdef USE_STM32412G_DISCOVERY
			GUI_SetColor(GUI_RED);
			GUI_DispStringHCenterAt(melding,120,100);
#endif
			write(echteData);
		}
		else
		{

#ifdef InterfaceTaalNederlands
			setLED(LEDKleur::Green, Schakelaar::Aan);
			setLED(LEDKleur::Orange, Schakelaar::Uit);

			static const char *rttMelding = "De string kwam WEL overeen met de inhoud van het BKUP register.\nDe inhoud was :";
#else
			setLED(LEDKleur::Green, Switch::Aan);
			setLED(LEDKleur::Orange, Switch::Uit);

			static const char *rttMelding = "The string DID match the BKUP register contents.\nThe contents were:";
#endif
			SEGGER_RTT_WriteString(0, rttMelding);

#ifdef USE_STM32412G_DISCOVERY
#ifdef InterfaceTaalNederlands
			static const char *guiMelding1 = "De string kwam WEL overeen";
			static const char *guiMelding2 = "met het BKUP register!";
#else
			static const char *guiMelding1 = "De string DID match";
			static const char *guiMelding2 = "the BKUP register contents!";
#endif
			GUI_SetColor(GUI_BLUE);
			GUI_DispStringHCenterAt(guiMelding1, 120, 100);
			GUI_DispStringHCenterAt(guiMelding2, 120, 116);
#endif

			SEGGER_RTT_WriteString(0, data.giveName());
			SEGGER_RTT_WriteString(0, "\n");
		}

		osDelay(2000); /* wait in sleep for 500 milliseconds  */
		setLED(LEDKleur::Blue, Schakelaar::Om);
	} while (0 != (--attempts));

	setLED(LEDKleur::AllColours, Schakelaar::Uit);

	setLED(LEDKleur::Red, Schakelaar::Aan);

	osDelay(1000);
	coreReset(); /* reset yourself. */

}



DataField::DataField(char const * const nPtr,
                     UInt32 gb,
                     UInt32 tf) : dateOfBirth(gb),telephoneNumber(tf)
{
	assert(nullptr != nPtr);
	memcpy(name,nPtr,NameSize);
}


bool DataField::operator == (const DataField &rhs) const
{
	const bool strgelijk = (0 == memcmp(name,rhs.name,NameSize));

	return((strgelijk &&
	        (dateOfBirth == rhs.dateOfBirth) &&
	        (telephoneNumber == rhs.telephoneNumber)));
}

bool DataField::operator != (const DataField &rhs) const
{
	const bool conditie = !((*this).operator == (rhs));
	return(conditie);
}

const char *DataField::giveName() const
{
	auto * ptr = name;
	return(ptr);
}


