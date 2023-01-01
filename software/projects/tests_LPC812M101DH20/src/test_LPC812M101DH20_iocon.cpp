/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101DH20 IOCON peripheral
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101DH20_teardown.hpp>
#include <common.hpp>

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC812M101DH20SetupIocon) {
  minUnitCheck(LPC812M101DH20TeardownCorrect() == true);
  sysconEnableClocks(SYSCON, CLKCTRL_GPIO | CLKCTRL_IOCON);
  sysconEnableResets(SYSCON, RESETCTRL_GPIO);
}

/**
 * @brief tests for the IOCON pullup and down function
 */
MINUNIT_ADD(LPC812M101DH20IoconPull, LPC812M101DH20SetupIocon, LPC812M101DH20Teardown) {
  gpioSetPortDir(GPIO, GPIO_PORT0, 0);
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_INACTIVE));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == true);
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_PULLDOWN));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == false);
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_PULLUP));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == true);
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC812M101DH20IoconRepeater, LPC812M101DH20SetupIocon, LPC812M101DH20Teardown) {
  gpioSetPortDir(GPIO, PORT_TESTPIN_0_0, 0);
  gpioSetPortDir(GPIO, PORT_TESTPIN_0_1, 0);
  // check pulled up buskeeper
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_INACTIVE));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_INACTIVE));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_PULLUP));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_REPEATER));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_INACTIVE));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == true);
  // check pulled down buskeeper and also flipping the pins
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_INACTIVE));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_INACTIVE));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_PULLDOWN));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_REPEATER));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_INACTIVE));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == false);
}

/**
 * @brief tests for the IOCON open drain function
 */
MINUNIT_ADD(LPC812M101DH20IoconOpenDrain, LPC812M101DH20SetupIocon, LPC812M101DH20Teardown) {
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE(IOCON_MODE_INACTIVE) | IOCON_OD(true));
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_PULLUP));
  gpioSetPortDIROutput(GPIO, PORT_TESTPIN_0_0, BITPOS(PIN_TESTPIN_0_0));
  gpioPortClear(GPIO, PORT_TESTPIN_0_0, BITPOS(PIN_TESTPIN_0_0));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == false);
  gpioPortSet(GPIO, PORT_TESTPIN_0_0, BITPOS(PIN_TESTPIN_0_0));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == true);
  ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE(IOCON_MODE_PULLDOWN));
  minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == false);
}

/* Some tests that are still to do:
 * Test glitch filtering, depends on timer subsystem
 * Analog pin tests, depends on ADC/Comparator
 */