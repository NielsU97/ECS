/*!
@file
API van de c++ schil voor gebruik van de STM32412g Discovery kit.
@version $Rev: 3655 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/BSP/STM32L4xx_Nucleo_32/h/STM32L4xxNucleo32.h $
$Id: STM32L4xxNucleo32.h 3655 2019-10-05 15:56:33Z ewout $
************************************************************************/

#ifndef STM32L432Nucleo32_H
#define STM32L432Nucleo32_H

#include "stm32l4xx_nucleo_32.h"
#include <CortexMProcessor.h>

#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_rng.h>
#include <stm32l4xx_hal_rtc.h>
#include <stm32l4xx_hal_iwdg.h>
#include <stm32l4xx_hal_adc.h>
#include <stm32l4xx_hal_lptim.h>

#include <algdef.h>
#include <dataPakket.h>

#ifdef FreeRTOSGebruikt
#include <semaphore.hpp>
#include <stm32l4xx_hal_tim.h>
using namespace cpp_freertos;
#endif


class STM32L432Nucleo32 : public CortexMProcessor
{
public:

	enum class LEDKleur
	{
		Green=0,
		AllColours,
		Red,   /* niet toegestane kleuren */
		Orange,
		Blue,
		LaatsteKleur
	} ;

	using LEDColour = LEDKleur;

	/*! @brief schakel een LED */
	void setLED(const LEDKleur,
	            const Switch ) const;

	enum class BlinkSetting
	{
		Stop=0,
		PermanentOn,
		VerySlow,  /* 1/4 Hz */
		Slow,      /* 1/2 Hz */
		Middle,    /* 1 Hz */
		Fast,      /* 2 Hz */
		VeryFast,  /* 4 Hz */
		Last
	};

	/*! @brief Blink the Green LED using timer 7 */
	void blinkLED(const BlinkSetting ) const;


	/*! @brief wacht in stop mode/ slaap mode
	 * @param stopMode = true --> wacht in STOP mode, false --> wacht in SLEEP mode */
	void waitFunction(const bool stopMode);

	/*! @brief wacht funktie gebaseerd op timer 4
	 *  @param  Wachttijd in millisecs.
	 *  @param Wacht in slaapmode (true = sleepmode, false = polling) */
	void waitFunction(const unsigned short,
	                  const bool slaap = true) const;

	/*! @brief Stel de Independent wachtdog in */
	void initWatchDog(const UInt16 prescaler = 8,
	                  const UInt16 window = 80);

	/*! @brief zorg er voor dat de lopende watchdog niet een HW reset veroorzaakt. */
	void petTheWatchdog();

	/*! @brief voer een HW reset uit op deze processor.
	 * @warning Er is gee nweg terug. Het programma stopt en start opnieuw !
	 */
	void coreReset() const;

	/*! @enum UART2 (DBG) en UART6 (FTDI ==> USB) selektor */
	enum class BoardUART
	{
		UART2=0,  /* Virtual Com port UART verbonden */
		UART6,    /* FTDI verbonden */
		LaatsteUART
	};

	/*! @brief Verstuur unidirectioneel een UInt8 gebaseerd datapakket.
  * @param de SPI slaaf in kwestie.
  * @param pakket dat naar de uitgaande data wijst. */
	void send(const BoardUART eh,
	          const DataPakket<UInt8> &);

	/*! @brief Ontvang unidirectioneel een char gebaseerd datapakket van de uart2
	  * @param de UART in kwestie.
	  * @param pakket dat naar de binnenkomende data wijst. */
	void receive(const BoardUART eh,
	             const DataPakket<UInt8> &);

	static void timer2IsAfgelopen();

	enum class Semafoor
	{
		Rx=0,
		Tx,
		ADC,
		LaatsteSem
	};
	static constexpr auto AantalSems = static_cast<Teller>(Semafoor::LaatsteSem);

	static constexpr inline Teller sem(const Semafoor s)
	{
		return(static_cast<Teller>(s));
	};

