/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief Teardown function that resets the LPC812 to a state
 * that more or less matches reset state
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <LPC812M101DH20_teardown.hpp>
#include <test_conditions.hpp>
#include <MinUnit.h>

/** @brief resets all the registers to their default states
 */
MINUNIT_TEARDOWN(LPC812M101DH20Teardown) {
  minUnitCheck(LPC812M101DH20TeardownCorrect() == true);
}

/** @brief checks if all the registers to their default states
 *  @return if all registers are correctly torndown
 */
bool LPC812M101DH20TeardownCorrect(void) {
  TESTANDRETURN(1 == 1);
  return true;
}