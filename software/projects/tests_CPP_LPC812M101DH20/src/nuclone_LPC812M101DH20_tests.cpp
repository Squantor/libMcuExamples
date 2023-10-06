/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC812M101DH20_tests.hpp>

libMcuLL::sw::iocon::iocon<libMcuLL::hw::IOCON_cpp> ioconPeripheral;
libMcuLL::sw::swm::swm<libMcuLL::hw::SWM_cpp> swmPeriperhal;
libMcuLL::sw::gpio::gpio<libMcuLL::hw::GPIO_cpp> gpioPeripheral;
libMcuLL::sw::spi::spiSync<libMcuLL::hw::SPI0_cpp, libMcuLL::sw::spi::chipEnables> spiPeripheral;
libMcuLL::sw::syscon::syscon<libMcuLL::hw::SYSCON_cpp> sysconPeripheral;
libMcuLL::sw::usart::usart<libMcuLL::hw::USART0_cpp> usartPeripheral;
libMcuLL::sw::i2c::i2c<libMcuLL::hw::I2C0_cpp> i2cPeripheral;

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
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_SWM | libMcuLL::sw::syscon::CLOCK_IOCON |
                                          libMcuLL::sw::syscon::CLOCK_GPIO);
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::hw::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::hw::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  // setup system clocks
  sysconPeripheral.setSysOscControl(libMcuLL::hw::syscon::SYSOSCCTRL::NO_BYPASS | libMcuLL::hw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(libMcuLL::sw::syscon::POWER_SYSOSC);
  crudeDelay(6000);
  sysconPeripheral.selectPllClock(libMcuLL::sw::syscon::PLLCLK_SYSOSC);
  FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);
  sysconPeripheral.depowerPeripherals(libMcuLL::sw::syscon::POWER_SYSPLL);
  sysconPeripheral.setSystemPllControl(4, libMcuLL::sw::syscon::PLLPOSTDIV_4);
  sysconPeripheral.powerPeripherals(libMcuLL::sw::syscon::POWER_SYSPLL);
  while (!sysconPeripheral.getSystemPllStatus())
    ;
  sysconPeripheral.setSystemClockDivider(2);
  sysconPeripheral.selectMainClock(libMcuLL::sw::syscon::MAINCLK_PLL_OUT);
  // disable all unneeded clocks
  sysconPeripheral.disablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_IOCON);
}
