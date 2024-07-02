/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek Taak klasse
 * Copyright      : 2010-2017 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: debugTaak.h 4029 2020-11-27 16:12:13Z ewout $  
******************************************************************************/

#ifndef HANESE_DebugTaak_H
#define HANESE_DebugTaak_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <thread.hpp>
#include <queue.hpp>

#ifdef DebugOpdracht
#include <debugSessie.h>
#include <rtosTaak.h>

class DebugTask : public RTOSTask
{
public:
	explicit DebugTask(DebugController &);

private:

	void Run();

	DebugController &controller;
};

#endif

#endif
