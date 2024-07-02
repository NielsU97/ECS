## Copyright 2011-2017 Hogeschool van Arnhem en Nijmegen
## Opleiding Embedded Systems Engineering
## ir drs E.J Boks
## Basis CMake (HAL) bestand voor STM32 gerelateerde development.
## $Id: STM32Development.cmake 3322 2019-02-02 15:01:50Z ewout $

if(NOT SoftwareBasisDir)
  message(FATAL_ERROR "Geef met SoftwareBasisDir aan waar de software basis bibliotheken (algemeen) staan.")
else(NOT STM32BasisDir)
if(NOT STM32BasisDir)
  message(FATAL_ERROR "Geef met STM32BasisDir aan waar de STM32 CMake scripts en STM32 bibliotheken staan.")
else(NOT STM32BasisDir)

  option(OverrideGCC_G++ "G++ override" ON)

  include(${STM32BasisDir}/BasisSTM32.cmake)

  set(STM32StdPeriphHALGemeenschappelijkDir ${STM32BasisDir}/gemeenschappelijk)
  set(LDScriptsDir ${STM32StdPeriphHALGemeenschappelijkDir}/ldscripts)
  set(SVDDir ${STM32StdPeriphHALGemeenschappelijkDir}/peripherals_svd)
  
  set(BasisDir ${STM32StdPeriphHALGemeenschappelijkDir}/basis)
  set(BasisSRCS ${STM32StdPeriphHALGemeenschappelijkDir}/basis/syscalls.cpp)
  set(ESEFreeRTOSDir ${STM32StdPeriphHALGemeenschappelijkDir}/ESEFreeRTOS)
    
  include_directories(${BasisDir}/h ${SoftwareBasisDir}/algemeen/h)
  
  if (GebruikHALDrivers)
	if(GebruikStdPeriphDrivers)
		message(FATAL_ERROR "StdPeriph en HAL kunnen niet tegelijkertijd worden gebruikt.")
	endif(GebruikStdPeriphDrivers)
		
	set(HALBasisDir ${STM32BasisDir}/HAL)
	set(GEMDIR ${HALBasisDir}/gemeenschappelijk)
	set(CMAKESCRIPTDIR ${HALBasisDir}/buildsystem)

	 add_definitions(-DUSE_HAL_DRIVER)
	 
  else(GebruikHALDrivers)
  
	if(NOT GebruikStdPeriphDrivers)
		message(FATAL_ERROR "StdPeriph of HAL moet worden gekozen.")
	endif(NOT GebruikStdPeriphDrivers)
	
  	set(StdPeriphBasisDir ${STM32BasisDir}/StdPeriph)
	set(GEMDIR ${StdPeriphBasisDir}/gemeenschappelijk)
	set(CMAKESCRIPTDIR ${StdPeriphBasisDir}/buildsystem)
   
    set(F0DISCOVERYDIR ${GEMDIR}/STM32F0Discovery)
    set(F1DISCOVERYDIR ${GEMDIR}/STM32F1Discovery)
    set(F3DISCOVERYDIR ${GEMDIR}/STM32F3Discovery)
    set(F4DISCOVERYDIR ${GEMDIR}/STM32F4Discovery)
  
    add_definitions(-DUSE_STDPERIPH_DRIVER)
	
  endif(GebruikHALDrivers)

  set(STLIBRARIES ${GEMDIR}/Libraries)
  set(ThirdParty ${GEMDIR}/Third_Party)
  
endif(NOT STM32BasisDir)
endif(NOT SoftwareBasisDir)
