/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file nuclone_LPC845BD48_small.cpp
 * @brief Board setup file for small LPC845 nuclone
 */
#include <nuclone_LPC845BD48_small.hpp>

namespace clocks = libmcuhw::clock;

libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvicPeripheral;
libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
libmcull::usart::UartPolled<libmcuhw::Usart0Address, std::uint8_t> usartPeripheral;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.Isr();
}
}

auto systickIsrLambda = []() {
  gpioPeripheral.Toggle(ledPin);
};

void boardInit(void) {
  // clock enables and resets
  sysconPeripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1,
    0);
  // setup IOCON pins
  ioconPeripheral.Setup(xtalInPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(xtalOutPin, libmcull::iocon::PullModes::Inactive);
  swmPeriperhal.Setup(xtalInPin, xtalInFunction);
  swmPeriperhal.Setup(xtalOutPin, xtalOutFunction);
  // setup clock out test pin
  // swmPeriperhal.Setup(testPin, clockOutFunction);
  // sysconPeripheral.setClockOutput(libmcull::syscon::clockOutSources::MAIN, 10u);
  sysconPeripheral.ConfigureMcuClocks<nucloneClockConfig>();
  // switch mainclock
  // sysconPeripheral.selectMainClock(libmcull::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  gpioPeripheral.SetOutput(ledPin);
  systickPeripheral.Init(nucloneClockConfig.GetSystemFreq() / ticksPerSecond);
  systickPeripheral.Start(systickIsrLambda);
}
