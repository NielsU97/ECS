/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek klasse
 * Copyright      : 2010-2020 ir drs E.J Boks HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: PIDControllerSessie.h 4227 2021-04-20 17:28:46Z ewout $  
******************************************************************************/

#ifndef HANESE_REGELTECHNIEK_PIDController_H
#define HANESE_REGELTECHNIEK_PIDController_H

#include <RGTData.h>

/*! @brief Basisklasse voor de Student PID Controller **/
class PIDController
{
public :

	/*! @brief De constructor voor de PID controller. */
	PIDController() = default;
	~PIDController() = default;

	/*! @brief De student moet deze funktie implementeren / The student must implement this function.
	 * This function is the central function in the PID controller.
	 * Implement the collection of P, I and D in this function, as well as the P compensation.
	 * @param De setpoint waarde / the setpoint value.
	 * @param de proces meetwaarde / the proces measurement value.
	 * @return De controle waarde die het proces in gaat / the control value that will be put into the process.
	 * @note Spanning = Voltage ***/
	Spanning pidFunktie(const Spanning,const Spanning);

	/*! @brief puur virtuele reset funktie voor de I en D term, moet worden gemaakt door de student */
	void reset();

	/*! @brief zet de P,I,D waarden */
	void zetPID(const WFT,const WFT,const WFT);

	/*! @brief zet een <-grens,grens> bereik voor de integratiefout.
	 * @param de grenswaarde. */
	//void zetIGrens(const Int32);

	/*! @brief Zet de input kompensatie bij een puur P proces.
	 * @param Moet de kompensatie aan of uit ?
	 * @note De input wordt kunstmatig verhoogt naar (Kp+1)/Kp.
	 */
	void zetKompensatie(const bool );

private:

	/* hulpfunkties voor gebruik in de pidController funktie */
	Spanning P_Aktie(const Spanning) const;
	Spanning I_Aktie(const Spanning);
	Spanning D_Aktie(const Spanning);
	float D_AktieCD(const Spanning invoer);

/* Beste leerling, dit deel van de software ontbreekt. Vul dit deel aan volgens de opdracht.  
   Dear student, this part of the software is missing. Complete this part accoording to the assignment.
*/

	/*! @brief de Kp, Ki en Kd waarden. */
	WFT P=1.0f,I=0.0f,D=0.0f;

	/* Grenswaarden voor het systeem. Gebruik deze grenzen om de integratie te temmen.
	 * Border Values for the system. User these values to limit (tame) the integration. */
#ifdef USE_STM32412G_DISCOVERY
	static constexpr auto dacLowerLimit = 0.0f,dacUpperLimit=5.0f;
#elif defined USE_STM32L432Nucleo32
	static constexpr auto dacLowerLimit = 0.0f,dacUpperLimit=3.0f;
#endif
	/* The minimum value that your integrator can store */
	static constexpr auto minIGrens = 10*dacLowerLimit;

	/* The maximum value that your integrator can store */
	static constexpr auto iGrens =  10*dacUpperLimit;
	bool kompenseerP=false;


};


#endif

