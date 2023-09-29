/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 IOCON peripheral
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

/**
 * @brief Tests iocon pullup/down functions
 *
 */
MINUNIT_ADD(LPC812M101DH20IoconPull, LPC812M101CppSetupIocon, LPC812M101Teardown) {
  gpioPeripheral.input(test1Pin);
  gpioPeripheral.input(test0Pin);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::INACTIVE);
  minUnitCheck(gpioPeripheral.get(test1Pin) != 0);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::PULLDOWN);
  minUnitCheck(gpioPeripheral.get(test1Pin) == 0);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::PULLUP);
  minUnitCheck(gpioPeripheral.get(test1Pin) != 0);
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC812M101DH20IoconRepeater, LPC812M101CppSetupIocon, LPC812M101Teardown) {
  gpioPeripheral.input(test1Pin);
  gpioPeripheral.input(test0Pin);
  // check pulled up buskeeper
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::REPEATER);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::INACTIVE);
  minUnitCheck(gpioPeripheral.get(test0Pin) != 0);
  // check pulled down buskeeper and also flipping the pins
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::PULLDOWN);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::REPEATER);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::INACTIVE);
  minUnitCheck(gpioPeripheral.get(test1Pin) == 0);
}

/**
 * @brief tests for the IOCON open drain function
 */
MINUNIT_ADD(LPC812M101DH20IoconOpenDrain, LPC812M101CppSetupIocon, LPC812M101Teardown) {
  gpioPeripheral.input(test1Pin);
  gpioPeripheral.input(test0Pin);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::INACTIVE, registers::iocon::PIO::OD);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::PULLUP);
  gpioPeripheral.output(test0Pin);
  gpioPeripheral.low(test0Pin);
  minUnitCheck(gpioPeripheral.get(test1Pin) == 0);
  gpioPeripheral.high(test0Pin);
  minUnitCheck(gpioPeripheral.get(test1Pin) != 0);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::PULLDOWN);
  minUnitCheck(gpioPeripheral.get(test1Pin) == 0);
}

/* TODO:
 * Test glitch filtering, depends on timer subsystem for generating clock pulses
 * Analog pin tests, depends on ADC/Comparator, will be tested with comparator/ADC
 */