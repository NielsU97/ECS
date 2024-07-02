/*!
@file
Demonstratie van de STM32F0308 Discovery met gebruik van een timer om de groene LED te laten knipperen.
@version $Rev: 3236 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/HAL/discoveryf0308HelloWorld/main.cpp $
$Id: main.cpp 3236 2018-12-01 13:17:01Z ewout $
************************************************************************/

#include <main.h>


STM32F0308DemoController::STM32F0308DemoController() : STM32F0308Discovery(48)
{

}

void STM32F0308DemoController::helloworld() const
{
	knipperBlauwLED(KnipperLEDStand::Middel);
	
	/* schakel de sleep-on-exit mode aan : de processor gaat na een interrupt automatisch terug naar sleep mode */
	/* zet het SOE bit in het system control register.
	 * Zie : "The definitive guide to the Cortex-M0" door Joseph Yiu.
	 * Bladzijde 207.
	 * ISBN 978-0-12-385477-3
	 * Een aan te raden boek om deze processor echt goed leren begrijpen. */
	SCB->SCR += (1<<1);
	
	do
	{
		/* ga naar Sleep mode : core en busklokken uit, timer is aktief en NVIC is aktief.
		 * Alleen tijdens de interrupt is stukje code aktief, maar na interrupt terug naar sleep mode. */
		__WFI(); /* Wait For Interrupt */
	} while (1==1);
}



int main(void)
{
	static STM32F0308DemoController demo;

	demo.helloworld();
	
}
