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
libMcuLL::hw::systick::peripheral *const systickDutRegisters{reinterpret_cast<libMcuLL::hw::systick::peripheral *>(systickAddress)};

/**
 * @brief systick setup and initialisation
 */
MINUNIT_SETUP(CortexM0plusSetupSystick) {
  minUnitCheck(CortexM0plusTeardownCorrect() == true);
}

MINUNIT_ADD(CortexM0plusSystickInit, CortexM0plusSetupSystick, CortexM0plusTeardown) {
  systickPeripheral.init(0x123456);
  minUnitCheck(systickDutRegisters->RVR == 0x123456);
  systickPeripheral.setReload(0x654321);
  minUnitCheck(systickDutRegisters->RVR == 0x654321);
}

MINUNIT_ADD(CortexM0plusSystickStart, CortexM0plusSetupSystick, CortexM0plusTeardown) {
  systickPeripheral.init(0x1000);  // short reload value so we can check value
  systickPeripheral.start();
  std::uint32_t firstCount = systickPeripheral.getCount();
  crudeDelay(101);
  std::uint32_t secondCount = systickPeripheral.getCount();
  minUnitCheck(firstCount != secondCount);
  // we need longer intervals for this test
  systickPeripheral.setReload(0xFFFF);
  systickPeripheral.getZeroPass();
  while (systickPeripheral.getZeroPass() == 0) {
    libMcuLL::sw::nop();
  }
  minUnitCheck(systickPeripheral.getZeroPass() == 0);
  crudeDelay(0xFFF);
  minUnitCheck(systickPeripheral.getZeroPass() != 0);
  minUnitPass();
}
