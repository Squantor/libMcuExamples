/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_empty.cpp
 * @brief Empty command template file
 */
#include <commands.hpp>
#include <application.hpp>

squLib::results empty(std::span<const char> commandLine) {
  (void)commandLine;
  commandConsole.print("Your command interpreter works perfectly!\n");
  return squLib::results::ok;
}

squLib::commandHandler emptyHandler{"empty", "Does nothing\n", empty};
