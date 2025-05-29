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
libMcuHal::spi::SpiSyncPol<libMcuHw::spi0Address> spiPeripheral;
libMcuLL::sct::sct<libMcuHw::sct0Address> sctPeripheral;
libMcuLL::inmux::inmux<libMcuHw::inmuxAddress> inmuxPeripheral;

namespace sctLL = libMcuLL::sct;

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
                                            libMcuLL::syscon::peripheralClocks0::UART0 | libMcuLL::syscon::peripheralClocks0::SPI0 |
                                            libMcuLL::syscon::peripheralClocks0::SCT,
                                          0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(ws2812SpiSckPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(ws2812SpiMosiPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(ws2812DataPin, libMcuLL::iocon::pullModes::INACTIVE);

  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.setup(ws2812SpiSckPin, spiSckFunction);
  swmPeriperhal.setup(ws2812SpiMosiPin, spiMosiFunction);
  swmPeriperhal.setup(ws2812SpiSckPin, sctIn0Function);
  swmPeriperhal.setup(ws2812SpiMosiPin, sctIn1Function);
  swmPeriperhal.setup(ws2812DataPin, sctOut0Function);
  // setup crystal oscillator
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
  spiPeripheral.init<spi0ClockConfig>(800000, static_cast<std::uint32_t>(libMcuHal::spi::spiSlaveSelects::Select0), 4, 4);
  // setup sct, counter L not used, counter H used for WS2812 waveform generation
  sysconPeripheral.setupSctClock(libMcuLL::syscon::sctClockSources::MAIN, 1);
  // setup taken from AN11538 SCT cookbook
  sctPeripheral.init(sctLL::counterMode::SPLIT, false, false);
  // counts assume 60MHz clock
  sctPeripheral.setupMatch(sctLL::matcher::MATCH0, 2, sctLL::subCounter::UPPER);
  sctPeripheral.setupMatch(sctLL::matcher::MATCH1, 10, sctLL::subCounter::UPPER);
  sctPeripheral.setupMatch(sctLL::matcher::MATCH2, 21, sctLL::subCounter::UPPER);
  sctPeripheral.setupMatch(sctLL::matcher::MATCH3, 1500, sctLL::subCounter::UPPER);
  // input/output setup
  inmuxPeripheral.setup(libMcuLL::inmux::sctInputIndexes::SCT0_INMUX0, libMcuLL::inmux::sctInputSources::SCT_PIN0);
  inmuxPeripheral.setup(libMcuLL::inmux::sctInputIndexes::SCT0_INMUX1, libMcuLL::inmux::sctInputSources::SCT_PIN1);
  // event setup
  sctPeripheral.setupEvent(sctLL::events::EVENT0, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 0, sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::IO, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setupEvent(sctLL::events::EVENT1, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 1, sctLL::ioEventConditions::LOW, sctLL::eventCombineModes::AND, true, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setupEvent(sctLL::events::EVENT2, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 1, sctLL::ioEventConditions::HIGH, sctLL::eventCombineModes::AND, true, 1, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setupEvent(sctLL::events::EVENT3, sctLL::stateMasks::STATE0, sctLL::matcher::MATCH1, false, 0,
                           sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::MATCH, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setupEvent(sctLL::events::EVENT4, sctLL::stateMasks::STATE1, sctLL::matcher::MATCH2, false, 0,
                           sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::MATCH, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setupEvent(sctLL::events::EVENT5, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH3,
                           false, 0, sctLL::ioEventConditions::LOW, sctLL::eventCombineModes::MATCH, true, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setStartEvents(sctLL::eventMasks::EVENT0, sctLL::subCounter::UPPER);
  sctPeripheral.setLimitEvents(sctLL::eventMasks::EVENT0, sctLL::subCounter::UPPER);
  sctPeripheral.setStopEvents(sctLL::eventMasks::EVENT5, sctLL::subCounter::UPPER);
  sctPeripheral.setOutputSetEvents(sctLL::outputs::OUTPUT0, sctLL::eventMasks::EVENT0);
  sctPeripheral.setOutputClearEvents(sctLL::outputs::OUTPUT0, sctLL::eventMasks::EVENT3 | sctLL::eventMasks::EVENT4);
  sctPeripheral.start(sctLL::subCounter::UPPER);
}
