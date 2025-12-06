/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for modifications to small LPC845BD48 nuclone
 */
#ifndef NUCLONE_LPC845BD48_SMALL_NUCLONE_SH1106_I2C_HPP
#define NUCLONE_LPC845BD48_SMALL_NUCLONE_SH1106_I2C_HPP

#include <nuclone_LPC845BD48_small_common.hpp>
#include <drivers/SH1106_i2c.hpp>

// SDA pin with 2.2K pull up resistor
using PinI2cSda = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin11>;
// SCL pin with 2.2K pull up resistor
using PinI2cScl = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin10>;

using FunctionMainI2cSda = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SdaInOut>;
using FunctionMainI2cScl = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SclInOut>;

constexpr PinI2cScl pin_i2c_scl;
constexpr PinI2cSda pin_i2c_sda;

constexpr FunctionMainI2cScl function_main_i2c_scl;
constexpr FunctionMainI2cSda function_main_i2c_sda;

constexpr libmcu::I2cDeviceAddress SH1106_i2c_address{0x3C};

constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::I2C0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  i2c0_clock_config;

extern libmcull::i2c::I2cInterrupt<libmcuhw::I2c0Address> i2c_peripheral_ll;
extern libmcuhal::i2c::I2cInterrupt<i2c_peripheral_ll> i2c_peripheral;
extern libMcuDriver::SH1106::Generic128x64 display_config;
extern libMcuDriver::SH1106::SH1106<i2c_peripheral, SH1106_i2c_address, display_config> display;

constexpr inline std::uint32_t ticksPerSecond{100u};

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

/**
 * @brief initializes the board
 */
void BoardInit(void);

#endif