/*!
@file
Implementatie van de c++ schil voor gebruik van de STM32412g Discovery kit.
@version $Rev: 3993 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/BSP/STM32L4xx_Nucleo_32/STM32L4xxNucleo32.cpp $
$Id: STM32L4xxNucleo32.cpp 3993 2020-10-01 16:24:31Z ewout $
************************************************************************/


#include <STM32L4xxNucleo32.h>
#include <algdef.h>
#include <h/STM32L4xxNucleo32.h>
#include <stm32l4xx_ll_usart.h>
#include <assert.h>


#ifndef HAL_RTC_MODULE_ENABLED
#error "HAL_RTC_MODULE_ENABLED moet aan staan voor dit BSP."
#endif

STM32L432Nucleo32::STM32L432Nucleo32(const UInt32 freq)
{
	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds rtosBasisRGT.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
	/* Configure Flash prefetch, Instruction cache, Data cache */
#if (INSTRUCTION_CACHE_ENABLE != 0U)
	__HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
#endif /* INSTRUCTION_CACHE_ENABLE */

#if (DATA_CACHE_ENABLE != 0U)
	__HAL_FLASH_DATA_CACHE_ENABLE();
#endif /* DATA_CACHE_ENABLE */

#if (PREFETCH_ENABLE != 0U)
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */

	HAL_Init();
	
	/* Eerst de hal tick starten, want deze wordt gebruikt bij de opstart van de LSE klok !*/
	/* Set Interrupt Group Priority */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* Use Tim16 as time base source and configure 1ms tick (default clock after Reset is HSI) */
	HAL_InitTick(TICK_INT_PRIORITY);

//	NVIC_DisableIRQ(SysTick_IRQn);
	SYSCLKConfig_STOP(freq);
//	NVIC_EnableIRQ(SysTick_IRQn);

	/* tijdens slaap en stop moet clk voor debug blijven draaien */
#ifndef NDEBUG
	HAL_DBGMCU_EnableDBGSleepMode();
	HAL_DBGMCU_EnableDBGStandbyMode();
#endif

	/* initialiseer de peripheral drivers */
	gpioInit();
	ledsInit();

	rngInit();
	rtcInit();

	adcInit();
	dacInit();
	usart2Init();
	
	lptimInit();
	timInit();
}



TIM_HandleTypeDef STM32L432Nucleo32::Tim7Handle;

void STM32L432Nucleo32::setLED(const LEDKleur kleur,
                               const Schakelaar stand) const
{
	if(kleur < LEDKleur::LaatsteKleur) /* doe alleen de toegestane kleuren. */
	{
		static const Led_TypeDef stLEDs[1] = {LED_GREEN};

		/* Een echte lambda funktie !! */
		auto schakelFunk = [](const LEDKleur lkleur, const Schakelaar s) {
			const auto k = static_cast<Teller>(lkleur);
			switch (s)
			{
				case Schakelaar::Uit:
					BSP_LED_Off(stLEDs[k]);
					break;
				case Schakelaar::Aan:
					BSP_LED_On(stLEDs[k]);
					break;
				case Schakelaar::Om:
					BSP_LED_Toggle(stLEDs[k]);
					break;
				default:
					StopHier();
					break;
			}
		};

		if (kleur < LEDKleur::AllColours)
			schakelFunk(kleur, stand);
		else
		{
			for (auto i = 0; i < 4; i++)
				schakelFunk(static_cast<LEDKleur>(i), stand);
		}
	}
}

