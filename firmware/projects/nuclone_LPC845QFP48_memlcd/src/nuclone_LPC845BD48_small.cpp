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

libmcull::iocon::Iocon<libmcuhw::ioconAddress> ioconPeripheral;
libmcull::swm::Swm<libmcuhw::swmAddress> swmPeriperhal;
libmcull::gpio::gpio<libmcuhw::gpioAddress> gpioPeripheral;
libmcull::syscon::Syscon<libmcuhw::sysconAddress> sysconPeripheral;
libmcull::systick::systick<libmcuhw::systickAddress> systickPeripheral;
libmcull::nvic::nvic<libmcuhw::nvicAddress, libmcuhw::scbAddress> nvicPeripheral;
libmcuhal::usart::SyncUart<libmcuhw::usart0Address, libmcuhw::nvicAddress, char, 128> usartPeripheral;
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
  sysconPeripheral.enablePeripheralClocks(libmcull::syscon::peripheralClocks0::SWM | libmcull::syscon::peripheralClocks0::IOCON |
                                            libmcull::syscon::peripheralClocks0::GPIO0 |
                                            libmcull::syscon::peripheralClocks0::GPIO1 |
                                            libmcull::syscon::peripheralClocks0::UART0 | libmcull::syscon::peripheralClocks0::SPI0,
                                          0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libmcull::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libmcull::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(ws2812SpiSckPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(ws2812SpiMosiPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispSpiCsPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispEmdPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispDonPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispEinPin, libmcull::iocon::pullModes::INACTIVE);
  // serial based com pulsing
  gpioPeripheral.low(dispEmdPin);
  gpioPeripheral.output(dispEmdPin);
  // gpioPeripheral.high(dispDonPin);
  // gpioPeripheral.output(dispDonPin);
  // gpioPeripheral.high(dispEinPin);
  // gpioPeripheral.output(dispEinPin);

  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.setup(dispSpiCsPin, spiCsFunction);
  swmPeriperhal.setup(ws2812SpiSckPin, spiSckFunction);
  swmPeriperhal.setup(ws2812SpiMosiPin, spiMosiFunction);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<sysconPeripheral, diySolderClockConfig>();
  sysconPeripheral.configureMcuClocks<nucloneClockConfig>();
  // setup systick
  systickPeripheral.init(nucloneClockConfig.getSystemFreq() / TICKS_PER_S);
  systickPeripheral.start(systickIsrLambda);
  // setup UART
  sysconPeripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::UART0, libmcull::syscon::clockSources::MAIN);
  usartPeripheral.init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::Interrupts::uart0);
  // setup spi
  sysconPeripheral.peripheralClockSource(libmcull::syscon::ClockSourceSelects::SPI0, libmcull::syscon::clockSources::MAIN);
  spiPeripheral.init<spi0ClockConfig>(1000000, static_cast<std::uint32_t>(libmcuhal::spi::spiSlaveSelects::Select0), 4, 4);
  display.init();
  display.update();
}
