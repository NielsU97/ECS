/*!
@file
Demonstratie "Hello World"van CMake/CLion voor gebruik van de STM32412g Discovery kit.
@version $Rev: 3662 $
@author $Author: ewout $

@copyright Copyright 2017-2019 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$Id: main.cpp 3662 2019-10-24 15:32:27Z ewout $
************************************************************************/
#include "main.h"
#include <controller.h>

int main(void)
{
	/* initialiseer de controller. Deze zorgt voor alle configuratie akties. */
	static DemoController controller;

	/* -3- Toggle IO in an infinite loop */
	ALTIJD
	{
		static const STM32412gDiscovery::LEDKleur kleuren[] =
			{
				STM32412gDiscovery::LEDKleur::Green,
				STM32412gDiscovery::LEDKleur::Orange,
				STM32412gDiscovery::LEDKleur::Red,
				STM32412gDiscovery::LEDKleur::Blue
			};
		
		static const char *kleurNamen[] =
			{
				"Groen\n","Oranje\n","Rood\n","Blauw\n"
			};
		
		for (auto kleur : kleuren)
		{
			controller.setLED(kleur,Schakelaar::Om);
			controller.rttMelding(kleurNamen[static_cast<Teller>(kleur)]);
			/* Insert delay 250 ms */
			HAL_Delay(1250);
		}
	}
}