void STM32L432Nucleo32::blinkLED(const STM32L432Nucleo32::BlinkSetting stand) const
{
	assert(stand<BlinkSetting::Last);

	switch(stand)
	{
		case BlinkSetting::Stop:
		{
			BSP_LED_Off(LED_GREEN);
			HAL_LPTIM_Counter_Stop_IT(&hlptim1);
			HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
		}
			break;

		case BlinkSetting::PermanentOn:
		{
			BSP_LED_On(LED_GREEN);
			HAL_LPTIM_Counter_Stop_IT(&hlptim1);
			HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
		}
			break;

		default:
		{
			/* gebaseerd op LPTIM1 , welke gevoed wordt door de LSE met prescaler 2 */
			static const UInt16 knipperStanden[] =
					{
							0,
							0,
							65535,   /* 32767 / (2*65535) = 1/4 Hz */
							32767,   /* 32767 / (2*32767) = 1/2 Hz */
							16383,   /* 1 Hz */
							8191,    /* 2 Hz */
							4095     /* 6 Hz */
					};

			const auto periode = knipperStanden[static_cast<Teller>(stand)];
			const auto halvePeriode = periode>>1;
			if(HAL_OK != HAL_LPTIM_SetOnce_Start_IT(&hlptim1,periode,halvePeriode))
			{
				/* Initialization Error */
				StopHier();
			}
			else
			{
				HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
			}
		}
	}
}


void STM32L432Nucleo32::waitFunction(const bool stopMode)
{
	/* stop de systick en andere timer interrupts , deze maakt anders de wfi ongedaan */
	HAL_NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn);
	NVIC_DisableIRQ(SysTick_IRQn);
	if (true == stopMode)
	{
		HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON,PWR_STOPENTRY_WFI);

		/* STM32 gaat verder na knop interrupt */
		SYSCLKConfig_STOP(80);  /* breng PLL en HSE weer tot leven */
	}
	else  /* wacht op interrupt */
	{
		slaapMode();
	}
	HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);
}

TIM_HandleTypeDef STM32L432Nucleo32::Tim15Handle;

void STM32L432Nucleo32::waitFunction(const unsigned short msecs,
                                     const bool slaap) const
{
	__HAL_RCC_TIM15_CLK_ENABLE();
	Tim15Handle.Instance = TIM15;

	Tim15Handle.Init.Period        = 1000*msecs;
	Tim15Handle.Init.Prescaler     = 8000;  /* 80 Mhz --> 8000 */
	Tim15Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim15Handle.Init.CounterMode   = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&Tim15Handle) != HAL_OK)
	{
		/* Initialization Error */
		StopHier();
	}
	else
	{
		HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 14, 0);

		HAL_TIM_Base_Start_IT(&Tim15Handle);
		HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
	}
}

volatile bool STM32L432Nucleo32::timer2Afgelopen=false;

void STM32L432Nucleo32::timer2IsAfgelopen()
{
	timer2Afgelopen=true;
}

void STM32L432Nucleo32::slaapMode() const
{
	/* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
	__force_stores();
#endif
	/* Request Wait For Interrupt */
	asm volatile ("wfi");
	//__WFI();
}

/**
 * @brief  Configures system clock after wake-up from STOP: enable HSE, PLL
 *         and select PLL as system clock source.
 * @param  None
 * @retval None
 */
void STM32L432Nucleo32::SYSCLKConfig_STOP(const UInt32 freq)
{
	assert(freq <= 100);

	/* 8 MHz klok in uit ST-Link, 96 MHz SysClk */
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/**Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
	                                   |RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		StopHier();
	else
	{
		/**Initializes the CPU, AHB and APB busses clocks
		*/
		RCC_ClkInitTypeDef RCC_ClkInitStruct;
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
			StopHier();
		else
		{
			RCC_PeriphCLKInitTypeDef PeriphClkInit;

			PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
			                                     |RCC_PERIPHCLK_LPTIM1|RCC_PERIPHCLK_RNG
			                                     |RCC_PERIPHCLK_ADC;
			PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
			PeriphClkInit.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSE;
			PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
			PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
			PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
			PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
			PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
			PeriphClkInit.PLLSAI1.PLLSAI1N = 16;
			PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
			PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
			PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
			PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK|RCC_PLLSAI1_ADC1CLK;
			if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
				StopHier();
			else
			{
				HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);

				/**Enables the Clock Security System
				*/
				HAL_RCCEx_EnableLSECSS();

				/**Configure the main internal regulator output voltage
   */
				if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
				{
					StopHier();
				}
				else
				{
					/**Configure the Systick interrupt time
					*/
					HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

					/**Configure the Systick
					*/
					HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

					/** Enable MSI Auto calibration */
					HAL_RCCEx_EnableMSIPLLMode();

					/* SysTick_IRQn interrupt configuration */
					HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
				}
			}
		}
	}
}

