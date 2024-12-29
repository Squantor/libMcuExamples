/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */
#include <application.hpp>
#include <cmdline_simple.hpp>
#include <console.hpp>

namespace application {

squLib::console<usartPeripheral> commandConsole;
squLib::commandValueStack<8, commandConsole> commandValues;
squLib::commandInterpreter<commandHandlers, commandValues, commandConsole> commandInterpreter;
squLib::commandlineSimple<80, commandConsole, commandInterpreter> commandline;

std::array<std::uint16_t, 64> pattern;

void application::init() {
  commandConsole.print("LPC845 small nuclone test program\n");
  pattern.fill(0x0000);
  // fill pattern with simple XOR pattern
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 32; y++) {
      std::uint16_t mask = 0x01 << (x & 0xF);
      std::size_t index = x / 16 + y;
      if ((x ^ y) & 0x40)
        pattern[index] = pattern[index] | mask;
    }
  }
}
void application::progress() {
  static std::uint32_t currentTicksSeconds = ticks;
  static std::uint32_t seconds = 0;
  static std::uint32_t currentTicksFaster = ticks;
  static std::uint32_t faster = 0;
  static std::uint32_t xCoord = 0;
  static std::uint32_t yCoord = 0;

  if (currentTicksSeconds + 100 < ticks) {
    memlcdDriver.toggleVcom();
    seconds++;
    currentTicksSeconds = ticks;
    xCoord += 3;
    if (xCoord > display.getXSize())
      xCoord -= display.getXSize();
    yCoord += 5;
    if (yCoord > display.getYSize())
      yCoord -= display.getYSize();
    display.fill(xCoord, yCoord, xCoord + 20, yCoord + 20, 0);
    display.update();
  }

  if (currentTicksFaster + 40 < ticks) {
    for (std::uint32_t x = 0; x < libMcuDrv::memlcd::LS013B4DN04::maxX; x++) {
      for (std::uint32_t y = 0; y < libMcuDrv::memlcd::LS013B4DN04::maxX; y++) {
        display.setPixel(x, y, (x * x + y * y + faster) & 64);
      }
    }
    display.update();
    faster++;
    currentTicksFaster = ticks;
  }

  // echo characters
  if (usartPeripheral.receiveDataAvailable() > 0) {
    static std::array<char, 1> data;
    usartPeripheral.read(data);
    commandline.input(data);
  }
  // state handling
  switch (state) {
    case applicationState::idle:
      break;

    default:
      commandConsole.print("Unknown state!!!");
      break;
  }
}

}  // namespace application
