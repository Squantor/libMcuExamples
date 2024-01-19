/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 SCT peripheral
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

using namespace libMcuLL::hw::acmp;
using namespace libMcuLL::sw::acmp;

// peripheral register sets
static constexpr libMcuLL::hwAddressType acmpAddress = libMcuLL::hw::ACMP_cpp;
libMcuLL::hw::acmp::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::acmp::peripheral *>(acmpAddress)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupacmp) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.powerPeripherals(libMcuLL::sw::syscon::POWER_ACMP);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_SCT | libMcuLL::sw::syscon::CLOCK_IOCON |
                                          libMcuLL::sw::syscon::CLOCK_GPIO | libMcuLL::sw::syscon::CLOCK_SWM |
                                          libMcuLL::sw::syscon::CLOCK_ACMP);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_SCT | libMcuLL::sw::syscon::RESET_GPIO |
                                    libMcuLL::sw::syscon::RESET_ACMP);
  // switch matrix
  swmPeriperhal.setup(pwmOutPin, sctOutput0Function);
  swmPeriperhal.enableFixedPins(libMcuLL::sw::swm::ACMP_I2);  // enable fixed function on PIO0_1
  ioconPeripheral.setup(pwmInPin, libMcuLL::sw::iocon::INACTIVE);
  gpioPeripheral.low(test1Pin);
  gpioPeripheral.output(test1Pin);
  // sct configuration
  sctPeripheral.init(0x0, libMcuLL::sw::sct::BIDIRECTIONAL);
  sctPeripheral.setMatch(libMcuLL::sw::sct::MATCH_0, 1000);
  sctPeripheral.setupPwm(libMcuLL::sw::sct::MATCH_1, 500, libMcuLL::sw::sct::EVENT_0, libMcuLL::sw::sct::OUTPUT_0, false);
  sctPeripheral.start();
}

MINUNIT_ADD(LPC812M101CppAcmpInit, LPC812M101CppSetupacmp, LPC812M101Teardown) {
  acmpPeripheral.init(inputPositiveSettings::IN2, inputNegativeSettings::REF, edgeDetectSettings::BOTH,
                      outputControlSettings::SYNCED, hysteresisSettings::HYS_20MV);
  minUnitCheck((dutRegisters->CTRL & CTRL::MASK) == 0x06203250);
  minUnitCheck((dutRegisters->LAD & LAD::MASK) == 0x00000000);
  acmpPeripheral.init(inputPositiveSettings::REF, inputNegativeSettings::IN2, edgeDetectSettings::FALLING,
                      outputControlSettings::DIRECT, hysteresisSettings::HYS_10MV, ladderReferenceSetting::VDD);
  minUnitCheck((dutRegisters->CTRL & CTRL::MASK) == 0x04001600);
  minUnitCheck((dutRegisters->LAD & LAD::MASK) == 0x00000001);
}

// test internal reference functionality
// test ladder functionality
