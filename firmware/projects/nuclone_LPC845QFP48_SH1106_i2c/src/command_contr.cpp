/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_contr.cpp
 * @brief Command for setting Oled display contrast
 */
#include <commands.hpp>
#include <application.hpp>

squLib::results Contrast(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() == 0) {
    commandConsole.print("Stack is empty\n");
    return squLib::results::error;
  }
  std::int32_t contrast = 10;
  commandValues.pop(contrast);
  display.Contrast(static_cast<std::uint8_t>(contrast));
  return squLib::results::ok;
}

squLib::commandHandler contrast_handler{"contr", "Sets the OLED display contrast\n", Contrast};
