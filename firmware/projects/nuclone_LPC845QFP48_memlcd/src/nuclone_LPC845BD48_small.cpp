/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#include <nuclone_LPC845BD48_small.hpp>

libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvicPeripheral;
libmcuhal::usart::SyncUart<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
libmcuhal::spi::SpiSyncPol<libmcuhw::spi0Address> spiPeripheral;
libMcuDrv::memlcd::memlcd<TestDisplay, libmcuhal::spi::spiSlaveSelects::Select0, spiPeripheral> memlcdDriver;
libMcuMid::display::displayMemlcd<TestDisplay, memlcdDriver> display;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}

void USART0_IRQHandler(void) {
  usartPeripheral.isr();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void boardInit(void) {
  ticks = 0;
  // clock, power and reset enables/clears
  syscon_peripheral.PowerPeripherals(libmcull::syscon::powerOptions::SYSOSC);
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::UART0 | libmcull::syscon::peripheral_clocks_0::SPI0,
    0);
  // setup pins
  iocon_peripheral.Setup(xtal_in_pin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(xtal_out_pin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(bootloadPin, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(debugUartRxPin, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(debugUartTxPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(ws2812SpiSckPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(ws2812SpiMosiPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(dispSpiCsPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(dispEmdPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(dispDonPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(dispEinPin, libmcull::iocon::PullModes::Inactive);
  // serial based com pulsing
  gpio_peripheral.low(dispEmdPin);
  gpio_peripheral.Output(dispEmdPin);
  // gpio_peripheral.high(dispDonPin);
  // gpio_peripheral.Output(dispDonPin);
  // gpio_peripheral.high(dispEinPin);
  // gpio_peripheral.Output(dispEinPin);

  swm_periperhal.Setup(xtal_in_pin, xtal_in_function);
  swm_periperhal.Setup(xtal_out_pin, xtal_out_function);
  swm_periperhal.Setup(debugUartRxPin, uartDebugRxFunction);
  swm_periperhal.Setup(debugUartTxPin, uartDebugTxFunction);
  swm_periperhal.Setup(dispSpiCsPin, spiCsFunction);
  swm_periperhal.Setup(ws2812SpiSckPin, spiSckFunction);
  swm_periperhal.Setup(ws2812SpiMosiPin, spiMosiFunction);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<syscon_peripheral, diySolderClockConfig>();
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // setup systick
  systickPeripheral.Init(nuclone_clock_config.GetSystemFreq() / TICKS_PER_S);
  systickPeripheral.Start(systickIsrLambda);
  // setup UART
  syscon_peripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::UART0, libmcull::syscon::clockSources::MAIN);
  usartPeripheral.Init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::Interrupts::uart0);
  // setup spi
  syscon_peripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::SPI0, libmcull::syscon::clockSources::MAIN);
  spiPeripheral.Init<spi0ClockConfig>(1000000, static_cast<std::uint32_t>(libmcuhal::spi::spiSlaveSelects::Select0), 4, 4);
  display.Init();
  display.update();
}
