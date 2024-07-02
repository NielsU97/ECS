/******************************************************************************
@file
PID Controller voor PRJ3PRT

@version $Rev: 4322 $
@author $Author: ewout $

@copyright Copyright 2013-2020 ir drs E.J Boks Hogeschool van Arnhem en Nijmegen

$Id: PIDControllerSessie.cpp 4322 2021-10-15 08:37:57Z ewout $
************************************************************************/

//#error  "(PIDcontroller.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(PIDcontroller.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :    Niels Urgert           ******/
/********  Studentnummer :    654746                 ******/

#include <math.h>
#include <string.h>
#include <assert.h>
#include <PIDControllerSessie.h>
#include <cmsis_os.h>

void PIDController::reset() {

    /* Gebruik deze funktie om de I en D akties te resetten.
     * Niet van toepassing bij de P aktie. */
    /* Use this function for ressting the I and D actions.
     * Not applicable for the P aktion. */
    // TODO integrator = 0.0f;
    // TODO differentiator = 0.0f


}

Spanning PIDController::pidFunktie(const Spanning setpoint,
                                   const Spanning meetwaarde)
{
    const auto sp = setpoint;
    const auto mw = meetwaarde;
    const auto error = sp - mw;
    const auto uit = P_Aktie(error)+ I_Aktie(error)+ D_Aktie(error);
    return uit;
}

float PIDController::P_Aktie(const Spanning invoer) const
{
    const auto uit = invoer * P;
    return uit;
}

static float buffer[] = {0.0};

float PIDController::I_Aktie(const Spanning invoer)
{
    //const auto uit = 0.5f * I * (invoer - invoer);
    const auto uit = I * (invoer + buffer[0]);
    buffer[0] = invoer;

    return uit;
}

float PIDController::D_Aktie(const Spanning invoer)
{
    //const auto uit
    return 0.0f;
}

float PIDController::D_AktieCD(const Spanning invoer)
{
    //const auto uit =
    return 0.0f;
}

void PIDController::zetPID(const WFT pw, const WFT iw, const WFT dw)
{
	assert(pw > 0.0f);
	P = pw;

	assert((iw>=0.0f) && (iw<=25.0f));
	I = iw;

	assert((dw>=0.0f) && (dw<=100.0f));
	D = dw;
}


