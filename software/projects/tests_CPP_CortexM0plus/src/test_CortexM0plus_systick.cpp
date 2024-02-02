/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the CortexM0plus systick peripheral
 */
#include <nuclone_CortexM0plus_tests.hpp>
#include <MinUnit.h>
#include <CortexM0plus_teardown.hpp>
#include <common.hpp>

using namespace libMcuLL::hw::systick;
using namespace libMcuLL::sw::systick;

// peripheral register sets
static constexpr libMcuLL::hwAddressType systickAddress = libMcuLL::hw::systickAddress;
libMcuLL::hw::systick::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::systick::peripheral *>(systickAddress)};

/**
 * @brief systick setup and initialisation
 */
MINUNIT_SETUP(CortexM0plusSetupSystick) {
  minUnitCheck(CortexM0plusTeardownCorrect() == true);
  minUnitPass();
}

MINUNIT_ADD(CortexM0plusSystickInit, CortexM0plusSetupSystick, CortexM0plusTeardown) {
  minUnitPass();
}
