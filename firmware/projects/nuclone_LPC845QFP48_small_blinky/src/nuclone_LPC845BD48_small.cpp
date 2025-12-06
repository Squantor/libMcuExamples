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
libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::usart::UartPolled<libmcuhw::Usart0Address, std::uint8_t> usartPeripheral;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.Isr();
}
}

auto systickIsrLambda = []() {
  gpio_peripheral.Toggle(led_pin);
};

void BoardInit(void) {
  // clock enables and resets
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1,
    0);
  // setup IOCON pins
  iocon_peripheral.Setup(xtal_in_pin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(xtal_out_pin, libmcull::iocon::PullModes::Inactive);
  swm_periperhal.Setup(xtal_in_pin, xtal_in_function);
  swm_periperhal.Setup(xtal_out_pin, xtal_out_function);
  // setup clock out test pin
  // swm_periperhal.Setup(test_pin, clock_out_function);
  // syscon_peripheral.setClockOutput(libmcull::syscon::clockOutSources::MAIN, 10u);
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // switch mainclock
  // syscon_peripheral.selectMainClock(libmcull::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  gpio_peripheral.SetOutput(led_pin);
  systickPeripheral.Init(nuclone_clock_config.GetSystemFreq() / ticksPerSecond);
  systickPeripheral.Start(systickIsrLambda);
}
