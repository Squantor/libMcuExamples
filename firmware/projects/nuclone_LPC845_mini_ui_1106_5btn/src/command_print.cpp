/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_print.cpp
 * @brief prints a character on the SH1106 OLED display
 */
#include <commands.hpp>
#include <application.hpp>
#include <algorithm>
#include <fonts/font_8x8_rowflip.hpp>

sqEmbedded::fonts::mono8x8RowFlip font;

std::array<std::uint8_t, 8> character_buffer;

squLib::results print(std::span<const char>) {
  if (commandValues.size() < 4) {
    commandConsole.print("Needs 4 elements from top to bottom: character, count, column, row\n");
    return squLib::results::error;
  }
  std::int32_t col, row, length, character;
  commandValues.pop(character);
  commandValues.pop(length);
  commandValues.pop(col);
  commandValues.pop(row);
  display.SetAddress(static_cast<uint32_t>(col), static_cast<uint32_t>(row));
  std::array<std::uint8_t, 8> buffer = font.ascii2Bitmap(static_cast<uint8_t>(character));
  std::copy_n(buffer.begin(), buffer.size(), character_buffer.begin());
  for (int i = 0; i < length; i++) {
    display.SendData(character_buffer);
  }
  return squLib::results::ok;
}

squLib::commandHandler print_handler{
  "print", "prints a character on col,row of the OLED display\n stack format col, row, character\n", print};