void STM32L432Nucleo32::initWatchDog(const UInt16 prescaler,
                                     const UInt16 venster)
{
	waakhond.Init.Prescaler = prescaler;
	waakhond.Init.Reload = venster;

	if (HAL_OK != HAL_IWDG_Init(&waakhond))
		StopHier();

}

void STM32L432Nucleo32::petTheWatchdog()
{
	HAL_IWDG_Refresh(&waakhond);
}

void STM32L432Nucleo32::coreReset() const
{
	NVIC_SystemReset();
}

UInt32 STM32L432Nucleo32::revEndianess(const UInt32 value) const
{
	UInt32 result;
	__ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
	return(result);
}

void  STM32L432Nucleo32::ledsInit()
{
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Off(LED_GREEN);
}

void STM32L432Nucleo32::gpioInit()
{
	/* voorlopig niets */
}

void STM32L432Nucleo32::rngInit()
{
	/* Peripheral clock enable */
	__HAL_RCC_RNG_CLK_ENABLE();

	hrng.Instance = RNG;
	if (HAL_RNG_Init(&hrng) != HAL_OK)
		StopHier();
}

void STM32L432Nucleo32::rtcInit()
{
	__HAL_RCC_RTC_ENABLE();

	/**Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
		StopHier();
}


void STM32L432Nucleo32::adcInit()
{
	__HAL_RCC_ADC_CLK_ENABLE();
	/**Common config */
	hadc1.Instance = ADC1;
	auto &init = hadc1.Init;
	init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	init.Resolution = ADC_RESOLUTION_12B;
	init.DataAlign = ADC_DATAALIGN_RIGHT;
	init.ScanConvMode = ADC_SCAN_DISABLE;
	init.EOCSelection = ADC_EOC_SINGLE_CONV;
	init.LowPowerAutoWait = DISABLE;
	init.ContinuousConvMode = DISABLE;
	init.NbrOfConversion = 1;
	init.DiscontinuousConvMode = DISABLE;
	init.ExternalTrigConv = ADC_EXTERNALTRIG_T6_TRGO;
	init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	init.DMAContinuousRequests = DISABLE;
	init.Overrun = ADC_OVR_DATA_PRESERVED;
	init.OversamplingMode = ENABLE;
	init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
	init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
	init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
	init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;

	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		StopHier();
	}
	else
	{
		ADC_ChannelConfTypeDef sConfig;
		/**Configure Regular Channel
		*/
		sConfig.Channel = ADC_CHANNEL_8;
		sConfig.Rank = ADC_REGULAR_RANK_1;
		sConfig.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
		sConfig.SingleDiff = ADC_SINGLE_ENDED;
		sConfig.OffsetNumber = ADC_OFFSET_NONE;
		sConfig.Offset = 0;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			StopHier();
		}
		else
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();

			GPIO_InitTypeDef GPIO_InitStruct;

			/**ADC1 GPIO Configuration
			PA3     ------> ADC1_IN8
			*/
			GPIO_InitStruct.Pin = GPIO_PIN_3;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

			/* ADC1 interrupt Init */
			HAL_NVIC_SetPriority(ADC1_IRQn, 5, 0);
			HAL_NVIC_EnableIRQ(ADC1_IRQn);
		}
	}
}

void STM32L432Nucleo32::dacInit()
{
	__HAL_RCC_DAC1_CLK_ENABLE();
	/**DAC Initialization*/
	hdac1.Instance = DAC1;
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		StopHier();
	}
	else
	{
		DAC_ChannelConfTypeDef sConfig;
		/**DAC channel OUT1 config*/
		sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
		sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
		sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
		sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
		sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
		if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
		{
			StopHier();
		}
		else
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();

			GPIO_InitTypeDef GPIO_InitStruct;

			/**DAC1 GPIO Configuration
			PA4     ------> DAC1_OUT1
			*/
			GPIO_InitStruct.Pin = GPIO_PIN_4;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
	}
}

