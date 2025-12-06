/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief definitions for LPC845 small nuclone LL tester
 */
#ifndef NUCLONE_LPC845BD48_SMALL_LL_HPP
#define NUCLONE_LPC845BD48_SMALL_LL_HPP

#include <nxp/libmcu_LPC845M301BD48_ll.hpp>

constexpr inline std::uint32_t ticksPerSecond{10u};

// pin types
// Crystal osillator pins
using XtalInPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using XtalOutPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
using TestPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
using LedBlinkPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin08>;

// function types
using XtalInFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using XtalOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using ClockOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::ClkOut>;

// pin instances
constexpr XtalInPinType xtal_in_pin;
constexpr XtalOutPinType xtal_out_pin;
constexpr TestPinType test_pin;
constexpr LedBlinkPinType led_pin;

// function instances
constexpr XtalInFunctionType xtal_in_function;
constexpr XtalOutFunctionType xtal_out_function;
constexpr ClockOutFunctionType clock_out_function;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::usart::UartPolled<libmcuhw::Usart0Address, std::uint8_t> usart_peripheral;
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0_clock_config;

void BoardInit(void);

#endif