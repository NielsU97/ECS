/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Fuzzy Controller klasse
 * Copyright      : 2010 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: fuzzyControllerSessie.h 4009 2020-11-12 14:13:31Z ewout $  
******************************************************************************/

#ifndef HANESE_REGELTECHNIEK_FuzzyController_H
#define HANESE_REGELTECHNIEK_FuzzyController_H

#include <RGTData.h>

/******************************************************************************
  Type definitions
******************************************************************************/



template<typename Dom,typename MBF,typename Crisp, const Teller Aantal>
class FuzzyContainer
{
public:
	FuzzyContainer()
	{
		reset();
	}

	/* reset alle MBF waarden naar nul */
	void reset()
	{
		memset(mbf_neg,0,Aantal*sizeof(MBF));
		memset(mbf_negL,0,Aantal*sizeof(MBF));

		memset(mbf_no,0,Aantal*sizeof(MBF));

		memset(mbf_pos,0,Aantal*sizeof(MBF));
		memset(mbf_posL,0,Aantal*sizeof(MBF));
	}

	/* De fuzzy variabelen */

	// Member NEG_LARGE
	MBF   mbf_negL[Aantal];
	Dom   dom_negL;

	// Member NEG
	MBF   mbf_neg[Aantal];
	Dom   dom_neg;

	// Member NO
	MBF   mbf_no[Aantal];
	Dom   dom_no;

	// Member POS
	MBF   mbf_pos[Aantal];
	Dom   dom_pos;

	// Member POS_LARGE
	MBF   mbf_posL[Aantal];
	Dom   dom_posL;

} ;

using t_crisp = float;
using t_dom = float;   // Degree Of Membership
using t_mbf = float;   // MemBership Function

// Linguistic ERROR
class t_er : public FuzzyContainer<t_dom,t_mbf,t_crisp,4>
{
public:
	using Container = FuzzyContainer<t_dom,t_mbf,t_crisp,4>;

	explicit t_er();

	// de Crisp value
	t_crisp crisp = 0.0f;

};

// Consequence CONTROLVALUE
class t_cv : public FuzzyContainer<t_dom,t_mbf,t_crisp,3>
{
public:
	using Container = FuzzyContainer<t_dom,t_mbf,t_crisp,3>;

	explicit t_cv();

};



/*! @brief Basisklasse voor de Student Fuzzy Controller **/
class FuzzyController
{
public :

	/*! @brief De constructor voor de Fuzzy controller.
	 */
	FuzzyController() = default;
	~FuzzyController() = default;

	/*! @brief De student moet deze funktie implementeren / The student must implement this function.
	 * @param De setpoint waarde / the setpoint value.
	 * @param de proces meetwaarde / the proces measurement value.
	 * @return De controle waarde die het proces in gaat / the control value that will be put into the process.
	 * @note Spanning = Voltage ***/
	Spanning fuzzyFunktie(const Spanning, const Spanning);

protected:

	/******************************************************************************
     	Function prototypes
	******************************************************************************/
	t_dom MBF_Trapezoid(t_mbf p[4], t_crisp crisp);
	t_dom MBF_Triangle (t_mbf p[3], t_crisp crisp);
	t_dom MBF_Singleton(t_mbf p, t_crisp crisp);
	t_dom MBF_Gaussian (t_mbf p[2], t_crisp crisp);

	/* Fuzzy beslissers */
	template<typename ttype>
	inline ttype f_and(const ttype a,const ttype b)
	{
		const auto uit = (((a) < (b)) ? (a) : (b));
		return(uit);
	}

	template<typename ttype>
	inline ttype f_or(const ttype a,const ttype b)
	{
		const auto uit = (((a) > (b)) ? (a) : (b));
		return(uit);
	};


private:

	// Fuzzy variables
	t_er  er;  // Error
	t_cv  cv;  // Control Value
	t_dom dom; // Degree of membership (for MOM)
};


#endif
