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
    sysconEnableClocks(SYSCON, CLKCTRL0_UART0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_UART0 | RESETCTRL0_SWM | RESETCTRL0_IOCON, 0x00);
}

MINUNIT_ADD(LPC845M301UsartTxRx, LPC845M301SetupUsart, LPC845M301Teardown)
{
    // setup UART baud rate
   
    // enable UART
    // Tx
    // check Rx
}