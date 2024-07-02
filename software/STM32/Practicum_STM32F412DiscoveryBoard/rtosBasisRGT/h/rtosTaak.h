/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek Taak klasse
 * Copyright      : 2010-2017 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: rtosTaak.h 4070 2021-01-21 08:32:46Z ewout $  
******************************************************************************/

#ifndef HANESE_rtosTaak_H
#define HANESE_rtosTaak_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <thread.hpp>
#include <queue.hpp>
#include <algdef.h>
#include <ESEBoardController.h>
#include <stdTaak.h>


using namespace cpp_freertos;


class RTOSTask : public StdTaak
{
protected:

	/*! @brief constructor for RTOS Taak.
	 * @param The name for the task.
	 * @param The Stack size of Cortex M3/4 UInt32 stack elements.
	 * @param The FreeRTOS priority of the task.
	 * @param A reference to the used controller.
	 */
	RTOSTask(const std::string &,
	         const UInt16,
	         const TaakPrio,
	         ESEBoardController & );

	ESEBoardController &eseBoardController;
};

#endif
