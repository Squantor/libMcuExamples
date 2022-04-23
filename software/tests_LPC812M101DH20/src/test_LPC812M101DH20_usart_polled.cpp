/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101DH20 UART peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101DH20_teardown.hpp>
#include <common.hpp>

/**
 * @brief UART setup and initialisation
 */
MINUNIT_SETUP(LPC812M101DH20SetupUsart) {
  minUnitCheck(LPC812M101DH20TeardownCorrect() == true);
}

MINUNIT_ADD(LPC812M101DH20UsartTxRx, LPC812M101DH20SetupUsart, LPC812M101DH20Teardown) {
  sysconEnableClocks(SYSCON, CLKCTRL_UART0 | CLKCTRL_SWM | CLKCTRL_IOCON);
  sysconEnableResets(SYSCON, RESETCTRL_UART0);
  SwmMovablePinAssign(SWM, SWM_USART0_TXD_O, SWM_TESTPIN_0_0);
  SwmMovablePinAssign(SWM, SWM_USART0_RXD_I, SWM_TESTPIN_0_1);
  sysconUartClockDiv(SYSCON, 1);
  // make sure we use a baud rate that is not an exact match
  minUnitCheck(usartSetBaud(USART0, 12000000, 9600) == 9615);
  usartSetConfig(USART0, DATALEN_8, PARITY_NONE, STOPLEN_1, 0);
  usartTXEnable(USART0);
  usartSendData(USART0, 0xA5);
  // loop until we got something
  int i = 0;
  while (i < 100000 && !(usartGetStatus(USART0) & USART_STAT_RXRDY)) i++;
  minUnitCheck(i < 100000);
  minUnitCheck(usartReadData(USART0) == 0xA5);
  usartTXDisable(USART0);
  usartDisable(USART0);
  SwmMovablePinAssign(SWM, SWM_USART0_TXD_O, SWM_PORTPIN_Reset);
  SwmMovablePinAssign(SWM, SWM_USART0_RXD_I, SWM_PORTPIN_Reset);
  sysconDisableClocks(SYSCON, CLKCTRL_UART0 | CLKCTRL_SWM | CLKCTRL_IOCON);
}