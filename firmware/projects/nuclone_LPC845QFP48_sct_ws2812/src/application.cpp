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

std::array<std::uint8_t, 72> ringValue;

constexpr std::uint8_t ledLimit = 24;
constexpr std::uint8_t ledStep = 4;

void fillRing() {
  static std::uint8_t red = 0;
  static bool redUpCnt = true;
  static std::uint8_t green = 8;
  static bool greenUpCnt = true;
  static std::uint8_t blue = 16;
  static bool blueUpCnt = true;

  uint8_t runningRed = red;
  bool runningRedUpCnt = redUpCnt;
  uint8_t runningGreen = green;
  bool runningGreenUpCnt = greenUpCnt;
  uint8_t runningBlue = blue;
  bool runningBlueUpCnt = blueUpCnt;
  for (int i = 0; i < 72; i += 3) {
    ringValue[i] = runningGreen;
    ringValue[i + 1] = runningRed;
    ringValue[i + 2] = runningBlue;

    if (runningRedUpCnt) {
      runningRed += ledStep;
      if (runningRed == ledLimit) {
        runningRedUpCnt = false;
      }
    } else {
      runningRed -= ledStep;
      if (runningRed == 0) {
        runningRedUpCnt = true;
      }
    }

    if (runningGreenUpCnt) {
      runningGreen += ledStep;
      if (runningGreen == ledLimit) {
        runningGreenUpCnt = false;
      }
    } else {
      runningGreen -= ledStep;
      if (runningGreen == 0) {
        runningGreenUpCnt = true;
      }
    }

    if (runningBlueUpCnt) {
      runningBlue += ledStep;
      if (runningBlue == ledLimit) {
        runningBlueUpCnt = false;
      }
    } else {
      runningBlue -= ledStep;
      if (runningBlue == 0) {
        runningBlueUpCnt = true;
      }
    }
  }
  if (redUpCnt) {
    red += ledStep;
    if (red == ledLimit) {
      redUpCnt = false;
    }
  } else {
    red -= ledStep;
    if (red == 0) {
      redUpCnt = true;
    }
  }

  if (greenUpCnt) {
    green += ledStep;
    if (green == ledLimit) {
      greenUpCnt = false;
    }
  } else {
    green -= ledStep;
    if (green == 0) {
      greenUpCnt = true;
    }
  }

  if (blueUpCnt) {
    blue += ledStep;
    if (blue == ledLimit) {
      blueUpCnt = false;
    }
  } else {
    blue -= ledStep;
    if (blue == 0) {
      blueUpCnt = true;
    }
  }
}

void application::init() {
  ringValue.fill(0x00);
  commandConsole.print("LPC845 SCT WS2812 test program\n");
}

void application::progress() {
  static std::uint32_t tick100ms = 0;
  if (tick100ms < ticks) {
    fillRing();
    spiPeripheral.write(ringValue, 8);
    tick100ms = ticks + TICKS_PER_S / 20;
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
