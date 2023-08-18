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

/** @brief resets all the registers to their default states
 *
 * TODO: syscon needs to be C++ified
 */
MINUNIT_TEARDOWN(LPC812M101Teardown) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
}

/** @brief checks if all the registers to their default states
 *  @return if all registers are correctly reset
 */
bool LPC812M101TeardownCorrect(void) {
  // use the TESTANDRETURN macro
  // TESTANDRETURN(IOCON->PIO[IOCON_PIO0_17] == IOCON_NORMAL_DEFAULT);
  return true;
}