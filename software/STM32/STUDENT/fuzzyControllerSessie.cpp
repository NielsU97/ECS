/******************************************************************************
@file
Fuzzy Controller voor PRJ3PRT/Fuz practicum

@version $Rev: 4009 $
@author $Author: ewout $

@copyright Copyright 2013-2018 Hogeschool van Arnhem en Nijmegen

$Id: fuzzyControllerSessie.cpp 4009 2020-11-12 14:13:31Z ewout $
************************************************************************/

//#error  "(FuzzyController.cpp) Student naam en nummer moeten beneden in de velden worden ingevuld."
//#error  "(FuzzyController.cpp) Student name and number must be entered into the fields below."
/********  Naam/name     :   Niels Urgert           ******/
/********  Studentnummer :   654746                 ******/

#include <math.h>
#include <string.h>
#include <assert.h>
#include <fuzzyControllerSessie.h>
#include <cmsis_os.h>

t_er::t_er() : Container()
{
	/* Voor studenten : vul hier de waarden in die uit opdracht 4 komen.
		 * For Students : fill in the values that result from assignment 4 */
#error "Dit deel van de software ontbreekt — this part of the software is missing."
/* Beste leerling, dit deel van de software ontbreekt. Vul dit deel aan volgens de opdracht.  
   Dear student, this part of the software is missing. Complete this part accoording to the assignment.
*/
}

t_cv::t_cv() : Container()
{
	/* Voor studenten : vul hier de waarden in die uit opdracht 4 komen.
		 * For Students : fill in the values that result from assignment 4 */
#error "Dit deel van de software ontbreekt — this part of the software is missing."
/* Beste leerling, dit deel van de software ontbreekt. Vul dit deel aan volgens de opdracht.  
   Dear student, this part of the software is missing. Complete this part accoording to the assignment.
*/
}

Spanning FuzzyController::fuzzyFunktie(const Spanning sp,
                                       const Spanning mw)
{
	const auto verschil = sp-mw;

	// ********************************************************************
	// Fuzzification
	er.dom_negL = MBF_Trapezoid(er.mbf_negL, verschil);
	er.dom_neg  = MBF_Trapezoid(er.mbf_neg,  verschil);
	er.dom_no   = MBF_Trapezoid(er.mbf_no,   verschil);
	er.dom_pos  = MBF_Trapezoid(er.mbf_pos,  verschil);
	er.dom_posL = MBF_Trapezoid(er.mbf_posL, verschil);

	// ********************************************************************
	// Decision making
	cv.dom_negL = er.dom_negL;
	cv.dom_neg  = er.dom_neg;
	cv.dom_no   = er.dom_no;
	cv.dom_pos  = er.dom_pos;
	cv.dom_posL = er.dom_posL;

	// ********************************************************************
	// Defuzzification
	// Centroid method
	const auto controlValue = (((cv.dom_negL * cv.mbf_negL[1] ) +
	                            (cv.dom_neg  * cv.mbf_neg[1]  ) +
	                            (cv.dom_no   * cv.mbf_no[1]   ) +
	                            (cv.dom_pos  * cv.mbf_pos[1]  ) +
	                            (cv.dom_posL * cv.mbf_posL[1] )) /
	                           (cv.dom_negL +
	                            cv.dom_neg  +
	                            cv.dom_no   +
	                            cv.dom_pos  +
	                            cv.dom_posL));
	return(controlValue);
}

// ----------------------------------------------------------------------------
// Membershipfunction implementation
// ----------------------------------------------------------------------------
t_dom FuzzyController::MBF_Trapezoid(t_mbf p[4], t_crisp crisp)
{
	t_dom ret;

	if(crisp < p[0])
	{
		return 0;
	}
	else if(crisp <= p[1])
	{
		if(p[0] == p[1])
		{
			ret = 100;
		}
		else
		{
			ret = ((crisp - p[0]) * 100) / (p[1] - p[0]);
		}
	}
	else if(crisp <= p[2])
	{
		ret = 100;
	}
	else if(crisp <= p[3])
	{
		if(p[2] == p[3])
		{
			ret = 100;
		}
		else
		{
			ret = 100 - ((crisp - p[2]) * 100) / (p[3] - p[2]);
		}
	}
	else
	{
		ret = 0;
	}

	return(ret);
}

// ----------------------------------------------------------------------------
// Membershipfunction implementation
// ----------------------------------------------------------------------------
t_dom FuzzyController::MBF_Triangle(t_mbf p[3], t_crisp crisp)
{
	t_dom ret;

	if(crisp < p[0])
	{
		ret = 0;
	}
	else if(crisp <= p[1])
	{
		if(p[0] == p[1])
		{
			ret = 100;
		}
		else
		{
			ret = ((crisp - p[0]) * 100) / (p[1] - p[0]);
		}
	}
	else if(crisp <= p[2])
	{
		if(p[1] == p[2])
		{
			ret = 100;
		}
		else
		{
			ret = 100 - ((crisp - p[1]) * 100) / (p[2] - p[1]);
		}
	}
	else
	{
		ret = 0;
	}

	return(ret);
}

// ----------------------------------------------------------------------------
// Membershipfunction implementation
// ----------------------------------------------------------------------------
t_dom FuzzyController::MBF_Singleton(t_mbf p, t_crisp crisp)
{
	const t_dom ret = ( (crisp == p) ? 100.0f : 0.0f);

	return(ret);

}

// ----------------------------------------------------------------------------
// Membershipfunction implementation
// ----------------------------------------------------------------------------
t_dom FuzzyController::MBF_Gaussian(t_mbf p[3], t_crisp crisp)
{
	return(0);
}




