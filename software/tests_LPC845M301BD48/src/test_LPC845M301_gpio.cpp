/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>

MINUNIT_ADD(LPC845M301GpioPins)
{
    // set output as low (it is default pulled up)
    // sense if inputs are low
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