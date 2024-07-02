/******************************************************************************
 * Project        : HAN ESE Project 3 - Regeltechniek
 * File           : Regeltechniek Taak klasse
 * Copyright      : 2010-2017 HAN Embedded Systems Engineering
 ******************************************************************************
  Change History:

    Version 1.0 - September 2010
    > Initial revision

$Id: RGTTaak.h 4195 2021-03-05 14:01:47Z ewout $  
******************************************************************************/

#ifndef HANESE_rgtTaak_H
#define HANESE_rgtTaak_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <rtosTaak.h>
#include <InputResponsieSessie.h>

#if (defined(InputResponsieOpdracht) )
class OpenLoopTask : public RTOSTask
{
public:
	OpenLoopTask();

protected:
	void Run() final;

private:
	RGTProces rgtProces;
};
#endif

#if (defined(PIDControllerOpdracht))
#include <PIDControllerSessie.h>
class PIDTaak : public RTOSTask
{
public:
	/*! @brief Constructor. */
	PIDTaak();

protected:
	void Run() final;

private:
	/* TODO 05.03.2021 Plaats hier een dummie buffer om geheugencorruptie op te vangen.
	 * TODO Echte fix is nog niet aanwezig. */
	UInt32 dummyGeheugen[64];

	PIDController pid;

	AanUitController aanUit;

	RGTProces rgtProces;

	Schakelaar startL432();
	Schakelaar startF412();

};
#elif (defined(FuzzyOpdracht))
#include <fuzzyController.h>

class FuzzyTaak : public RTOSTask
{
public:
	/*! @brief Constructor. */
	FuzzyTaak();

protected:
	void Run() final;

private:
	FuzzyController fuzzy;
	AanUitController aanUit;
	RGTProces rgtProces;
};

#endif

class LedBlinkTask : public StdTaak
{
public:
	LedBlinkTask();

protected:
    [[noreturn]] void Run() final;

private:

};

#endif
