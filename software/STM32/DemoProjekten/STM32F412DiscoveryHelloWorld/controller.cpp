/*!
@file
Implementatie van de c++ schil voor gebruik van de STM32412g Discovery kit.
@version $Rev: 3662 $
@author $Author: ewout $

@copyright Copyright 2017-2019 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$Id: controller.cpp 3662 2019-10-24 15:32:27Z ewout $
************************************************************************/

#include <controller.h>
#include <RTT/SEGGER_RTT.h>

DemoController::DemoController() : STM32412gDiscovery(96)
{
	SEGGER_RTT_ConfigUpBuffer(0, "RTT Buffer", rttBuffer,
	                          rttBufferGrootte, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
}

void DemoController::postOSInit()
{
	eepromInit();
}

void DemoController::rttMelding(const char *melding)
{
	if (false == rttBufferVol)
	{
		const auto lengte = strlen(melding);
		const auto geschreven = SEGGER_RTT_WriteSkipNoLock(0, melding, lengte);
		rttBufferVol = (lengte != geschreven);  /* als hij vol zit, dan stopt het */
	}
}

