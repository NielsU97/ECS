/******************************************************************************
@file
PID Controller voor PRJ3PRT

@version $Rev: 4009 $
@author $Author: ewout $

@copyright Copyright 2013-2020 Hogeschool van Arnhem en Nijmegen

$Id: aanUitControllerSessie.cpp 4009 2020-11-12 14:13:31Z ewout $
************************************************************************/

//#error  "(AanUitController.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(AanUitController.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :    Niels Urgert           ******/
/********  Studentnummer :    654746                 ******/

#include <math.h>
#include <string.h>
#include <assert.h>
#include <aanUitControllerSessie.h>
#include <cmsis_os.h>

void AanUitController::zetEigenschap(const AanUitController::Eigenschap e,
                                     const Spanning param)
{
	eigenschap = e;

	if (Eigenschap::Standaard == eigenschap)
		dzWaarde=minDzWaarde=0.0f;
	else
	{
		dzWaarde = param;
		minDzWaarde= -1.0f*param;
	}
}

Spanning AanUitController::aanUitFunktie(const Spanning sp,
                                         const Spanning mw)
{
	const auto verschil = sp-mw;
	auto resultaat = 0.0f;

	switch(eigenschap)
	{
		case Eigenschap::Standaard:
		{
			resultaat = (verschil >= 0) ? dacUpperLimit : dacLowerLimit;
		}
			break;

		case Eigenschap::DodeZone:
		{
			resultaat = (verschil >= dzWaarde) ? dacUpperLimit :
			            ((verschil < minDzWaarde) ? dacLowerLimit : 0.0f);
		}
			break;

		case Eigenschap::Hysterese:
		{
			switch (hysterese)
			{
				case HysteresePad::Laag:
				{
					if (verschil >= dzWaarde)
					{
						hysterese = HysteresePad::Hoog;
						resultaat = dacUpperLimit;
					}
					else
						resultaat = dacLowerLimit;
				}
					break;
				case HysteresePad::Hoog:
				{
					if (verschil < minDzWaarde)
					{
						hysterese = HysteresePad::Laag;
						resultaat = dacLowerLimit;
					}
					else
						resultaat = dacUpperLimit;
				}
					break;
				case HysteresePad::Onbepaald:
				{
					if (verschil >= dzWaarde)
					{
						hysterese = HysteresePad::Hoog;
						resultaat = dacUpperLimit;
					}
					else if (verschil < minDzWaarde)
					{
						hysterese = HysteresePad::Laag;
						resultaat = dacLowerLimit;
					}
					else
						resultaat = 0.0f;
				}
					break;
			}
		}
	}

	return (resultaat);
}








