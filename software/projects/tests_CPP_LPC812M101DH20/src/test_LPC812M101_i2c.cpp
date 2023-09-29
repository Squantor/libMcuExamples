/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 UART peripheral polling mode
 */

#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

// peripheral register sets
registers::i2c::registers *const dutRegisters{reinterpret_cast<registers::i2c::registers *>(peripherals::I2C0_cpp)};

/**
 * @brief Gpio setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupI2c) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_I2C);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_I2C);
}

// testing inits
MINUNIT_ADD(LPC812M101DH20I2cInits, LPC812M101CppSetupI2c, LPC812M101Teardown) {
  uint32_t actualRate = i2cPeripheral.initMaster(133630);
  minUnitCheck(actualRate == 133928);
  minUnitCheck((dutRegisters->CFG & registers::i2c::CFG::MASK) == registers::i2c::CFG::MSTEN);
}
