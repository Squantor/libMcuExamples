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
squLib::console<displayTerminal> graphicalConsole;
squLib::commandValueStack<8, commandConsole> commandValues;
squLib::commandInterpreter<commandHandlers, commandValues, commandConsole> commandInterpreter;
squLib::commandlineSimple<80, commandConsole, commandInterpreter> commandline;

void application::init() {
  commandConsole.print("LPC845 small nuclone test program\n");
}
void application::progress() {
  static std::uint32_t currentTicksSeconds = ticks;
  static std::uint32_t currentTicksTens = ticks;
  static std::uint32_t seconds = 0;
  static std::uint32_t tens = 0;
  static std::uint32_t bright = 0;
  if (currentTicksSeconds + 200 < ticks) {
    display.invert(seconds % 2 == 0);
    graphicalConsole.print("seconds: ", seconds, "\n");
    seconds++;
    currentTicksSeconds = ticks;
  }
  if (currentTicksTens + 20 < ticks) {
    // display.scroll(tens % 64);
    // display.brightness(bright);
    tens++;
    bright++;
    if (bright > 100)
      bright = 0;
    currentTicksTens = ticks;
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
