/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC845M301 UART peripheral polling mode
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>
#include <common.hpp>

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC845M301SetupUsart)
{
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}

MINUNIT_ADD(LPC845M301UsartTxRx, LPC845M301SetupUsart, LPC845M301Teardown)
{
    sysconEnableClocks(SYSCON, CLKCTRL0_UART0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_UART0 | RESETCTRL0_SWM | RESETCTRL0_IOCON, 0x00);
    sysconPeripheralClockSelect(SYSCON, UART0CLKSEL, CLKSRC_MAIN);
    SwmMovablePinAssign(SWM0, SWM_USART0_TXD, SWM_TESTPINT_0_0);
    SwmMovablePinAssign(SWM0, SWM_USART0_RXD, SWM_TESTPINT_0_1);
    // make sure we use a baud rate that is not an exact match
    minUnitCheck(usartSetBaud(USART0, CLOCK_MAIN, 9600) == 9615);
    usartSetConfig(USART0, DATALEN_8, PARITY_NONE, STOPLEN_1, 0);
    usartTXEnable(USART0);
    usartSendByte(USART0, 0xA5);
    // loop until we got something
    int i = 0;
    while(i < 100000)
        
    minUnitCheck(i < 100000);
    minUnitCheck(usartReadByte(USART0) == 0xA5);
    usartTXDisable(USART0);
    usartDisable(USART0);
    SwmMovablePinAssign(SWM0, SWM_USART0_TXD, SWM_PORTPIN_Reset);
    SwmMovablePinAssign(SWM0, SWM_USART0_RXD, SWM_PORTPIN_Reset);
    sysconDisableClocks(SYSCON, CLKCTRL0_UART0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
}