void STM32L432Nucleo32::usart2Init()
{
	__HAL_RCC_USART2_CLK_ENABLE();
	huart2.Instance = USART2;

	auto &init = huart2.Init;
#ifdef STM32L432Nucleo32BaudRate
	/* ingesteld vanuit RGT.cmake
	 * win 10 machines op school werken standaard op 9600 en niet op 115200 !!! 115200; */
 	init.BaudRate = STM32L432Nucleo32BaudRate;
#else
	init.BaudRate = 115200;
#endif
	init.WordLength = UART_WORDLENGTH_8B;
	init.StopBits = UART_STOPBITS_1;
	init.Parity = UART_PARITY_NONE;
	init.Mode = UART_MODE_TX_RX;
	init.HwFlowCtl = UART_HWCONTROL_NONE;
	init.OverSampling = UART_OVERSAMPLING_16;
	init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	auto &advInit = huart2.AdvancedInit;
//	advInit.AdvFeatureInit = UART_ADVFEATURE_AUTOBAUDRATE_INIT;
//	advInit.AutoBaudRateEnable = UART_ADVFEATURE_AUTOBAUDRATE_ENABLE;
//	advInit.AutoBaudRateMode = UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		StopHier();
	}
	else
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct;
		/**USART2 GPIO Configuration
		 PA2     ------> USART2_TX
		 PA15 (JTDI)     ------> USART2_RX
		 */

		GPIO_InitStruct.Pin = VCP_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = VCP_RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF3_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		__HAL_RCC_DMA1_CLK_ENABLE();
		/* USART2 DMA Init */
		/* USART2_RX Init */
		hdma_usart2_rx.Instance = DMA1_Channel6;
		auto &rxInit = hdma_usart2_rx.Init;
		rxInit.Request = DMA_REQUEST_2;
		rxInit.Direction = DMA_PERIPH_TO_MEMORY;
		rxInit.PeriphInc = DMA_PINC_DISABLE;
		rxInit.MemInc = DMA_MINC_ENABLE;
		rxInit.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		rxInit.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		rxInit.Mode = DMA_NORMAL;
		rxInit.Priority = DMA_PRIORITY_MEDIUM;
		if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
		{
			StopHier();
		}
		else
		{
			__HAL_LINKDMA(&huart2, hdmarx, hdma_usart2_rx);

			/* USART2_TX Init */
			hdma_usart2_tx.Instance = DMA1_Channel7;
			auto &txInit = hdma_usart2_tx.Init;
			txInit.Request = DMA_REQUEST_2;
			txInit.Direction = DMA_MEMORY_TO_PERIPH;
			txInit.PeriphInc = DMA_PINC_DISABLE;
			txInit.MemInc = DMA_MINC_ENABLE;
			txInit.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
			txInit.MemDataAlignment = DMA_MDATAALIGN_BYTE;
			txInit.Mode = DMA_NORMAL;
			txInit.Priority = DMA_PRIORITY_LOW;
			if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
			{
				StopHier();
			}
			else
			{
				__HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);

				HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 7, 0);
				HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 8, 0);

//				isrSem[static_cast<Teller>(Semafoor::Tx)] = CountingSemaphore(1,1);
//				isrSem[static_cast<Teller>(Semafoor::Tx)].Give(); /* hij staat klaar voor gebruik */
			}
		}
	}
}

void STM32L432Nucleo32::lptimInit()
{
	__HAL_RCC_LPTIM1_CLK_ENABLE();

	hlptim1.Instance = LPTIM1;
	auto &init = hlptim1.Init;
	
	init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
	init.Clock.Prescaler = LPTIM_PRESCALER_DIV2;
	init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
	init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
	init.UpdateMode = LPTIM_UPDATE_ENDOFPERIOD;
	init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
	init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
	init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
	if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
	{
		StopHier();
	}
}

