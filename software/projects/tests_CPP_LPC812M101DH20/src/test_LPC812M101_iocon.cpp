/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101 IOCON peripheral
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

// peripheral register sets
registers::iocon::registers *const dutRegisters{reinterpret_cast<registers::iocon::registers *>(peripherals::IOCON_cpp)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupIocon) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_IOCON);
}

MINUNIT_ADD(LPC812M101DH20Iocon, LPC812M101CppSetupIocon, LPC812M101Teardown) {
  minUnitPass();
}