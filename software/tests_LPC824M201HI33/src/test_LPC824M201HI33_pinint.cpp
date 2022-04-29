/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC824M201HI33 PININT peripheral
 */
#include <nuclone_LPC824M201HI33_tests.hpp>
#include <MinUnit.h>
#include <LPC824M201HI33_teardown.hpp>
#include <common.hpp>

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC824M201HI33SetupPinint) {
  minUnitCheck(LPC824M201HI33TeardownCorrect() == true);
  sysconEnableClocks(SYSCON, CLKCTRL_GPIO);  // pinint engine shares clock with GPIO
}

/**
 * @brief
 */
MINUNIT_ADD(LPC824M201HI33Pinint, LPC824M201HI33SetupPinint, LPC824M201HI33Teardown) {
  minUnitPass();
}