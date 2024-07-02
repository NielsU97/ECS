/*!
@file
Demonstratie van de STM32L432 Nucleo32 met gebruik van de Low Power Timer om de groene LED te laten knipperen.
@version $Rev: 3236 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/HAL/STM32L432Nucleo32HelloWorld/main.cpp $
$Id: main.cpp 3236 2018-12-01 13:17:01Z ewout $
************************************************************************/
#include <main.h>


STM32L432DemoController::STM32L432DemoController() : STM32L432Nucleo32(80)
{

}

void STM32L432DemoController::helloworld() const
{
	/* laad de LED knipperen vanuit de LPTimer1 (Low Power Timer) */
	blinkLED(BlinkSetting::Middle);
	
	/* schakel de deep sleep (bijna alles uit) en sleep-on-exit mode aan : de processor gaat na een interrupt automatisch terug naar sleep mode */
	/* zet het SOE bit in het system control register.
	 * Zie : "The definitive guide to ARM Cortex-M3 and ARM Cortex-M4" door Joseph Yiu
	 * bladzijde 295
	 * ISBN 978-0-12-408082-9
	 * Een aan te raden boek om deze processor echt goed te leren begrijpen. */
	SCB->SCR += (1<<2)+(1<<1);
	
	do
	{
		/* ga naar DeepSleep mode : core, systeemklokken,perifklokken en busklokken uit, timer is aktief (want draaitop 32,768 kHz crystal
		 * en NVIC aktief.
		 * Alleen tijdens de interrupt is stukje code aktief, maar na interrupt terug naar deep sleep mode. */
		__WFI(); /* Wait For Interrupt */
	} while (1==1);
}



int main(void)
{
	static STM32L432DemoController demo;

	demo.helloworld();
	
}
