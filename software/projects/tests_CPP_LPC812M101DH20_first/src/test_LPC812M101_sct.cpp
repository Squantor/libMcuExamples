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

// peripheral register sets
static constexpr libMcuLL::hwAddressType sctAddress = libMcuLL::hw::SCT0_cpp;
libMcuLL::hw::sct::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::sct::peripheral *>(sctAddress)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSct) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_SCT);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_SCT);
}

MINUNIT_ADD(LPC812M101CppSctInit, LPC812M101CppSetupSct, LPC812M101Teardown) {
  sctPeripheral.init(0x4, BIDIRECTIONAL);
  minUnitCheck(dutRegisters->CONFIG == 0x00020001);
  minUnitCheck(dutRegisters->CTRL == 0x00040094);
  sctPeripheral.init(0x3, 0x5, BIDIRECTIONAL, UP);
  minUnitCheck(dutRegisters->CONFIG == 0x00060000);
  minUnitCheck(dutRegisters->CTRL == 0x00A40074);
}