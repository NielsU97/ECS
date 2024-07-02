/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek Taak klasse
 * Copyright      : 2010-2017 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: rtosTaak.h 3172 2018-11-16 09:27:14Z ewout $  
******************************************************************************/

#ifndef HANESE_rtosTaak_H
#define HANESE_rtosTaak_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <thread.hpp>
#include <queue.hpp>
#include <algdef.h>
#include <stdTaak.h>
#include <STM32L4xxNucleo32.h>


using namespace cpp_freertos;


class RTOSTask : public StdTaak
{
protected:

	/*! @brief constructor for RGTTaak.
	 * @param The name for the task.
	 * @param The Stack size of Cortex M3/4 UInt32 stack elements.
	 * @param The FreeRTOS priority of the task.
	 */
	RTOSTask(const std::string &,
	         const UInt16,
	         const TaakPrio,
	         STM32L432Nucleo32 & );

	STM32L432Nucleo32 &nucleo;
};

#endif
