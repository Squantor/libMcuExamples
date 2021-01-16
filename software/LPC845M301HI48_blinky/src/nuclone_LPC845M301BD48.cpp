/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48.hpp>

void boardInit(void)
{
    // clock enable!
    ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE(IOCON_MODE_INACTIVE));
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
