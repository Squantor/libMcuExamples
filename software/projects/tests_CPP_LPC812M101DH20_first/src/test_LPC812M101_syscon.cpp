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

using namespace libMcuLL::hw::syscon;
using namespace libMcuLL::sw::syscon;

// peripheral register sets
static constexpr libMcuLL::hwAddressType sysconAddress = libMcuLL::hw::SYSCON_cpp;
libMcuLL::hw::syscon::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::syscon::peripheral *>(sysconAddress)};

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
  uint32_t resetRegister = dutRegisters->PRESETCTRL & libMcuLL::hw::syscon::PRESETCTRL::RESERVED_MASK;
  resetRegister = resetRegister & ~(RESET_SPI0 | RESET_I2C | RESET_ACMP);
  minUnitCheck(resetRegister == 0x00000FBE);
  dutRegisters->PRESETCTRL = (dutRegisters->PRESETCTRL & ~PRESETCTRL::RESERVED_MASK) | (PRESETCTRL::RESERVED_MASK & resetRegister);
  sysconPeripheral.resetPeripherals(RESET_SPI0);
  // the reset function will restore all bits to operational
  minUnitCheck(dutRegisters->PRESETCTRL == 0x00000FBF);
  sysconPeripheral.resetPeripherals(RESET_I2C | RESET_ACMP);
  minUnitCheck(dutRegisters->PRESETCTRL == 0x00001FFF);
}

// We only test analog comparator as this is the most convienient peripheral to test
MINUNIT_ADD(LPC812M101CppSysconPowering, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(dutRegisters->PDRUNCFG == 0x0000ED50);
  sysconPeripheral.powerPeripherals(POWER_ACMP);
  minUnitCheck(dutRegisters->PDRUNCFG == 0x00006D50);
  sysconPeripheral.depowerPeripherals(POWER_ACMP);
  minUnitCheck(dutRegisters->PDRUNCFG == 0x0000ED50);
}

MINUNIT_ADD(LPC812M101CppSysconClocking, LPC812M101CppSetupSyscon, LPC812M101Teardown) {
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000000DF);
  sysconPeripheral.enablePeripheralClocks(CLOCK_ACMP);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000800DF);
  sysconPeripheral.enablePeripheralClocks(CLOCK_IOCON);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000C00DF);
  sysconPeripheral.disablePeripheralClocks(CLOCK_ACMP);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000400DF);
  sysconPeripheral.disablePeripheralClocks(CLOCK_IOCON);
  minUnitCheck(dutRegisters->SYSAHBCLKCTRL == 0x000000DF);
}