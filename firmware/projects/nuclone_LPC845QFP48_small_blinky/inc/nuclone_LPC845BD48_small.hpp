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
using xtalInPinType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN08>;
using xtalOutPinType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN09>;
using testPinType = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN05>;
using ledBlinkPinType = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN08>;

// function types
using xtalInFunctionType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALOUT>;
using clockOutFunctionType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::CLKOUT_O>;

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
extern libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
extern libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
extern libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
extern libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
extern libMcuLL::usart::usart<libMcuHw::usart0Address, std::uint8_t> usartPeripheral;
constexpr inline libMcuHw::clock::mcuClockConfig<libMcuHw::clock::clockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::UART0,
                                                  libMcuHw::clock::periSource::MAIN>
  uart0ClockConfig;

void boardInit(void);

#endif