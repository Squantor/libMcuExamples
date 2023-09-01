/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief Teardown function that resets the LPC812M101 to a state
 * that more or less matches reset state
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <LPC812M101_teardown.hpp>
#include <test_conditions.hpp>
#include <MinUnit.h>

// peripheral register sets
registers::syscon::registers *const sysconRegisters{reinterpret_cast<registers::syscon::registers *>(peripherals::SYSCON_cpp)};

/** @brief resets all the registers to their default states
 *
 */
MINUNIT_TEARDOWN(LPC812M101Teardown) {
  sysconRegisters->PRESETCTRL = 0x00001FFF;
  sysconRegisters->PDRUNCFG = 0x0000ED50;  // we deviate here from the datasheet as we use the PLL and crystal oscillator
  sysconRegisters->SYSAHBCLKCTRL = 0x000000DF;
  minUnitCheck(LPC812M101TeardownCorrect() == true);
}

/** @brief checks if all the registers to their default states
 *  @return if all registers are correctly reset
 */
bool LPC812M101TeardownCorrect(void) {
  TESTANDRETURN(sysconRegisters->PRESETCTRL == 0x00001FFF);
  TESTANDRETURN(sysconRegisters->PDRUNCFG == 0x0000ED50);
  TESTANDRETURN(sysconRegisters->SYSAHBCLKCTRL == 0x000000DF);
  return true;
}