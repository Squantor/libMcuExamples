/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for modifications to small LPC845BD48 nuclone
 */
#ifndef NUCLONE_LPC845BD48_SMALL_NUCLONE_TEMPLATE_HPP
#define NUCLONE_LPC845BD48_SMALL_NUCLONE_TEMPLATE_HPP

#include <nuclone_LPC845BD48_small_common.hpp>

constexpr inline std::uint32_t ticksPerSecond{100u};

// pin types specific for blinky
using PinClockOut = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;
using PinLedBlink = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin08>;

// pin function types specific for blinky
using FunctionClockOut = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::ClkOut>;

// pin instances specific for blinky
constexpr PinClockOut pin_clock_out;
constexpr PinLedBlink pin_blink_led;

// function instances specific for blinky
constexpr FunctionClockOut function_clock_out;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

/**
 * @brief initializes the board
 */
void BoardInit(void);

#endif