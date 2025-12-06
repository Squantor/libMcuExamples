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
libmcuhal::i2c::i2cSyncPol<libmcuhw::i2c0Address, 128> i2cPeripheral;
libMcuDriver::SSD1306::generic128x32 testDisplay;
libMcuDriver::SSD1306::SSD1306<i2cPeripheral, SSD1306_I2C_ADDRESS, testDisplay> SSD1306;
libMcuMid::display::displayDirSSD1306<testDisplay, SSD1306> display;
sqEmbedded::fonts::mono6x8RowFlip font;
libMcuMid::display::graphicsTerminal<display, font> displayTerminal;

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
      libmcull::syscon::peripheral_clocks_0::UART0 | libmcull::syscon::peripheral_clocks_0::I2C0,
    0);
  // setup pins
  iocon_peripheral.Setup(xtal_in_pin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(xtal_out_pin, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(bootloadPin, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(debugUartRxPin, libmcull::iocon::PullModes::PULLUP);
  iocon_peripheral.Setup(debugUartTxPin, libmcull::iocon::PullModes::Inactive);
  swm_periperhal.Setup(xtal_in_pin, xtal_in_function);
  swm_periperhal.Setup(xtal_out_pin, xtal_out_function);
  swm_periperhal.Setup(debugUartRxPin, uartDebugRxFunction);
  swm_periperhal.Setup(debugUartTxPin, uartDebugTxFunction);
  swm_periperhal.Setup(i2cSclPin, i2cSclFunction);
  swm_periperhal.Setup(i2cSdaPin, i2cSdaFunction);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<syscon_peripheral, diySolderClockConfig>();
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // setup systick
  systickPeripheral.Init(nuclone_clock_config.GetSystemFreq() / TICKS_PER_S);
  systickPeripheral.Start(systickIsrLambda);
  // setup UART
  syscon_peripheral.peripheralClockSource(libmcull::syscon::clockSourceSelects::UART0, libmcull::syscon::clockSources::MAIN);
  usartPeripheral.Init<uart0ClockConfig>(115200);
  nvicPeripheral.enable(libmcuhw::interrupts::uart0);
  // setup I2C
  syscon_peripheral.peripheralClockSource(libmcull::syscon::clockSourceSelects::I2C0, libmcull::syscon::clockSources::MAIN);
  // i2cPeripheral.InitMaster<i2c0ClockConfig>(100000, 100);
  i2cPeripheral.Init<i2c0ClockConfig>(400000, 100);
  // setup SSD1306 display
  SSD1306.Init();
  display.fill(0x00);
}
