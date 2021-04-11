/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC845M301 IOCON peripheral
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC845M301SetupIocon)
{
    minUnitCheck(LPC845M301TeardownCorrect() == true); // check if the MCU is in its reset state
    sysconEnableClocks(SYSCON, CLKCTRL0_GPIO0 | CLKCTRL0_GPIO1 | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_GPIO0, 0x00);
}

/**
 * @brief tests for the IOCON pullup and down function
 */
MINUNIT_ADD(LPC845M301IoconPull, LPC845M301SetupIocon, LPC845M301Teardown)
{
    // setup sensing GPIO to inputs
    // check if high (Default pullups on LPC)
    // set iocon to pulldowns
    // check if low
    // set iocon to pullups
    // check if high
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC845M301IoconRepeater, LPC845M301SetupIocon, LPC845M301Teardown)
{
    
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC845M301IoconOpenDrain, LPC845M301SetupIocon, LPC845M301Teardown)
{
    
}

/* Some tests that are still to do:
* Test glitch filtering, depends on timer subsystem
* Analog pin tests, depends on ADC/Comparator
*/