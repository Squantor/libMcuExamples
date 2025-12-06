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

namespace application {

squLib::results stat(std::span<const char> commandLine) {
  (void)commandLine;
  switch (controller.GetState()) {
    case ApplicationState::idle:
      commandConsole.print("Application is idle\n");
      break;

    default:
      commandConsole.print("Unknown state!\n");
      break;
  }
  return squLib::results::ok;
}

squLib::commandHandler statHandler{"stat", "prints the current application state\n", stat};

}  // namespace application