void STM32L432Nucleo32::timInit()
{
	TIM_MasterConfigTypeDef sMasterConfig;

	__HAL_RCC_TIM6_CLK_ENABLE();

	htim6.Instance = TIM6;

	htim6.Init.Prescaler = 80;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 1000;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
		StopHier();
	}
	else
	{
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
		{
			StopHier();
		}
		else
		{
			__HAL_RCC_TIM7_CLK_ENABLE();
			htim7.Instance = TIM7;
			htim7.Init.Prescaler = 800;
			htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim7.Init.Period = 10000;
			htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
			if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
			{
				StopHier();
			}
			else
			{
				/*Configure the Tim7IRQ priority */
				HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, 12,0);

				sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
				sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
				if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
				{
					StopHier();
				}
				else
				{
					__HAL_RCC_TIM15_CLK_ENABLE();

					htim15.Instance = TIM15;
					htim15.Init.Prescaler = 800;
					htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
					htim15.Init.Period = 10000;
					htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
					htim15.Init.RepetitionCounter = 0;
					htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
					if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
					{
						StopHier();
					}
					else
					{
						TIM_ClockConfigTypeDef sClockSourceConfig;
						sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
						if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
						{
							StopHier();
						}
						else
						{
							sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
							sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
							if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
							{
								StopHier();
							}
							else
							{
								/*Configure the Tim7IRQ priority */
								HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 13,0);
							}
						}
					}
				}
			}
		}
	}
}


void STM32L432Nucleo32::send(const BoardUART eh,
                             const DataPakket<UInt8> &zendPakket)
{
	static const IRQn_Type uartDMAirqn[] = { DMA1_Channel7_IRQn , DMA1_Channel7_IRQn };

	/* neem de semafoor om toegang te krijgen tot de USART en de DMA */
	if (BoardUART::UART2 == eh)
	{

#ifndef FreeRTOSGebruikt
		while (false == isrSem[sem(Semafoor::Tx)]);
#else
		isrSem[sem(Semafoor::Tx)].Take();
#endif
	}
	else
	{
#ifndef FreeRTOSGebruikt
		while (false == isrSem[sem(Semafoor::Tx)]);
#else
		isrSem[sem(Semafoor::Tx)].Take();
#endif
	}
	const auto masterIndex = static_cast<Teller>(eh);
	/* IRQ wordt uitgezet in de ISR na verzending */
	NVIC_EnableIRQ(uartDMAirqn[masterIndex]);

	UART_HandleTypeDef * const huart = ((BoardUART::UART2 == eh) ? &huart2 : &huart2);
	auto * const tekens = zendPakket.geefPtr();
	const auto grootte = static_cast<UInt16>(zendPakket.geefGrootte());

	ONGEBRUIKT const HAL_StatusTypeDef status  = HAL_UART_Transmit_DMA(huart,tekens,grootte);
	assert(HAL_OK == status);
}

void STM32L432Nucleo32::receive(const BoardUART eh,
                                const DataPakket<UInt8> &ontvangPakket)
{
	assert(BoardUART::UART2==eh);


#ifndef FreeRTOSGebruikt
	isrSem[sem(Semafoor::Rx)]=false;
#endif

	auto * const huart = &huart2 ;

	/* Soms staat er nog data in het USART DR. lees deze data, anders pikt de DMA dit op. */
	LL_USART_ReceiveData8(huart->Instance);

	static const IRQn_Type uartDMAirqn[] = { DMA1_Channel6_IRQn , DMA1_Channel6_IRQn };

	const auto masterIndex = static_cast<Teller>(eh);
	NVIC_EnableIRQ(uartDMAirqn[masterIndex]);


	auto * const tekens = reinterpret_cast<UInt8 *>(&(ontvangPakket[0]));
	const auto grootte = static_cast<UInt16>(ontvangPakket.geefGrootte());

	ONGEBRUIKT const HAL_StatusTypeDef status = HAL_UART_Receive_DMA(huart,tekens,grootte);

	assert(HAL_OK == status);

#ifndef FreeRTOSGebruikt
		while (false == isrSem[sem(Semafoor::Rx)]);
#else
		const auto sw = sem(Semafoor::Rx);
		isrSem[sw].Take();
#endif

	NVIC_DisableIRQ(uartDMAirqn[masterIndex]);
}



