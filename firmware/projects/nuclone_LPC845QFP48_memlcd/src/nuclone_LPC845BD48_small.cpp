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

libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
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
  sysconPeripheral.powerPeripherals(libmcull::syscon::powerOptions::SYSOSC);
  sysconPeripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::UART0 | libmcull::syscon::peripheral_clocks_0::SPI0,
    0);
  // setup pins
  ioconPeripheral.Setup(xtalInPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(xtalOutPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(bootloadPin, libmcull::iocon::PullModes::PULLUP);
  ioconPeripheral.Setup(debugUartRxPin, libmcull::iocon::PullModes::PULLUP);
  ioconPeripheral.Setup(debugUartTxPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(ws2812SpiSckPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(ws2812SpiMosiPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(dispSpiCsPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(dispEmdPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(dispDonPin, libmcull::iocon::PullModes::Inactive);
  ioconPeripheral.Setup(dispEinPin, libmcull::iocon::PullModes::Inactive);
  // serial based com pulsing
  gpioPeripheral.low(dispEmdPin);
  gpioPeripheral.Output(dispEmdPin);
  // gpioPeripheral.high(dispDonPin);
  // gpioPeripheral.Output(dispDonPin);
  // gpioPeripheral.high(dispEinPin);
  // gpioPeripheral.Output(dispEinPin);

  swmPeriperhal.Setup(xtalInPin, xtalInFunction);
  swmPeriperhal.Setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.Setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.Setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.Setup(dispSpiCsPin, spiCsFunction);
  swmPeriperhal.Setup(ws2812SpiSckPin, spiSckFunction);
  swmPeriperhal.Setup(ws2812SpiMosiPin, spiMosiFunction);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<sysconPeripheral, diySolderClockConfig>();
  sysconPeripheral.ConfigureMcuClocks<nucloneClockConfig>();
  // setup systick
  systickPeripheral.Init(nucloneClockConfig.GetSystemFreq() / TICKS_PER_S);
  systickPeripheral.Start(systickIsrLambda);
  // setup UART
  sysconPeripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::UART0, libmcull::syscon::clockSources::MAIN);
  usartPeripheral.Init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::Interrupts::uart0);
  // setup spi
  sysconPeripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::SPI0, libmcull::syscon::clockSources::MAIN);
  spiPeripheral.Init<spi0ClockConfig>(1000000, static_cast<std::uint32_t>(libmcuhal::spi::spiSlaveSelects::Select0), 4, 4);
  display.Init();
  display.update();
}
