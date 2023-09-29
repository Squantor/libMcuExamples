/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 SYSCON peripheral
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

// We only test analog comparator as this is the most convienient peripheral to test
MINUNIT_ADD(LPC812M101CppSysconPowering, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(dutRegisters->PDRUNCFG == 0x0000ED50);
  sysconPeripheral.powerPeripherals(instances::syscon::POWER_ACMP);
  minUnitCheck(dutRegisters->PDRUNCFG == 0x00006D50);
  sysconPeripheral.depowerPeripherals(instances::syscon::POWER_ACMP);
  minUnitCheck(dutRegisters->PDRUNCFG == 0x0000ED50);
}

MINUNIT_ADD(LPC812M101CppSysconClocking, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000000DF);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_ACMP);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000800DF);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_IOCON);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000C00DF);
  sysconPeripheral.disablePeripheralClocks(instances::syscon::CLOCK_ACMP);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000400DF);
  sysconPeripheral.disablePeripheralClocks(instances::syscon::CLOCK_IOCON);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000000DF);
}