/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file SSD1306_i2c.hpp
 * @brief driver for the SSD1306 OLED display via I2C
 */
#ifndef SSD1306_I2C_HPP
#define SSD1306_I2C_HPP

#include "SSD1306.hpp"
#include <span>

namespace libMcuDriver::SSD1306 {
namespace i2c = libMcuLL::i2c;

template <auto &i2cLL, const libMcu::i2cDeviceAddress &i2cAddress, auto &config>
struct SSD1306 {
  void init() {
    sendCommands(config.initCommands);
  }

  void sendCommands(std::span<const std::uint8_t> commands) {
    libMcu::results result;
    result = i2cLL.masterWriteStart(i2cAddress, 0x00);
    if (result != libMcu::results::NO_ERROR)
      goto i2cStop;
    result = i2cLL.masterWriteContinue(commands);
    if (result != libMcu::results::NO_ERROR)
      goto i2cStop;

  i2cStop:
    i2cLL.masterStop();
  }
};

}  // namespace libMcuDriver::SSD1306

#endif