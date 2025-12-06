/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file main.cpp
 * @brief LPC845 QFP48 blink test project
 */
#include <nuclone_LPC845BD48_small.hpp>

int main() {
  BoardInit();
  while (1) {
    libmcull::nop();
  }
}
