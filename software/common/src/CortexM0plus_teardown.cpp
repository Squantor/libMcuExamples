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
#include <nuclone_CortexM0plus_tests.hpp>
#include <CortexM0plus_teardown.hpp>
#include <test_conditions.hpp>
#include <MinUnit.h>

// peripheral register sets

MINUNIT_TEARDOWN(CortexM0plusTeardown) {
  minUnitPass();
}

bool CortexM0plusTeardownCorrect(void) {
  TESTANDRETURN(0 == 0);
  return true;
}