FoutCode STM32L432Nucleo32::backupGeheugenOpslaan(const UInt16 adres, const UInt32 waarde)
{
	assert(adres<20);
	auto retkode = FoutCode::Onbekend;

	if (false == (adres<20))
		retkode = FoutCode::Fout;
	else
	{
		const auto hwAdres = (RTC_BKP_DR0 + adres);
		HAL_RTCEx_BKUPWrite(&hrtc, hwAdres, waarde);
		retkode = FoutCode::Ok;
	}
	return(retkode);
}

UInt32 STM32L432Nucleo32::backupGeheugenLezen(const UInt16 adres)
{
	assert(adres<20);

	UInt32 waarde = 0;

	if (true == (adres<20))
	{
		const auto hwAdres = (RTC_BKP_DR0 + adres);
		waarde = HAL_RTCEx_BKUPRead(&hrtc,hwAdres);
	}

	return(waarde);
}

TIM_HandleTypeDef STM32L432Nucleo32::Tim16Handle;

HAL_StatusTypeDef STM32L432Nucleo32::HAL_InitTick(uint32_t TickPriority)
{
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock = 0;
	uint32_t              uwPrescalerValue = 0;
	uint32_t              pFLatency;

	/* Enable Tim16 clock */
	__HAL_RCC_TIM16_CLK_ENABLE();

	/* Get clock configuration */
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	/* Compute Tim16 clock */
	uwTimclock = 2*HAL_RCC_GetPCLK1Freq();

	/* Compute the prescaler value to have Tim16 counter clock equal to 1MHz */
	uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);

	/* Initialize Tim16 */
	Tim16Handle.Instance = TIM16;

	/* Initialize TIMx peripheral as follow:
	+ Period = [(Tim16CLK/1000) - 1]. to have a (1/1000) s time base.
	+ Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
	+ ClockDivision = 0
	+ Counter direction = Up
	*/
	auto &handel = Tim16Handle.Init;
	handel.Period = (1000000 / 1000) - 1;
	handel.Prescaler = uwPrescalerValue;
	handel.ClockDivision = 0;
	handel.CounterMode = TIM_COUNTERMODE_UP;

	ONGEBRUIKT const auto status = HAL_TIM_Base_Init(&Tim16Handle);
	assert(HAL_OK == status);

	/*Configure the Tim16 IRQ priority */
	HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, TickPriority,0);
	/* Enable the Tim16 global Interrupt */
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

	/* Start the TIM time Base generation in interrupt mode */
	return HAL_TIM_Base_Start_IT(&Tim16Handle);

}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling Tim16 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
	/* Disable Tim16 update Interrupt */
	__HAL_TIM_DISABLE_IT(&STM32L432Nucleo32::Tim16Handle, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling Tim16 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
	/* Enable Tim16 Update interrupt */
	__HAL_TIM_ENABLE_IT(&STM32L432Nucleo32::Tim16Handle, TIM_IT_UPDATE);
}

#ifdef FreeRTOSGebruikt

void STM32L432Nucleo32::isrSemafoorAfhandeling(CountingSemaphore &sem)
{
	BaseType_t nieuwePrio;
	const bool wakkerGeworden = sem.GiveFromISR(&nieuwePrio);
	if (true == wakkerGeworden)
		portYIELD_FROM_ISR(nieuwePrio);
}

CountingSemaphore STM32L432Nucleo32::isrSem[AantalSems] = { CountingSemaphore(1,0),
															CountingSemaphore(1,1),
															CountingSemaphore(1,0) };
