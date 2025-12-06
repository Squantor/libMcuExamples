/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for LPC845QFP48 template project
 */
#include <nuclone_LPC845BD48_small_template.hpp>
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
