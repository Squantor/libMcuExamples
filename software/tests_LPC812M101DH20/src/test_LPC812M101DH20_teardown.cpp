/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101DH20 teardown
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101DH20_teardown.hpp>

MINUNIT_ADD(LPC812M101DH20teardown, NULL, NULL) {
  LPC812M101DH20Teardown(testResults);  // passing test state directly
  minUnitCheck(LPC812M101DH20TeardownCorrect() == true);
}