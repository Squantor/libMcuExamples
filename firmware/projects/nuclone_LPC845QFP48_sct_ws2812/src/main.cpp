/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for Diy Solder
 */
#include <nuclone_LPC845BD48_small.hpp>
#include <application.hpp>

namespace application {
application controller;
}

int main() {
  boardInit();
  application::controller.Init();
  while (1) {
    application::controller.progress();
  }
}
