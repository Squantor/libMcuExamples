/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101 SPI peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

// peripheral register sets
registers::syscon::registers *const dutRegisters{reinterpret_cast<registers::syscon::registers *>(peripherals::SYSCON_cpp)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSyscon) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
}

MINUNIT_ADD(LPC812M101CppSysconChipID, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(sysconPeripheral.getChipId() == 0x00008122);
}

MINUNIT_ADD(LPC812M101CppSysconResets, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(dutRegisters->PRESETCTRL == 0x00001FFF);
  // preset the reset register to a value that will be rest by the test
  uint32_t resetRegister = dutRegisters->PRESETCTRL & registers::syscon::PRESETCTRL::MASK;
  resetRegister = resetRegister & ~(instances::syscon::RESET_SPI0 | instances::syscon::RESET_I2C | instances::syscon::RESET_ACMP);
  minUnitCheck(resetRegister == 0x00000FBE);
  dutRegisters->PRESETCTRL =
    (dutRegisters->PRESETCTRL & ~registers::syscon::PRESETCTRL::MASK) | (registers::syscon::PRESETCTRL::MASK & resetRegister);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_SPI0);
  // the reset function will restore all bits to operational
  minUnitCheck(dutRegisters->PRESETCTRL == 0x00000FBF);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_I2C | instances::syscon::RESET_ACMP);
  minUnitCheck(dutRegisters->PRESETCTRL == 0x00001FFF);
}