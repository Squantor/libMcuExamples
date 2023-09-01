/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC812M101DH20_tests.hpp>

instances::iocon::iocon<peripherals::IOCON_cpp> ioconPeripheral;
instances::swm::swm<peripherals::SWM_cpp> swmPeriperhal;
instances::gpio::gpio<peripherals::GPIO_cpp> gpioPeripheral;
instances::spi::spi<peripherals::SPI0_cpp, instances::spi::chipEnables> spiPeripheral;
instances::syscon::syscon<peripherals::SYSCON_cpp> sysconPeripheral;

void crudeDelay(uint32_t iterations) {
  for (uint32_t i = iterations; i > 0; i--) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
}

void boardInit(void) {
  // clock enables and resets
  sysconEnableClocks(SYSCON, CLKCTRL_SWM | CLKCTRL_IOCON | CLKCTRL_GPIO);
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, registers::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalIn);
  swmPeriperhal.setup(xtalOut, xtalOut);
  // setup system clocks
  sysconSysOscControl(SYSCON, SYSOSCCTRL_BYPASS(0) | SYSOSCCTRL_FREQ_1_20MHZ);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
  crudeDelay(6000);
  sysconSysPllClockSelect(SYSCON, SYSPLLCLKSEL_SYSOSC);
  FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);
  sysconPowerDisable(SYSCON, PDRUNCFG_SYSPLL);
  sysconPllControl(SYSCON, 4, SYSPLLCTRL_POSTDIV_4);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSPLL);
  while (!sysconPllStatus(SYSCON))
    ;
  sysconMainClockDivider(SYSCON, 2);
  sysconMainClockSelect(SYSCON, MAINCLKSEL_PLL_OUT);
  // disable all unneeded clocks
  sysconDisableClocks(SYSCON, CLKCTRL_IOCON);
}
