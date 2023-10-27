/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 UART peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

using namespace libMcuLL::sw::usart;
using namespace libMcuLL::hw::usart;

static constexpr libMcuLL::hwAddressType usart0Address = libMcuLL::hw::USART0_cpp;
libMcuLL::hw::usart::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::usart::peripheral *>(usart0Address)};

/**
 * @brief USART setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupUsartSync) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  swmPeriperhal.setup(test0Pin, uartMainRxFunction);
  swmPeriperhal.setup(test1Pin, uartMainTxFunction);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_UART0 | libMcuLL::sw::syscon::CLOCK_SWM |
                                          libMcuLL::sw::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_UART0);
}

MINUNIT_ADD(LPC812M101CppUsartSyncInit, LPC812M101CppSetupUsartSync, LPC812M101Teardown) {
  uint32_t realBaudRate;
  realBaudRate = usartPeripheral.init(115200);
  minUnitCheck(realBaudRate == 117187);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == (CFG::ENABLE | uartLength::SIZE_8 | uartParity::NONE | uartStop::STOP_1));
  dutRegisters->CFG = 0x00000000;
  realBaudRate = usartPeripheral.init(9600, uartLength::SIZE_7, uartParity::EVEN, uartStop::STOP_2);
  minUnitCheck(realBaudRate == 9615);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == (CFG::ENABLE | uartLength::SIZE_7 | uartParity::EVEN | uartStop::STOP_2));
}

MINUNIT_ADD(LPC812M101CppUsartSyncComms, LPC812M101CppSetupUsartSync, LPC812M101Teardown) {
  uint32_t data, status;
  int timeout;
  usartPeripheral.init(115200);
  sysconPeripheral.setUsartClockDivider(1);
  minUnitCheck((dutRegisters->STAT & STAT::MASK) == 0x0000000E);
  minUnitCheck(usartPeripheral.status() & uartStatus::TXRDY);
  usartPeripheral.write(0xA5);
  timeout = 0xFFFF;
  while (timeout > 0 && !(usartPeripheral.status() & uartStatus::RXRDY)) {
    timeout--;
  }
  minUnitCheck(timeout > 0);
  minUnitCheck(usartPeripheral.status() & uartStatus::RXRDY);
  usartPeripheral.read(data);
  minUnitCheck(data == 0xA5);
  for (uint32_t i = 0; i < 256; i++) {
    usartPeripheral.write(i);
    timeout = 0xFFFF;
    while (timeout > 0 && !(usartPeripheral.status() & uartStatus::RXRDY)) {
      timeout--;
    }
    minUnitCheck(timeout > 0);
    minUnitCheck(usartPeripheral.status() & uartStatus::RXRDY);
    usartPeripheral.read(data, status);
    minUnitCheck(data == i);
    minUnitCheck(status == 0x00000000);
  }
}