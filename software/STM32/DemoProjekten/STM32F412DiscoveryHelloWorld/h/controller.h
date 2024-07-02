/*!
@file
API van de c++ schil voor gebruik van de STM32412g Discovery kit.
@version $Rev: 3662 $
@author $Author: ewout $

@copyright Copyright 2017-2019 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$Id: controller.h 3662 2019-10-24 15:32:27Z ewout $
************************************************************************/

#ifndef DemoController_H
#define DemoController_H

#include <ESEBoardController.h>

class DemoController : public STM32412gDiscovery
{
public:
	DemoController();
	
	void postOSInit();
	
	void rttMelding(const char *);

private:
	static constexpr auto rttBufferGrootte=64;
	char rttBuffer[rttBufferGrootte];
	bool rttBufferVol = false;
};


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
