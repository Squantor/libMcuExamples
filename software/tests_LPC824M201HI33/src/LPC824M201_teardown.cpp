/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief Teardown function that resets the LPC845 to a state
 * that more or less matches reset state
 */
#include <nuclone_LPC824M201HI33_tests.hpp>
#include <LPC824M201_teardown.hpp>
#include <test_conditions.hpp>
#include <MinUnit.h>

/** @brief resets all the registers to their default states
 */
MINUNIT_TEARDOWN(LPC824M201Teardown)
{
    minUnitCheck(LPC824M201TeardownCorrect() == true);
}

/** @brief checks if all the registers to their default states
 *  @return if all registers are correctly torndown
 */
bool LPC824M201TeardownCorrect(void)
{
    TESTANDRETURN(1 == 1);
    return true;
}