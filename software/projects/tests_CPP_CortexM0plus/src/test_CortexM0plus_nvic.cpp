/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the CortexM0plus NVIC peripheral
 */
#include <nuclone_CortexM0plus_tests.hpp>
#include <MinUnit.h>
#include <CortexM0plus_teardown.hpp>
#include <common.hpp>

using namespace libMcuLL::hw::nvic;
using namespace libMcuLL::sw::nvic;

// peripheral register sets
static constexpr libMcuLL::hwAddressType nvicAddress = libMcuLL::hw::nvicAddress;
libMcuLL::hw::nvic::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::nvic::peripheral *>(nvicAddress)};

/**
 * @brief systick setup and initialisation
 */
MINUNIT_SETUP(CortexM0plusSetupNvic) {
  minUnitCheck(CortexM0plusTeardownCorrect() == true);
}

MINUNIT_ADD(CortexM0plusNvicInit, CortexM0plusSetupNvic, CortexM0plusTeardown) {
  minUnitPass();
}