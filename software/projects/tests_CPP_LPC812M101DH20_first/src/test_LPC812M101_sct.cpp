/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 SCT peripheral
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

using namespace libMcuLL::hw::sct;
using namespace libMcuLL::sw::sct;

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSct) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
}

MINUNIT_ADD(LPC812M101CppSctInit, LPC812M101CppSetupSct, LPC812M101Teardown) {
  minUnitPass();
}