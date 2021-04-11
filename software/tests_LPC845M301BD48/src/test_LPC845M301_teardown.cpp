/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC845M301 teardown
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>

MINUNIT_ADD(LPC845M301teardown, NULL, NULL)
{
    LPC845M301Teardown();
    minUnitCheck(LPC845M301TeardownCorrect() == true);
}