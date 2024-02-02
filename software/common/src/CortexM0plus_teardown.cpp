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
static constexpr libMcuLL::hwAddressType systickAddress = libMcuLL::hw::systickAddress;
libMcuLL::hw::systick::peripheral *const systickRegisters{reinterpret_cast<libMcuLL::hw::systick::peripheral *>(systickAddress)};

MINUNIT_TEARDOWN(CortexM0plusTeardown) {
  systickRegisters->CSR = 0;
  systickRegisters->RVR = 0;
  systickRegisters->CVR = 0;
  minUnitPass();
}

bool CortexM0plusTeardownCorrect(void) {
  TESTANDRETURN(systickRegisters->CSR == 0);
  TESTANDRETURN(systickRegisters->RVR == 0);
  TESTANDRETURN(systickRegisters->CVR == 0);
  return true;
}