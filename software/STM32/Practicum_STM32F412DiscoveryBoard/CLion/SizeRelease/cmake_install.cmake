# Install script for directory: C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/RGTpracticum")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "SizeRelease")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/MinGW/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/BasisDir/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/STM32CMSIS/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/STM32_HAL_Driver/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/FreeRTOS/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/FreeRTOSOOSchil/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/ESE_FreeRTOS/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/Utilities/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/STemWin/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/Components/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/F412GDiscoveryLib/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/FatFS/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/AlgemeenDir/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerRTT/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/SeggerSysview/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/ESE_DigProcesAansturing/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/ESE_BSPProcessor/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/rtosBasisRGT/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/RGTData/cmake_install.cmake")
  include("C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/toepassing/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/niels/Documents/Elektrotechniek/Jaar 2/ECS/ECSL/software/STM32/Practicum_STM32F412DiscoveryBoard/CLion/SizeRelease/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
