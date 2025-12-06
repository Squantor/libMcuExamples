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
libmcuhal::usart::uartSync<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
libmcuhal::spi::SpiSyncPol<libmcuhw::spi0Address> spiPeripheral;
libmcull::sct::sct<libmcuhw::sct0Address> sctPeripheral;
libmcull::inmux::inmux<libmcuhw::inmuxAddress> inmuxPeripheral;

namespace sctLL = libmcull::sct;

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
      libmcull::syscon::peripheral_clocks_0::UART0 | libmcull::syscon::peripheral_clocks_0::SPI0 |
      libmcull::syscon::peripheral_clocks_0::SCT,
    0);
  // setup pins
  iocon_peripheral.Setup(pin_xtal_in, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_xtal_out, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_bootload_switch, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(pin_debug_uart_rx, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(pin_debug_uart_tx, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(ws2812SpiSckPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(ws2812SpiMosiPin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(ws2812DataPin, libmcull::iocon::PullModes::Inactive);

  swm_periperhal.Setup(pin_xtal_in, function_xtal_in);
  swm_periperhal.Setup(pin_xtal_out, function_xtal_out);
  swm_periperhal.Setup(pin_debug_uart_rx, function_debug_uart_rx);
  swm_periperhal.Setup(pin_debug_uart_tx, function_debug_uart_tx);
  swm_periperhal.Setup(ws2812SpiSckPin, spiSckFunction);
  swm_periperhal.Setup(ws2812SpiMosiPin, spiMosiFunction);
  swm_periperhal.Setup(ws2812SpiSckPin, sctIn0Function);
  swm_periperhal.Setup(ws2812SpiMosiPin, sctIn1Function);
  swm_periperhal.Setup(ws2812DataPin, sctOut0Function);
  // setup crystal oscillator
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // setup systick
  systickPeripheral.Init(nuclone_clock_config.GetSystemFreq() / TICKS_PER_S);
  systickPeripheral.Start(systickIsrLambda);
  // setup UART
  syscon_peripheral.peripheralClockSource(libmcull::syscon::clockSourceSelects::UART0, libmcull::syscon::clockSources::MAIN);
  usartPeripheral.Init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::interrupts::uart0);
  // setup spi
  syscon_peripheral.peripheralClockSource(libmcull::syscon::clockSourceSelects::SPI0, libmcull::syscon::clockSources::MAIN);
  spiPeripheral.Init<spi0ClockConfig>(800000, static_cast<std::uint32_t>(libmcuhal::spi::spiSlaveSelects::Select0), 4, 4);
  // setup sct, counter L not used, counter H used for WS2812 waveform generation
  syscon_peripheral.SetupSctClock(libmcull::syscon::sctClockSources::MAIN, 1);
  // setup taken from AN11538 SCT cookbook
  sctPeripheral.Init(sctLL::counterMode::SPLIT, false, false);
  // counts assume 60MHz clock
  sctPeripheral.SetupMatch(sctLL::matcher::MATCH0, 2, sctLL::subCounter::UPPER);
  sctPeripheral.SetupMatch(sctLL::matcher::MATCH1, 10, sctLL::subCounter::UPPER);
  sctPeripheral.SetupMatch(sctLL::matcher::MATCH2, 21, sctLL::subCounter::UPPER);
  sctPeripheral.SetupMatch(sctLL::matcher::MATCH3, 1500, sctLL::subCounter::UPPER);
  // input/output setup
  inmuxPeripheral.Setup(libmcull::inmux::sctInputIndexes::SCT0_INMUX0, libmcull::inmux::sctInputSources::SCT_PIN0);
  inmuxPeripheral.Setup(libmcull::inmux::sctInputIndexes::SCT0_INMUX1, libmcull::inmux::sctInputSources::SCT_PIN1);
  // event setup
  sctPeripheral.SetupEvent(sctLL::events::EVENT0, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 0, sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::IO, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.SetupEvent(sctLL::events::EVENT1, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 1, sctLL::ioEventConditions::LOW, sctLL::eventCombineModes::AND, true, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.SetupEvent(sctLL::events::EVENT2, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH0,
                           false, 1, sctLL::ioEventConditions::HIGH, sctLL::eventCombineModes::AND, true, 1, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.SetupEvent(sctLL::events::EVENT3, sctLL::stateMasks::STATE0, sctLL::matcher::MATCH1, false, 0,
                           sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::MATCH, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.SetupEvent(sctLL::events::EVENT4, sctLL::stateMasks::STATE1, sctLL::matcher::MATCH2, false, 0,
                           sctLL::ioEventConditions::RISE, sctLL::eventCombineModes::MATCH, false, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.SetupEvent(sctLL::events::EVENT5, sctLL::stateMasks::STATE0 | sctLL::stateMasks::STATE1, sctLL::matcher::MATCH3,
                           false, 0, sctLL::ioEventConditions::LOW, sctLL::eventCombineModes::MATCH, true, 0, false,
                           sctLL::eventCountingDirections::UP, sctLL::subCounter::UPPER);
  sctPeripheral.setStartEvents(sctLL::eventMasks::EVENT0, sctLL::subCounter::UPPER);
  sctPeripheral.setLimitEvents(sctLL::eventMasks::EVENT0, sctLL::subCounter::UPPER);
  sctPeripheral.setStopEvents(sctLL::eventMasks::EVENT5, sctLL::subCounter::UPPER);
  sctPeripheral.setOutputSetEvents(sctLL::outputs::OUTPUT0, sctLL::eventMasks::EVENT0);
  sctPeripheral.setOutputClearEvents(sctLL::outputs::OUTPUT0, sctLL::eventMasks::EVENT3 | sctLL::eventMasks::EVENT4);
  sctPeripheral.Start(sctLL::subCounter::UPPER);
}
