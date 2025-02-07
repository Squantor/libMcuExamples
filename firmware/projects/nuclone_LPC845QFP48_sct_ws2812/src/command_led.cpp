/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_led.cpp
 * @brief Command handler for the LED command
 */
#include <commands.hpp>
#include <application.hpp>
#include <nuclone_LPC845BD48_small.hpp>

namespace application {

squLib::results led(std::span<const char> commandLine) {
  (void)commandLine;
  std::int32_t rgbValue;
  if (commandValues.pop(rgbValue) != squLib::results::ok) {
    commandConsole.print("Insufficient elements on stack\n");
    return squLib::results::error;
  }
  std::array<std::uint8_t, 3> color;
  color[0] = (rgbValue >> 16) & 0xFF;
  color[1] = (rgbValue >> 8) & 0xFF;
  color[2] = rgbValue & 0xFF;

  spiPeripheral.write(color, 8);

  return squLib::results::ok;
}

squLib::commandHandler ledHandler{"led", "sends one WS2812 worth of data, stack value is 00RRGGBB\n", led};

}  // namespace application