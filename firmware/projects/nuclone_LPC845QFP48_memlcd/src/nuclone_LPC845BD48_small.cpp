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

libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
libMcuLL::nvic::nvic<libMcuHw::nvicAddress, libMcuHw::scbAddress> nvicPeripheral;
libMcuHal::usart::uartSync<libMcuHw::usart0Address, libMcuHw::nvicAddress, char, 128> usartPeripheral;
libMcuHal::spi::spiSyncPol<libMcuHw::spi0Address> spiPeripheral;

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
  sysconPeripheral.powerPeripherals(libMcuLL::syscon::powerOptions::SYSOSC);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::syscon::peripheralClocks0::SWM | libMcuLL::syscon::peripheralClocks0::IOCON |
                                            libMcuLL::syscon::peripheralClocks0::GPIO0 |
                                            libMcuLL::syscon::peripheralClocks0::GPIO1 |
                                            libMcuLL::syscon::peripheralClocks0::UART0 | libMcuLL::syscon::peripheralClocks0::SPI0,
                                          0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispSpiSckPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispSpiMosiPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(dispSpiCsPin, libMcuLL::iocon::pullModes::INACTIVE);
  gpioPeripheral.high(dispEmdPin);
  gpioPeripheral.output(dispEmdPin);
  gpioPeripheral.high(dispDonPin);
  gpioPeripheral.output(dispDonPin);
  gpioPeripheral.high(dispEinPin);
  gpioPeripheral.output(dispEinPin);

  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.setup(dispSpiCsPin, spiCsFunction);
  swmPeriperhal.setup(dispSpiSckPin, spiSckFunction);
  swmPeriperhal.setup(dispSpiMosiPin, spiMosiFunction);
  // setup crystal oscillator
  // libMcuHw::clock::configureClocks<sysconPeripheral, diySolderClockConfig>();
  sysconPeripheral.configureMcuClocks<nucloneClockConfig>();
  // setup systick
  systickPeripheral.init(nucloneClockConfig.getSystemFreq() / TICKS_PER_S);
  systickPeripheral.start(systickIsrLambda);
  // setup UART
  sysconPeripheral.peripheralClockSource(libMcuLL::syscon::clockSourceSelects::UART0, libMcuLL::syscon::clockSources::MAIN);
  usartPeripheral.init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libMcuHw::interrupts::uart0);
  // setup spi
  sysconPeripheral.peripheralClockSource(libMcuLL::syscon::clockSourceSelects::SPI0, libMcuLL::syscon::clockSources::MAIN);
  spiPeripheral.init<spi0ClockConfig>(1000000, static_cast<std::uint32_t>(libMcuHal::spi::spiSlaveSelects::Select0), 3, 3);
  std::array<std::uint16_t, 8> data;
  data.fill(0);
  data[0] = 0x0801;
  for (std::size_t i = 1; i < data.size() - 1; i++) {
    data[i] = i;
  }
  spiPeripheral.write<decltype(data)::value_type>(data, 16u, libMcuHal::spi::spiSlaveSelects::Select0, true, true);
}
