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

MINUNIT_ADD(CortexM0plusNvicSetClear, CortexM0plusSetupNvic, CortexM0plusTeardown) {
  nvicPeripheral.enable(libMcuLL::hw::interrupts::dummy0);
  minUnitCheck(dutRegisters->ICER[0] == 0x1);
  nvicPeripheral.enable(libMcuLL::hw::interrupts::dummy12);
  minUnitCheck(dutRegisters->ICER[0] == 0x1001);
  nvicPeripheral.disable(libMcuLL::hw::interrupts::dummy0);
  minUnitCheck(dutRegisters->ICER[0] == 0x1000);
  nvicPeripheral.disable(libMcuLL::hw::interrupts::dummy12);
  minUnitCheck(dutRegisters->ICER[0] == 0x0);
}

MINUNIT_ADD(CortexM0plusNvicPending, CortexM0plusSetupNvic, CortexM0plusTeardown) {
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy0) == false);
  nvicPeripheral.setPending(libMcuLL::hw::interrupts::dummy0);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy0) == true);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy12) == false);
  minUnitCheck(dutRegisters->ICPR[0] == 0x00000001UL);
  nvicPeripheral.setPending(libMcuLL::hw::interrupts::dummy12);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy0) == true);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy12) == true);
  minUnitCheck(dutRegisters->ICPR[0] == 0x00001001UL);
  nvicPeripheral.clearPending(libMcuLL::hw::interrupts::dummy12);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy0) == true);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy12) == false);
  minUnitCheck(dutRegisters->ICPR[0] == 0x00000001UL);
  nvicPeripheral.clearPending(libMcuLL::hw::interrupts::dummy0);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy0) == false);
  minUnitCheck(nvicPeripheral.getPending(libMcuLL::hw::interrupts::dummy12) == false);
  minUnitCheck(dutRegisters->ICPR[0] == 0x00000000UL);
}

MINUNIT_ADD(CortexM0plusNvicPriority, CortexM0plusSetupNvic, CortexM0plusTeardown) {
  minUnitCheck(dutRegisters->IP[0] == 0x00000000);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy0, 2);
  minUnitCheck(dutRegisters->IP[0] == 0x00000080);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy1, 3);

  minUnitCheck(dutRegisters->IP[0] == 0x0000C080);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy0, 0);
  minUnitCheck(dutRegisters->IP[0] == 0x0000C000);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy12, 1);
  minUnitCheck(dutRegisters->IP[3] == 0x00000040);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy12, 0);
  minUnitCheck(dutRegisters->IP[3] == 0x00000000);
  nvicPeripheral.setPriority(libMcuLL::hw::interrupts::dummy1, 0);
  for (int i = 0; i < 8; ++i) {
    minUnitCheck(dutRegisters->IP[i] == 0x00000000);
  }
}