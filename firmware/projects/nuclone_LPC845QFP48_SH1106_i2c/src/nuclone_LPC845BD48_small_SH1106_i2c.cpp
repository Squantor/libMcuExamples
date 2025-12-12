/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#include <nuclone_LPC845BD48_small_SH1106_i2c.hpp>

libmcu::I2cDeviceAddress SH1106_i2c_address{0x3C};

libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvic_peripheral;
libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 64> usart_peripheral_ll;
libmcull::i2c::I2cInterrupt<libmcuhw::I2c0Address> i2c_peripheral_ll;
libmcuhal::usart::Uart<usart_peripheral_ll, char> usart_peripheral;
libmcuhal::i2c::I2c<i2c_peripheral_ll> i2c_peripheral;
libMcuDriver::SH1106::Generic128x64 display_config;
libMcuDriver::SH1106::SH1106<i2c_peripheral, SH1106_i2c_address, display_config> display;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systick_peripheral.Isr();
}

void USART0_IRQHandler(void) {
  usart_peripheral_ll.InterruptHandler();
}
void I2C0_IRQHandler(void) {
  i2c_peripheral_ll.InterruptHandler();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void BoardInit(void) {
  ticks = 0;
  syscon_peripheral.PowerPeripherals(libmcull::syscon::power_options::SysOsc);
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::Uart0 | libmcull::syscon::peripheral_clocks_0::I2c0,
    0);
  syscon_peripheral.ResetPeripherals(libmcull::syscon::peripheral_resets_0::I2c0, 0);
  iocon_peripheral.Setup(pin_xtal_in, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_xtal_out, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_bootload_switch, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_rx, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_tx, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_i2c_scl, libmcull::iocon::I2cModes::Standard);
  iocon_peripheral.Setup(pin_i2c_sda, libmcull::iocon::I2cModes::Standard);
  swm_periperhal.Setup(pin_xtal_in, function_xtal_in);
  swm_periperhal.Setup(pin_xtal_out, function_xtal_out);
  swm_periperhal.Setup(pin_debug_uart_rx, function_debug_uart_rx);
  swm_periperhal.Setup(pin_debug_uart_tx, function_debug_uart_tx);
  swm_periperhal.Setup(pin_i2c_scl, function_main_i2c_scl);
  swm_periperhal.Setup(pin_i2c_sda, function_main_i2c_sda);
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::Uart0, libmcull::syscon::ClockSources::Main);
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::I2c0, libmcull::syscon::ClockSources::Main);
  systick_peripheral.Init(nuclone_clock_config.GetSystemFreq() / ticksPerSecond);
  systick_peripheral.Start(systickIsrLambda);
  nvic_peripheral.Enable(libmcuhw::Interrupts::Uart0);
  nvic_peripheral.Enable(libmcuhw::Interrupts::I2c0);
  usart_peripheral.Init<uart0_clock_config>(115200);
  i2c_peripheral.Init<i2c0_clock_config>(400000, 1000);
  // delay before we turn on screen
  while (ticks < 10)
    ;
  display.Init();
}
