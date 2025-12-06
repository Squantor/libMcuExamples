/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code common for small LPC845BD48 nuclones
 */
#ifndef NUCLONE_LPC845BD48_SMALL_NUCLONE_COMMON_HPP
#define NUCLONE_LPC845BD48_SMALL_NUCLONE_COMMON_HPP

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>

// pin types
// Crystal osillator pins
using PinXtalIn = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using PinXtalOut = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// uart pins
using PinDebugUartTx = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using PinDebugUartRx = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
// bootloader entry switch pin
using PinBootloader = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;

// pin function types
using FunctionXtalIn = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using FunctionXtalOut = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using FunctionUartDebugTx = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0TxOut>;
using FunctionUartDebugRx = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0RxIn>;

// pin instances
constexpr PinXtalIn xtal_in_pin;
constexpr PinXtalOut xtal_out_pin;
constexpr PinBootloader bootloadPin;
constexpr PinDebugUartTx debugUartTxPin;
constexpr PinDebugUartRx debugUartRxPin;

// function instances
constexpr FunctionXtalIn xtal_in_function;
constexpr FunctionXtalOut xtal_out_function;
constexpr FunctionUartDebugTx uartDebugTxFunction;
constexpr FunctionUartDebugRx uartDebugRxFunction;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 64> usart_peripheral_ll;
extern libmcuhal::usart::UartInterrupt<usart_peripheral_ll, char> usart_peripheral;
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0_clock_config;

void BoardInit(void);

#endif