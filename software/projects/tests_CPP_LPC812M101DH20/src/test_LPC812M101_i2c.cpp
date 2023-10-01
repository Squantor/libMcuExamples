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
static constexpr libMcuLL::hwAddressType i2cAddress = libMcuLL::hw::I2C0_cpp;
libMcuLL::hw::i2c::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::i2c::peripheral *>(i2cAddress)};

/**
 * @brief Gpio setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupI2c) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_I2C);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_I2C);
}

// testing inits
MINUNIT_ADD(LPC812M101DH20I2cInits, LPC812M101CppSetupI2c, LPC812M101Teardown) {
  uint32_t actualRate = i2cPeripheral.initMaster(133630);
  minUnitCheck(actualRate == 133928);
  minUnitCheck((dutRegisters->CFG & libMcuLL::hw::i2c::CFG::MASK) == libMcuLL::hw::i2c::CFG::MSTEN);
}
