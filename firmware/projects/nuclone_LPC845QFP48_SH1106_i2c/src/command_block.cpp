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

std::array<std::uint8_t, 16> pattern_buffer;

squLib::results block(std::span<const char> commandLine) {
  (void)commandLine;
  if (commandValues.size() < 4) {
    commandConsole.print("Needs 4 elements from top to bottom: pattern, length, column, row\n");
    return squLib::results::error;
  }
  std::int32_t col, row, length, pattern;
  commandValues.pop(pattern);
  commandValues.pop(length);
  commandValues.pop(col);
  commandValues.pop(row);
  pattern_buffer.fill(static_cast<std::uint8_t>(pattern));
  display.SetAddress(static_cast<uint32_t>(col), static_cast<uint32_t>(row));
  display.SendData(std::span<uint8_t>(pattern_buffer).subspan(0, length));
  return squLib::results::ok;
}

squLib::commandHandler block_handler{
  "block", "writes to column and row a block with pattern p of length l\n stack format pattern, length, column, row\n", block};