#else
bool STM32L432Nucleo32::isrSem[AantalSems] = { false,true,false };
#endif

DMA_HandleTypeDef STM32L432Nucleo32::hdma_usart2_tx;
DMA_HandleTypeDef STM32L432Nucleo32::hdma_usart2_rx;
UART_HandleTypeDef STM32L432Nucleo32::huart2;
ADC_HandleTypeDef STM32L432Nucleo32::hadc1;
LPTIM_HandleTypeDef STM32L432Nucleo32::hlptim1;

const GPIO_TypeDef * STM32L432Nucleo32::MCO_GPIO_Port = GPIOA;
const GPIO_TypeDef * STM32L432Nucleo32::VCP_TX_GPIO_Port= GPIOA;
const GPIO_TypeDef * STM32L432Nucleo32::SWDIO_GPIO_Port= GPIOA;
const GPIO_TypeDef * STM32L432Nucleo32::SWCLK_GPIO_Port= GPIOA;
const GPIO_TypeDef * STM32L432Nucleo32::VCP_RX_GPIO_Port= GPIOA;
const GPIO_TypeDef * STM32L432Nucleo32::LD3_GPIO_Port= GPIOB;




/* C++ name mangling mag niet de interrupt handler namen veranderen, 
 * deze staan in een assembly bestand zo genoemd.
 * Derhalve hieronder met C-Linking compileren.
 */
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
  Cortex-M3 Processor Exceptions Handlers
******************************************************************************/

// ----------------------------------------------------------------------------
// This function handles NMI exception.
// ----------------------------------------------------------------------------
void NMI_Handler(void)
{
	while(1){;}
}

// ----------------------------------------------------------------------------
// This function handles Hard Fault exception.
// ----------------------------------------------------------------------------
void HardFault_Handler(void)
{
	// Go to infinite loop when Hard Fault exception occurs
	while(1){;}
}

// ----------------------------------------------------------------------------
// This function handles Memory Manage exception.
// ----------------------------------------------------------------------------
void MemManage_Handler(void)
{
	// Go to infinite loop when Memory Manage exception occurs
	while(1){;}
}

// ----------------------------------------------------------------------------
// This function handles Bus Fault exception.
// ----------------------------------------------------------------------------
void BusFault_Handler(void)
{
	// Go to infinite loop when Bus Fault exception occurs
	while(1){;}
}

// ----------------------------------------------------------------------------
// This function handles Usage Fault exception.
// ----------------------------------------------------------------------------
void UsageFault_Handler(void)
{
	// Go to infinite loop when Usage Fault exception occurs
	while(1){;}
}

// ----------------------------------------------------------------------------
// This function handles SVCall exception.
// ----------------------------------------------------------------------------
ZWAKGEPLAATST void SVC_Handler(void)
{
}

// ----------------------------------------------------------------------------
// This function handles Debug Monitor exception.
// ----------------------------------------------------------------------------
void DebugMon_Handler(void)
{
}

// ----------------------------------------------------------------------------
// This function handles PendSV_Handler exception.
// ----------------------------------------------------------------------------
ZWAKGEPLAATST void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
ZWAKGEPLAATST void SysTick_Handler(void)
{
	HAL_SYSTICK_IRQHandler();
}


void TIM1_BRK_TIM15_IRQHandler(void)
{
	/* wacht timer */
	HAL_TIM_IRQHandler(&(STM32L432Nucleo32::Tim15Handle));

	STM32L432Nucleo32::timer2IsAfgelopen();
}

void TIM7_IRQHandler(void)
{
	/* blauwe led knipper */
	HAL_TIM_IRQHandler(&(STM32L432Nucleo32::Tim7Handle));
	BSP_LED_Toggle(LED_GREEN);
}



void TIM1_UP_TIM16_IRQHandler(void)
{
	/**
     * @brief  Deze funktie wordt gebruikt voor de HAL Tick funktie.
     */

	HAL_TIM_IRQHandler(&(STM32L432Nucleo32::Tim16Handle));
	HAL_IncTick();

}


