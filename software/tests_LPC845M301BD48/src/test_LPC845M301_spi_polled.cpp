/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC845M301 SPI peripheral polling mode
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>
#include <common.hpp>

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC845M301SetupSpi)
{
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}

MINUNIT_ADD(LPC845M301SpiRxTx, LPC845M301SetupSpi, LPC845M301Teardown)
{
    sysconEnableClocks(SYSCON, CLKCTRL0_SPI0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_SPI0 | RESETCTRL0_SWM | RESETCTRL0_IOCON, RESETCTRL1_NONE);
    sysconPeripheralClockSelect(SYSCON, SPI0CLKSEL, CLKSRC_MAIN);
    SwmMovablePinAssign(SWM0, SWM_SPI0_MOSI, SWM_TESTPIN_0_0);
    SwmMovablePinAssign(SWM0, SWM_SPI0_MISO, SWM_TESTPIN_0_1);
    SwmMovablePinAssign(SWM0, SWM_SPI0_SCK, SWM_TESTPIN_1_0);
    SwmMovablePinAssign(SWM0, SWM_SPI0_SSEL0, SWM_TESTPIN_2);
    spiSetConfig(SPI0, SPI_CFG_ENABLE | SPI_CFG_MASTER);
    spiSetDelays(SPI0, SPI_DLY_PRE(1) | SPI_DLY_POST(2) | SPI_DLY_FRAME(3) | SPI_DLY_TRANSFER(4));
    minUnitCheck(SPI0->DLY == 0x00004321);
    minUnitCheck(spiSetGetStatus(SPI0, 0x0) == 0x102);
    SwmMovablePinAssign(SWM0, SWM_SPI0_SSEL0, SWM_PORTPIN_Reset);
    SwmMovablePinAssign(SWM0, SWM_SPI0_MOSI, SWM_PORTPIN_Reset);
    SwmMovablePinAssign(SWM0, SWM_SPI0_MISO, SWM_PORTPIN_Reset);
    SwmMovablePinAssign(SWM0, SWM_SPI0_SCK, SWM_PORTPIN_Reset);
    sysconDisableClocks(SYSCON, CLKCTRL0_UART0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
}