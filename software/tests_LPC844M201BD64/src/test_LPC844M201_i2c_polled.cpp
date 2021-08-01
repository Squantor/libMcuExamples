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
    i2cSetClockDivider(I2C0, 5);
    i2cSetConfiguration(I2C0, I2C_CFG_MSTEN);
    // write to address 0x7 with !W/R bit unset
    i2cSetMasterData(I2C0, 0x0E);
    i2cSetMasterControl(I2C0, I2C_MSCTL_MSTSTART);
    // waiting for status
    uint32_t i2cStatus;
    int i = 0;
    do {
        i2cStatus = i2cGetStatus(I2C0);
        i++;
    } while(I2C_STAT_MSTSTATE(i2cStatus) != I2C_STAT_MSSTATE_NACK_ADDRESS && i < 1000);
    // timed out?
    minUnitCheck(i < 1000);
    minUnitCheck(I2C_STAT_MSTSTATE(i2cStatus) == I2C_STAT_MSSTATE_NACK_ADDRESS);
    swmDisableFixedPin(SWM, SWM_EN0_I2C0_SCL, SWM_EN1_NONE);
    swmDisableFixedPin(SWM, SWM_EN0_I2C0_SDA, SWM_EN1_NONE);
    sysconDisableClocks(SYSCON, CLKCTRL0_I2C0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
}