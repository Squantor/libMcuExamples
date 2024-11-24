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

void application::init() {
  commandConsole.print("LPC845 small nuclone test program\n");
}
void application::progress() {
  static std::uint32_t currentTicks = ticks;
  static bool displayState = false;
  if (currentTicks + 200 < ticks) {
    // Print("test:\t", currentTicks, "\t", print::Hex{currentTicks}, "\n");
    SSD1306.invertDisplay(displayState);
    displayState = !displayState;
    currentTicks = ticks;
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
