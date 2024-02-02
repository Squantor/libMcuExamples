/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_CortexM0plus_tests.hpp>

libMcuLL::sw::systick::systick<libMcuLL::hw::systickAddress> systickPeripheral;

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

void boardInit(void) {
  systickPeripheral.peripheral()->CSR = 0;
  systickPeripheral.peripheral()->RVR = 0;
  systickPeripheral.peripheral()->CVR = 0;
}
