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

namespace clocks = libMcuHw::clock;

libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
libMcuLL::nvic::nvic<libMcuHw::nvicAddress, libMcuHw::scbAddress> nvicPeripheral;
libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
libMcuLL::usart::usart<libMcuHw::usart0Address, std::uint8_t> usartPeripheral;

static constexpr libMcu::hwAddressType systickAddress = libMcuHw::systickAddress;
libMcuHw::systick::systick *const systickDutRegisters{reinterpret_cast<libMcuHw::systick::systick *>(systickAddress)};

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}
}

auto systickIsrLambda = []() {
  gpioPeripheral.toggle(ledPin);
};

void boardInit(void) {
  // clock enables and resets
  sysconPeripheral.enablePeripheralClocks(libMcuLL::syscon::peripheralClocks0::SWM | libMcuLL::syscon::peripheralClocks0::IOCON |
                                            libMcuLL::syscon::peripheralClocks0::GPIO0 | libMcuLL::syscon::peripheralClocks0::GPIO1,
                                          0);
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  // setup clock out test pin
  // swmPeriperhal.setup(testPin, clockOutFunction);
  // sysconPeripheral.setClockOutput(libMcuLL::syscon::clockOutSources::MAIN, 10u);
  sysconPeripheral.configureMcuClocks<nucloneClockConfig>();
  // switch mainclock
  // sysconPeripheral.selectMainClock(libMcuLL::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  gpioPeripheral.output(ledPin);
  systickPeripheral.init(nucloneClockConfig.getSystemFreq() / ticksPerSecond);
  systickPeripheral.start(systickIsrLambda);
}
