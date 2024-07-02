/* $Id: main.cpp 3736 2020-01-06 15:10:03Z ewout $     */
/*************** Regeltechniek practicum *****************/
/*************** Code van de student *********************/
/*************** VUL HIER NAAM en STUDENTNUMMER in *******/
/*************** en verwijder de preprocessor error aanduiding */
//#error  "(student.cpp) Er is nog geen naam en studentnummer ingevuld ingevuld."   
/********  Naam :               ******/
/********  Studentnummer :      ******/

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

