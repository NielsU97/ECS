/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek klasse
 * Copyright      : 2010 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: aanUitControllerSessie.h 4009 2020-11-12 14:13:31Z ewout $  
******************************************************************************/

#ifndef HANESE_REGELTECHNIEK_AanUitController_H
#define HANESE_REGELTECHNIEK_AanUitController_H

#include <RGTData.h>

/*! @brief Basisklasse voor de Student Aan/Uit Controller **/
class AanUitController
{
public :

	/*! @brief De constructor voor de Aan/Uit controller.
	 */
	AanUitController() = default;
	~AanUitController() = default;

	enum class Eigenschap
	{
		Standaard,
		DodeZone,
		Hysterese
	};

	void zetEigenschap(const Eigenschap,const Spanning param=0.0f);

	/*! @brief De student moet deze funktie implementeren / The student must implement this function.
	 * @param De setpoint waarde / the setpoint value.
	 * @param de proces meetwaarde / the proces measurement value.
	 * @return De controle waarde die het proces in gaat / the control value that will be put into the process.
	 * @note Spanning = Voltage ***/
	Spanning aanUitFunktie(const Spanning, const Spanning);


private:
	
	/* Grenswaarden voor het systeem. Gebruik deze grenzen om de integratie te temmen. */
	static constexpr auto dacLowerLimit = 0.0f,dacUpperLimit=3.0f;
	static constexpr auto minIGrens =  10*dacUpperLimit;
	static constexpr auto iGrens =  10*dacUpperLimit;

	Eigenschap eigenschap = Eigenschap::Standaard;
	Spanning dzWaarde=0.0f;
	Spanning minDzWaarde=0.0f;

	enum class HysteresePad
	{
		Hoog,
		Laag,
		Onbepaald
	} hysterese = HysteresePad::Onbepaald;

};


#endif
