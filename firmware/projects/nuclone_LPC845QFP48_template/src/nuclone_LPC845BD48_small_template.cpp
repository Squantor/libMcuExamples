/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#include <nuclone_LPC845BD48_small_template.hpp>

libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
libmcull::systick::Systick<libmcuhw::SystickAddress> systick_peripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvic_peripheral;
libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 64> usart_peripheral_ll;
libmcuhal::usart::UartInterrupt<usart_peripheral_ll, char> usart_peripheral;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systick_peripheral.Isr();
}

void USART0_IRQHandler(void) {
  usart_peripheral_ll.InterruptHandler();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
};

void BoardInit(void) {
  ticks = 0;
  // clock, power and reset enables/clears
  syscon_peripheral.PowerPeripherals(libmcull::syscon::power_options::SysOsc);
  syscon_peripheral.EnablePeripheralClocks(
    libmcull::syscon::peripheral_clocks_0::Swm | libmcull::syscon::peripheral_clocks_0::Iocon |
      libmcull::syscon::peripheral_clocks_0::Gpio0 | libmcull::syscon::peripheral_clocks_0::Gpio1 |
      libmcull::syscon::peripheral_clocks_0::Uart0,
    0);
  // setup pins
  iocon_peripheral.Setup(pin_xtal_in, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_xtal_out, libmcull::iocon::PullModes::Inactive);
  iocon_peripheral.Setup(pin_bootload_switch, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_rx, libmcull::iocon::PullModes::Pullup);
  iocon_peripheral.Setup(pin_debug_uart_tx, libmcull::iocon::PullModes::Inactive);
  swm_periperhal.Setup(pin_xtal_in, function_xtal_in);
  swm_periperhal.Setup(pin_xtal_out, function_xtal_out);
  swm_periperhal.Setup(pin_debug_uart_rx, function_debug_uart_rx);
  swm_periperhal.Setup(pin_debug_uart_tx, function_debug_uart_tx);
  // setup crystal oscillator
  // libmcuhw::clock::configureClocks<syscon_peripheral, diySolderClockConfig>();
  syscon_peripheral.ConfigureMcuClocks<nuclone_clock_config>();
  // setup systick
  systick_peripheral.Init(nuclone_clock_config.GetSystemFreq() / TICKS_PER_S);
  systick_peripheral.Start(systickIsrLambda);
  // setup UART
  syscon_peripheral.PeripheralClockSource(libmcull::syscon::ClockSourceSelects::Uart0, libmcull::syscon::ClockSources::Main);
  usart_peripheral.Init<uart0_clock_config>(115200);
  nvic_peripheral.Enable(libmcuhw::Interrupts::Uart0);
}
