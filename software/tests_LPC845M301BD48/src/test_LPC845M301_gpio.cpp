/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>

#define BITPOS(value) (1 << value)

void LPC845M301_setup_gpio()
{
    sysconEnableClocks(SYSCON, CLKCTRL0_GPIO0 | CLKCTRL0_GPIO1, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_GPIO0, 0x00);
}

MINUNIT_ADD(LPC845M301GpioPin)
{
    LPC845M301_setup_gpio();    
    gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
    gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
    gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 0);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) == 0);
    gpioPinWrite(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0, 1);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1) != 0);
    // switch around
    gpioSetPinDIRInput(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0);
    gpioSetPinDIROutput(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1);
    gpioPinWrite(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1, 0);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == 0);
    gpioPinWrite(GPIO, PORT_TESTPIN_0_1, PIN_TESTPIN_0_1, 1);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) != 0);
    LPC845M301_teardown();
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}

// same tests as pins but checking a whole port
MINUNIT_ADD(LPC845M301GpioPort)
{
    // some prerequisite tests
    minUnitCheck(PORT_TESTPIN_0_0 == PORT_TESTPIN_1_0);
    // set output as low (it is default pulled up)
    gpioSetPortDir(GPIO, PORT_TESTPIN_0_0, BITPOS(PIN_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_1_0));
    gpioPortWrite(GPIO, PORT_TESTPIN_0_0, gpioPortRead(GPIO, PORT_TESTPIN_0_0) & ~BITPOS(PIN_TESTPIN_0_0) & ~BITPOS(PIN_TESTPIN_1_0));
    // sense input changes
    minUnitCheck((gpioPortRead(GPIO, 
        PORT_TESTPIN_0_0) & (BITPOS(PIN_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_1_0))) == 0x00000000);
    // set output as high 
    gpioPortWrite(GPIO, PORT_TESTPIN_0_0, gpioPortRead(GPIO, PORT_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_1_0));
    // sense if inputs are high
    minUnitCheck((gpioPortRead(GPIO, 
        PORT_TESTPIN_0_0) & (BITPOS(PIN_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_1_0))) == (BITPOS(PIN_TESTPIN_0_0) | BITPOS(PIN_TESTPIN_1_0)));
    // switch around pins
    LPC845M301_teardown();
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}