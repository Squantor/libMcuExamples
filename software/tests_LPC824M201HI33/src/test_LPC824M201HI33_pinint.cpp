/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC824M201HI33 PININT peripheral
 */
#include <nuclone_LPC824M201HI33_tests.hpp>
#include <MinUnit.h>
#include <LPC824M201HI33_teardown.hpp>
#include <common.hpp>
#include <LPC82X_interrupts.hpp>
#include <cortexM/delay_cycles.h>

uint32_t pinIntIsrCounter;

/**
 * @brief Pin change interrupt counter
 *
 */
void pinIntIsr(void) {
  pinIntIsrCounter++;
}

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC824M201HI33SetupPinint) {
  minUnitCheck(LPC824M201HI33TeardownCorrect() == true);
  pinIntIsrCounter = 0;
  interrupt_PIN_INT0 = pinIntIsr;
  sysconEnableClocks(SYSCON, CLKCTRL_GPIO);  // pinint engine shares clock with GPIO
}

/**
 * @brief
 */
MINUNIT_ADD(LPC824M201HI33PinintEdges, LPC824M201HI33SetupPinint, LPC824M201HI33Teardown) {
  gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
  gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  pinintSetPinModeEdge(PININT, PININT_CHAN0);
  pinintEnableIntHigh(PININT, PININT_CHAN0);
  // change pin
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  delay_cycles(100);
  minUnitCheck(pinIntIsrCounter == 1);
  // detect edge
  // reset to zero
  // do not detect edge
  // setup falling edge sensitivity
  // change pin
  // do not detect edge
  // reset to zero
  // detect edge
  // Done
}