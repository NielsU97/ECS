/*!
@file
Demonstratie API van de STM32F0308 Discovery met gebruik van een timer om de groene LED te laten knipperen.
@version $Rev: 3207 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/BSP/STM32L4xx_Nucleo_32/STM32L4xxNucleo32.cpp $
$Id: STM32L4xxNucleo32.cpp 3207 2018-11-22 08:06:21Z ewout $
************************************************************************/

#ifndef STM32F0DISCOVERDEMO_MAIN_H
#define STM32F0DISCOVERDEMO_MAIN_H


#include <stm32f0308Discovery.h>


class STM32F0308DemoController : public STM32F0308Discovery
{
public:
	STM32F0308DemoController();
	
	void helloworld() const;
};

#endif //STM32F0DISCOVERDEMO_MAIN_H
