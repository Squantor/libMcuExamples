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
libMcuHal::i2c::i2cSyncPol<libMcuHw::i2c0Address, 128> i2cPeripheral;
libMcuDriver::SSD1306::generic128x32 testDisplay;
libMcuDriver::SSD1306::SSD1306<i2cPeripheral, SSD1306_I2C_ADDRESS, testDisplay> SSD1306;
libMcuMiddleware::display::displayDirSSD1306<testDisplay, SSD1306> display;

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
                                            libMcuLL::syscon::peripheralClocks0::UART0 | libMcuLL::syscon::peripheralClocks0::I2C0,
                                          0);
  // setup pins
  ioconPeripheral.setup(xtalInPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcuLL::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(bootloadPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartRxPin, libMcuLL::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(debugUartTxPin, libMcuLL::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  swmPeriperhal.setup(debugUartRxPin, uartDebugRxFunction);
  swmPeriperhal.setup(debugUartTxPin, uartDebugTxFunction);
  swmPeriperhal.setup(i2cSclPin, i2cSclFunction);
  swmPeriperhal.setup(i2cSdaPin, i2cSdaFunction);
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
  // setup I2C
  sysconPeripheral.peripheralClockSource(libMcuLL::syscon::clockSourceSelects::I2C0, libMcuLL::syscon::clockSources::MAIN);
  // i2cPeripheral.initMaster<i2c0ClockConfig>(100000, 100);
  i2cPeripheral.init<i2c0ClockConfig>(400000, 100);
  // setup SSD1306 display
  SSD1306.init();
  display.fill(0x55);
  std::span<const std::uint8_t> bitmap = sqEmbedded::fonts::mono8x8RowFlip.fontBitmap.subspan(264, 32);
  display.writeBlock(16, 8, 32, 16, bitmap);
}
