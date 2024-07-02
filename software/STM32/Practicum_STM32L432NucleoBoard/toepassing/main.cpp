/******************************************************************************
@file
main entry point for PRJ3PRT voor PRJ3PRT

@version $Rev: 3999 $
@author $Author: ewout $

@copyright Copyright 2013-2020Hogeschool van Arnhem en Nijmegen

$Id: main.cpp 3999 2020-10-16 14:48:51Z ewout $
************************************************************************/

//#error  "(main.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(main.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :               ******/
/********  Studentnummer :               ******/

#include <main.h>
#if defined(DebugOpdracht)
#include <debugTaak.h>
#elif (defined(InputResponsieOpdracht) || defined(PIDControllerOpdracht))
#include <RGTTaak.h>
#elif (defined(FuzzyOpdracht))
#include <RGTTaak.h>
#include <fuzzyController.h>

#else
#error "Geen opdracht gedefinieerd in CMakeLists.txt"
#endif

int main (void)
{
#if defined(DebugOpdracht)
	static DebugController debugController;
	static DebugTask debugTaak(debugController);
#elif defined(InputResponsieOpdracht)
	static OpenLoopTask olTaak;
#elif defined(PIDControllerOpdracht)
	static PIDTaak pidTaak;
#elif (defined(FuzzyOpdracht))
	static FuzzyTaak fuzzyTaak;
#endif

#if ! (defined(DebugOpdracht))
	static LedBlinkTask ledBlinkTask;
#endif

    Thread::StartScheduler();

    StopHier();  /* hier mogen wij NIET komen */

    return 0;
}

