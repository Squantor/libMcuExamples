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
using xtalInPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using xtalOutPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
using testPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
using ledBlinkPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin08>;

// function types
using xtalInFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using xtalOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using clockOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::ClkOut>;

// pin instances
constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr testPinType testPin;
constexpr ledBlinkPinType ledPin;

// function instances
constexpr xtalInFunctionType xtalInFunction;
constexpr xtalOutFunctionType xtalOutFunction;
constexpr clockOutFunctionType clockOutFunction;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::usart::UartPolled<libmcuhw::Usart0Address, std::uint8_t> usartPeripheral;
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libmcuhw::clock::PeriClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0ClockConfig;

void boardInit(void);

#endif