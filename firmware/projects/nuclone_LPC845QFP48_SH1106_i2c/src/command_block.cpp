/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command handlers definitions
 * @brief central gathering spot for all command handlers
 */
#include <commands.hpp>
#include <application.hpp>

std::array<std::uint8_t, 32> pattern_buffer;

squLib::results block(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() < 3) {
    commandConsole.print("Needs 3 elements on the stack, X Y coordinates and a pattern\n");
    return squLib::results::error;
  }
  std::int32_t x, y, pattern;
  commandValues.pop(x);
  commandValues.pop(y);
  commandValues.pop(pattern);
  pattern_buffer.fill(static_cast<std::uint8_t>(pattern));
  display.SendData(pattern_buffer);
  return squLib::results::ok;
}

squLib::commandHandler block_handler{"block", "writes to x and y a block with pattern p\n", block};
