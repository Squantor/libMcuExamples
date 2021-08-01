/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC844M201 SPI peripheral polling mode
 */
#include <nuclone_LPC844M201BD64_tests.hpp>
#include <MinUnit.h>
#include <LPC844M201_teardown.hpp>
#include <common.hpp>

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC844M201SetupI2C)
{
    minUnitCheck(LPC844M201TeardownCorrect() == true);
}

MINUNIT_ADD(LPC844M201I2CWriteNoAck, LPC844M201SetupI2C, LPC844M201Teardown)
{
    sysconEnableClocks(SYSCON, CLKCTRL0_I2C0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_I2C0 | RESETCTRL0_SWM | RESETCTRL0_IOCON, RESETCTRL1_NONE);
    ioconSetupPin(IOCON, IOCON_I2C_SCL_OUT, IOCON_I2CMODE_STD);
    ioconSetupPin(IOCON, IOCON_I2C_SDA_OUT, IOCON_I2CMODE_STD);
    swmEnableFixedPin(SWM, SWM_EN0_I2C0_SCL, SWM_EN1_NONE);
    swmEnableFixedPin(SWM, SWM_EN0_I2C0_SDA, SWM_EN1_NONE);
    sysconPeripheralClockSelect(SYSCON, I2C0CLKSEL, CLKSRC_MAIN);
    i2cSetClockDivider(I2C0, CLOCK_AHB / I2C_TEST_FREQ);
    minUnitCheck(1 == 1);
    sysconDisableClocks(SYSCON, CLKCTRL0_I2C0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
}