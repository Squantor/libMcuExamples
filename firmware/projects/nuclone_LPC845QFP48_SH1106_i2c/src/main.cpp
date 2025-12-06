/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for SH1106 test project
 */
#include <nuclone_LPC845BD48_small_SH1106_i2c.hpp>
#include <application.hpp>

namespace application {
Application controller;
}

int main() {
  BoardInit();
  application::controller.Init();
  while (1) {
    application::controller.Progress();
  }
}