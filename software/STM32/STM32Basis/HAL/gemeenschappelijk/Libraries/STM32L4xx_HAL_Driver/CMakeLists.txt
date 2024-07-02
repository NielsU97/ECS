## Boombaard gegenereerd CMakelists add_library bestand
## Bestand gegenereerd op : 2020-09-30 17:33:30.
## (c)2001-2018 Hogeschool van Arnhem en Nijmegen
## ir drs E.J Boks, opleiding Elektrotechniek/ESE
## $Id: boombaardvenster.cpp 8532 2017-12-04 19:07:15Z oldenburgh $


set(LibName STM32L4xx_HAL_Driver)

# Het absolute pad voor dit bestand “CMakeLists.txt” is “/Users/ese/vakken/ti_cp/regeltechniek/practicum/rgtpracticum/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/STM32L4xx_HAL_Driver/“ 
## Definieer de minimale cmake versie.
cmake_minimum_required(VERSION 3.10.4)

## GemPath is een gemeenschappelijk pad dat gevonden wordt onder de bron, inclusief en bibliotheek paden.
set(GemPath0 ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
set(GemPath1 ${GemPath0}/Legacy)
set(GemPath2 ${CMAKE_CURRENT_SOURCE_DIR}/Src)



## SourcePath is een gemeenschappelijk pad voor de bronbestanden.
set(SourcePath0 ${GemPath2})
set(SourcePath1 ${GemPath1})
set(SourcePath2 ${GemPath0})



## Dit gedeelte geeft de include directories voor de bronbestanden aan.
set(AllIncludeDirs ${SourcePath1} ${SourcePath2} )
include_directories(${AllIncludeDirs})


## Geef een lijst van alle bronbestanden met de juiste paden.
set(SRCS0 stm32l4xx_hal_rcc.c stm32l4xx_ll_rtc.c stm32l4xx_hal_pka.c stm32l4xx_hal_smartcard.c stm32l4xx_ll_dma2d.c 
	stm32l4xx_ll_tim.c stm32l4xx_hal_pssi.c stm32l4xx_ll_spi.c stm32l4xx_ll_usb.c stm32l4xx_hal_lptim.c stm32l4xx_ll_opamp.c 
	stm32l4xx_hal_nand.c stm32l4xx_ll_fmc.c stm32l4xx_hal_opamp_ex.c stm32l4xx_hal_i2c_ex.c stm32l4xx_hal_dfsdm_ex.c 
	stm32l4xx_hal_pcd_ex.c stm32l4xx_hal_usart_ex.c stm32l4xx_hal_tim_ex.c stm32l4xx_ll_exti.c stm32l4xx_hal_smbus.c 
	stm32l4xx_hal_i2c.c stm32l4xx_hal_wwdg.c stm32l4xx_hal_exti.c stm32l4xx_hal_nor.c stm32l4xx_ll_crs.c 
	stm32l4xx_hal_uart_ex.c stm32l4xx_hal_swpmi.c stm32l4xx_hal_mmc_ex.c stm32l4xx_hal_pcd.c stm32l4xx_hal_iwdg.c 
	stm32l4xx_hal_dac_ex.c stm32l4xx_hal_uart.c stm32l4xx_hal_crc_ex.c stm32l4xx_hal_sd_ex.c stm32l4xx_ll_i2c.c 
	stm32l4xx_hal_ltdc_ex.c stm32l4xx_ll_utils.c stm32l4xx_hal_flash.c stm32l4xx_hal_rng_ex.c stm32l4xx_ll_usart.c 
	stm32l4xx_hal_smartcard_ex.c stm32l4xx_hal_rtc.c stm32l4xx_ll_pka.c stm32l4xx_hal_rcc_ex.c stm32l4xx_ll_rcc.c 
	stm32l4xx_hal_sd.c stm32l4xx_hal_spi.c stm32l4xx_hal_spi_ex.c stm32l4xx_hal_dma_ex.c stm32l4xx_hal_cortex.c 
	stm32l4xx_hal_pwr_ex.c stm32l4xx_ll_sdmmc.c stm32l4xx_hal_tim.c stm32l4xx_hal_dfsdm.c stm32l4xx_hal_firewall.c 
	stm32l4xx_hal_gpio.c stm32l4xx_ll_gpio.c stm32l4xx_hal_crc.c stm32l4xx_hal_hash_ex.c stm32l4xx_hal_dsi.c 
	stm32l4xx_hal_opamp.c stm32l4xx_hal_rtc_ex.c stm32l4xx_ll_lptim.c stm32l4xx_hal_lcd.c stm32l4xx_hal_mmc.c 
	stm32l4xx_ll_pwr.c stm32l4xx_hal_can.c stm32l4xx_ll_adc.c stm32l4xx_hal_rng.c stm32l4xx_hal_hcd.c stm32l4xx_hal_sai_ex.c 
	stm32l4xx_hal_sram.c stm32l4xx_ll_dac.c stm32l4xx_ll_comp.c stm32l4xx_hal_ospi.c stm32l4xx_ll_dma.c 
	stm32l4xx_hal_tsc.c stm32l4xx_hal_dma2d.c stm32l4xx_hal_comp.c stm32l4xx_ll_rng.c stm32l4xx_hal_qspi.c 
	stm32l4xx_hal_dcmi.c stm32l4xx_hal_flash_ramfunc.c stm32l4xx_hal_cryp_ex.c stm32l4xx_hal_hash.c stm32l4xx_hal_adc.c 
	stm32l4xx_hal_adc_ex.c stm32l4xx_hal_flash_ex.c stm32l4xx_hal_dma.c stm32l4xx_hal_usart.c stm32l4xx_hal_sai.c 
	stm32l4xx_ll_lpuart.c stm32l4xx_hal.c stm32l4xx_hal_dac.c stm32l4xx_hal_cryp.c stm32l4xx_ll_crc.c stm32l4xx_hal_ltdc.c 
	stm32l4xx_hal_irda.c stm32l4xx_hal_gfxmmu.c stm32l4xx_ll_swpmi.c stm32l4xx_hal_pwr.c )
set(Addition0Path ${SourcePath0})
foreach(FN ${SRCS0})
	list(APPEND SRCS ${Addition0Path}/${FN})
endforeach(FN)


list(SORT SRCS)

add_library(${LibName} STATIC ${SRCS})
## This library can now be included in any build by using “add_subdirectory( the_path_to_this_lib )”.