/**
  * @brief This function handles LPTIM1 global interrupt.
  */
void LPTIM1_IRQHandler(void)
{
	HAL_LPTIM_IRQHandler(&(STM32L432Nucleo32::hlptim1));
	BSP_LED_Toggle(LED_GREEN);	
}

void USART2_IRQHandler()
{
	const bool rxInterrupt = (HAL_UART_STATE_BUSY_RX  == STM32L432Nucleo32::huart2.RxState);
	const bool txInterrupt = (HAL_UART_STATE_BUSY_TX  == STM32L432Nucleo32::huart2.gState);

	HAL_UART_IRQHandler(&(STM32L432Nucleo32::huart2));

	if (true == rxInterrupt)
	{
		const bool rxEindeInterrupt = (HAL_UART_STATE_READY  == STM32L432Nucleo32::huart2.RxState);
		if (true == rxEindeInterrupt)
		{
			static constexpr auto index = STM32L432Nucleo32::sem(STM32L432Nucleo32::Semafoor::Rx);
#ifndef FreeRTOSGebruikt
			STM32L432Nucleo32::isrSem[index] = true;
#else
			auto &sem = STM32L432Nucleo32::isrSem[index];
			STM32L432Nucleo32::isrSemafoorAfhandeling(sem);
#endif
		}
	}
	else if (true == txInterrupt)
	{
		const bool txEindeInterrupt = (HAL_UART_STATE_READY  == STM32L432Nucleo32::huart2.gState);
		if (true == txEindeInterrupt)
		{
			static constexpr auto index = STM32L432Nucleo32::sem(STM32L432Nucleo32::Semafoor::Tx);
#ifndef FreeRTOSGebruikt

			STM32L432Nucleo32::isrSem[index] = true;
#else
			auto &sem = STM32L432Nucleo32::isrSem[index];
			STM32L432Nucleo32::isrSemafoorAfhandeling(sem);
#endif
		}
	}
}
/**
* @brief This function handles DMA1 Channel 6 global interrupt.
*/
void DMA1_Channel6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&(STM32L432Nucleo32::huart2));
	HAL_DMA_IRQHandler(&STM32L432Nucleo32::hdma_usart2_rx);

	if(HAL_DMA_STATE_READY == STM32L432Nucleo32::hdma_usart2_rx.State)
	{
		static constexpr auto index = STM32L432Nucleo32::sem(STM32L432Nucleo32::Semafoor::Rx);
		STM32L432Nucleo32::huart2.gState = HAL_UART_STATE_READY; /* fix want hal bibliotheek doet dit niet ..... */
#ifndef FreeRTOSGebruikt
		STM32L432Nucleo32::isrSem[index] = true;
#else
		auto &sem = STM32L432Nucleo32::isrSem[index];
		STM32L432Nucleo32::isrSemafoorAfhandeling(sem);
#endif
	}
}

/**
* @brief This function handles DMA1 Channel 7 global interrupt.
*/
void DMA1_Channel7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&STM32L432Nucleo32::hdma_usart2_tx);

	if(HAL_DMA_STATE_READY == STM32L432Nucleo32::hdma_usart2_tx.State)
	{
		NVIC_DisableIRQ(DMA1_Channel7_IRQn); /* zet uit */

		static constexpr auto index = STM32L432Nucleo32::sem(STM32L432Nucleo32::Semafoor::Tx);
		STM32L432Nucleo32::huart2.gState = HAL_UART_STATE_READY; /* fix want hal bibliotheek doet dit niet ..... */
#ifndef FreeRTOSGebruikt
		STM32L432Nucleo32::isrSem[index] = true;
#else
		auto &sem = STM32L432Nucleo32::isrSem[index];
		STM32L432Nucleo32::isrSemafoorAfhandeling(sem);
#endif

	}
}


#ifdef __cplusplus
}
#endif

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
extern "C" void assert_failed(char *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	StopHier();

}



#endif

