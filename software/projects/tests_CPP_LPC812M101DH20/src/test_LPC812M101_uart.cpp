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

using namespace registers::usart;
using namespace instances::usart;

registers::usart::registers *const dutRegisters{reinterpret_cast<registers::usart::registers *>(peripherals::USART0_cpp)};

/**
 * @brief USART setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupUsart) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  swmPeriperhal.setup(test0Pin, uartMainRxFunction);
  swmPeriperhal.setup(test1Pin, uartMainTxFunction);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_UART0 | instances::syscon::CLOCK_SWM |
                                          instances::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_UART0);
}

MINUNIT_ADD(LPC812M101CppUsartInit, LPC812M101CppSetupUsart, LPC812M101Teardown) {
  uint32_t realBaudRate;
  realBaudRate = usartPeripheral.init(115200);
  minUnitCheck(realBaudRate == 117187);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == (CFG::ENABLE | uartLength::SIZE_8 | uartParity::NONE | uartStop::STOP_1));
  dutRegisters->CFG = 0x00000000;
  realBaudRate = usartPeripheral.init(9600, uartLength::SIZE_7, uartParity::EVEN, uartStop::STOP_2);
  minUnitCheck(realBaudRate == 9615);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == (CFG::ENABLE | uartLength::SIZE_7 | uartParity::EVEN | uartStop::STOP_2));
}
