/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef LPC845M301_TEARDOWN_HPP
#define LPC845M301_TEARDOWN_HPP


/** @brief resets all the registers to their default states
 * 
 */
void LPC845M301Teardown(void);


/** @brief checks if all registers are in their default states
 *  @return false if a register is not properly set
 */
bool LPC845M301TeardownCorrect(void);

#endif