/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef NUCLONE_STM32F030K6_HPP
#define NUCLONE_STM32F030K6_HPP

#include <st/libmcu_STM32F031K6T_ll.hpp>

#define CLOCK_XTAL (8000000u) /*!< Crystal frequency */
#define CLOCK_AHB1 (8000000u) /*!< AHB1 frequency */
#define CLOCK_AHB2 (8000000u) /*!< AHB2 frequency */
#define CLOCK_APB (8000000u)  /*!< APB frequency */
#define CLOCK_HCLK (8000000u) /*!< core clock */

// PA0 is led pin

#define TICKS_PER_S 2

// register definitions of peripherals
static constexpr libMcu::hwAddressType gpioaAddress = libMcuHw::gpioaAddress;
libMcuHw::gpio::gpio *const gpioaRegisters{reinterpret_cast<libMcuHw::gpio::gpio *>(gpioaAddress)};
static constexpr libMcu::hwAddressType rccAddress = libMcuHw::rccAddress;
libMcuHw::rcc::rcc *const rccRegisters{reinterpret_cast<libMcuHw::rcc::rcc *>(rccAddress)};

void boardInit(void);

#endif