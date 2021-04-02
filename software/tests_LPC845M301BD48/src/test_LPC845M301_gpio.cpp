/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>

void LPC845M301_setup_gpio()
{
    sysconEnableClocks(SYSCON, CLKCTRL0_GPIO0, CLKCTRL1_NONE);
}

MINUNIT_ADD(LPC845M301GpioPin)
{
    LPC845M301_setup_gpio();    
    // set output as low (it is default pulled up)
    gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
    gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
    gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PORT_TESTPIN_0_0, 0);
    // sense if inputs are low
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == 0);
    // set output as high 
    // sense if inputs are high
    // switch around pins
    LPC845M301_teardown();
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}

// same tests as pins but checking a whole port
MINUNIT_ADD(LPC845M301GpioPort)
{
    // set output as low (it is default pulled up)
    // sense if inputs are low
    // set output as high 
    // sense if inputs are high
    // switch around pins
    LPC845M301_teardown();
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}