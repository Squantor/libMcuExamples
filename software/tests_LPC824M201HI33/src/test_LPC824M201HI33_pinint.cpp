/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC824M201HI33 PININT peripheral
 */
#include <board.hpp>
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
  pinintClearIntStatus(PININT, PININT_CHAN0);
}

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC824M201HI33SetupPinint) {
  minUnitCheck(LPC824M201HI33TeardownCorrect() == true);
  pinIntIsrCounter = 0;
  interrupt_PIN_INT0 = pinIntIsr;
  sysconPinInterruptSelect(SYSCON, PININT0, PIN_TESTPIN_0_1);
  sysconEnableClocks(SYSCON, CLKCTRL_GPIO);  // pinint engine shares clock with GPIO
}

/**
 * @brief PININT tests for edge triggered interrupts
 */
MINUNIT_ADD(LPC824M201HI33PinintEdges, LPC824M201HI33SetupPinint, LPC824M201HI33Teardown) {
  gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
  gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  delay_cycles(100);
  pinintSetPinModeEdge(PININT, PININT_CHAN0);
  pinintClearRiseStates(PININT, PININT_CHAN0);
  pinintClearFallStates(PININT, PININT_CHAN0);
  pinintEnableIntHigh(PININT, PININT_CHAN0);
  NVIC_EnableIRQ(PININT0_IRQn);
  // change pin
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  // detect edge
  delay_cycles(100);
  minUnitCheck(pinIntIsrCounter == 1);
  // reset to zero
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  // do not detect edge
  delay_cycles(100);
  minUnitCheck(pinIntIsrCounter == 1);
  // setup falling edge sensitivity
  NVIC_DisableIRQ(PININT0_IRQn);
  pinintDisableIntHigh(PININT, PININT_CHAN0);
  pinintClearRiseStates(PININT, PININT_CHAN0);
  pinintClearFallStates(PININT, PININT_CHAN0);
  pinintEnableIntLow(PININT, PININT_CHAN0);
  NVIC_EnableIRQ(PININT0_IRQn);
  // change pin
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  // do not detect edge
  delay_cycles(100);
  minUnitCheck(pinIntIsrCounter == 1);
  // reset to zero
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  // detect edge
  delay_cycles(100);
  minUnitCheck(pinIntIsrCounter == 2);
  // Done
}

/**
 * @brief PININT tests for edge triggered interrupts
 */
MINUNIT_ADD(LPC824M201HI33PinintLevels, LPC824M201HI33SetupPinint, LPC824M201HI33Teardown) {
  gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
  gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  delay_cycles(100);
  // setup high level sensitivity
  pinintSetPinModeLevel(PININT, PININT_CHAN0);
  pinintClearRiseStates(PININT, PININT_CHAN0);
  pinintClearFallStates(PININT, PININT_CHAN0);
  pinintEnableIntHigh(PININT, PININT_CHAN0);
  NVIC_EnableIRQ(PININT0_IRQn);
  // change pin and trigger a few interrupts
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  delay_cycles(1000);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  // count interrupts
  minUnitCheck(pinIntIsrCounter > 3);

  // setup low level sensitivity
  NVIC_DisableIRQ(PININT0_IRQn);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  pinintClearRiseStates(PININT, PININT_CHAN0);
  pinintClearFallStates(PININT, PININT_CHAN0);
  pinintDisableIntHigh(PININT, PININT_CHAN0);
  pinintEnableIntLow(PININT, PININT_CHAN0);
  NVIC_EnableIRQ(PININT0_IRQn);
  // change pin and trigger a few interrupts
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
  delay_cycles(1000);
  gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
  // count interrupts
  minUnitCheck(pinIntIsrCounter == 2);
  // Done
}

// TODO tests for pattern matcher