	/*! @brief draai de byte volgorde van 4,3,2,1 om naar 1,2,3,4.
	 * @param Het om te draaien word.
	 * @return Het omgedraaide word.
	 */
	UInt32 revEndianess(const UInt32) const;

	static TIM_HandleTypeDef Tim6Handle; /* voor ADC bemonstering */
	static TIM_HandleTypeDef Tim7Handle; /* voor knipper van Groene LED */
	static TIM_HandleTypeDef Tim15Handle; /* voor wachtfunktie */
	static TIM_HandleTypeDef Tim16Handle; /* voor HAL Tick */

#ifdef FreeRTOSGebruikt
	static CountingSemaphore isrSem[AantalSems];
#else
	static bool isrSem[AantalSems];
#endif

	static DMA_HandleTypeDef hdma_usart2_tx;
	static DMA_HandleTypeDef hdma_usart2_rx;

	static UART_HandleTypeDef huart2;
	static ADC_HandleTypeDef hadc1;

	/* Voor het omschakelen van de groeen led in een isr */
	static LPTIM_HandleTypeDef hlptim1;

#ifndef FreeRTOSGebruikt

#else
	static void isrSemafoorAfhandeling(CountingSemaphore &sem);
#endif

	FoutCode backupGeheugenOpslaan(const UInt16 adres, const UInt32 waarde);
	UInt32 backupGeheugenLezen(const UInt16 adres);

protected:

	/*! @brief Constructor.
     * @param de PLL output (SYSCLK) frequentie in MHz. */
	explicit STM32L432Nucleo32(const UInt32 );

	RTC_HandleTypeDef hrtc;


	DAC_HandleTypeDef hdac1;

	TIM_HandleTypeDef htim6;
	TIM_HandleTypeDef htim7;
	TIM_HandleTypeDef htim15;

private:

	/*! @brief initialiseer de gpio voor I/O akties zoals antia alias ctrl en rgt ctrl */
	void gpioInit();

	void ledsInit();

	void rngInit();

	void rtcInit();

	void adcInit();
	void dacInit();

	/* De virtuele compoort */
	void usart2Init();

	void lptimInit();
	void timInit();

	void slaapMode() const;

	/**
     * @brief  This function configures the TIM16 as a time base source.
     *         The time source is configured  to have 1ms time base with a dedicated
     *         Tick interrupt priority.
     * @note   This function is called  automatically at the beginning of program after
     *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
     * @param  TickPriority: Tick interrupt priorty.
     * @retval HAL status
     */
	HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority=14);


	/* herstel HSE/PLL na stop mode */
	void SYSCLKConfig_STOP(const UInt32 freq);

	ErrorStatus HSEStartUpStatus;

	IWDG_HandleTypeDef waakhond;   /* de waakhond */
	RNG_HandleTypeDef hrng;        /* getalgenerator */


	static volatile bool timer2Afgelopen;

	static constexpr auto MCO_Pin=GPIO_PIN_0;
	static const GPIO_TypeDef * MCO_GPIO_Port; //= GPIOA;
	static constexpr auto VCP_TX_Pin= GPIO_PIN_2;
	static const GPIO_TypeDef * VCP_TX_GPIO_Port; //= GPIOA;
	static constexpr auto SWDIO_Pin= GPIO_PIN_13;
	static const GPIO_TypeDef * SWDIO_GPIO_Port; //= GPIOA;
	static constexpr auto SWCLK_Pin= GPIO_PIN_14;
	static const GPIO_TypeDef * SWCLK_GPIO_Port; //= GPIOA;
	static constexpr auto VCP_RX_Pin= GPIO_PIN_15;
	static const GPIO_TypeDef * VCP_RX_GPIO_Port; //= GPIOA;
	static constexpr auto LD3_Pin= GPIO_PIN_3;
	static const GPIO_TypeDef * LD3_GPIO_Port; //= GPIOB;


};

#endif /* STM32L432Nucleo32_H */
