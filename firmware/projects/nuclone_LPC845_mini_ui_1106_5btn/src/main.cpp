/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for SH1106 test project
 */
#include <nuclone_LPC845BD48_UI_1106_5btn.hpp>
#include <application.hpp>

Application controller;

int main() {
  BoardInit();
  controller.Init();
  while (1) {
    controller.Progress();
    usart_peripheral.Progress();
    i2c_peripheral.Progress();
  }
}