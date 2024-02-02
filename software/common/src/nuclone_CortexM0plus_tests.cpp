/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_CortexM0plus_tests.hpp>

void crudeDelay(uint32_t iterations) {
  for (uint32_t i = iterations; i > 0; i--) {
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
    libMcuLL::sw::nop();
  }
}

void boardInit(void) {}
