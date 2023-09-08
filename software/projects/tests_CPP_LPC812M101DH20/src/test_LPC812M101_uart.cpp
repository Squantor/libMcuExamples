/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101 UART peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

instances::usart::usart<peripherals::USART0_cpp> testUsartPeripheral;

/**
 * @brief USART setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupUsart) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_UART0 | instances::syscon::CLOCK_SWM |
                                          instances::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_UART0);
}

MINUNIT_ADD(LPC812M101CppUsartInit, LPC812M101CppSetupUsart, LPC812M101Teardown) {
  // use C++ variants
  swmPeriperhal.setup(test0Pin, uartMainRxFunction);
  swmPeriperhal.setup(test1Pin, uartMainTxFunction);
  // undo setup
  swmPeriperhal.clear(test0Pin, uartMainRxFunction);
  swmPeriperhal.clear(test1Pin, uartMainTxFunction);
  // TODO, move this to teardown
  sysconPeripheral.disablePeripheralClocks(instances::syscon::CLOCK_UART0 | instances::syscon::CLOCK_SWM |
                                           instances::syscon::CLOCK_IOCON);
  minUnitPass();
}