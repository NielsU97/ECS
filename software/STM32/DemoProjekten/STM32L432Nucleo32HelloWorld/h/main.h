/*!
@file
Demonstratie API van de STM32L432 Nucleo32 met gebruik van de Low Power Timer om de groene LED te laten knipperen.
@version $Rev: 3207 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/BSP/STM32L4xx_Nucleo_32/STM32L4xxNucleo32.cpp $
$Id: STM32L4xxNucleo32.cpp 3207 2018-11-22 08:06:21Z ewout $
************************************************************************/

#ifndef STM32L432NUKLEODEMO_MAIN_H
#define STM32L432NUKLEODEMO_MAIN_H


#include <STM32L4xxNucleo32.h>

class STM32L432DemoController : public STM32L432Nucleo32
{
public:
	STM32L432DemoController();
	
	void helloworld() const;
};

#endif
