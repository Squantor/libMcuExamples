/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48.hpp>

void boardInit(void)
{
    sysconlPowerEnable(SYSCON, PDRUNCFG_SYSOSC | PDRUNCFG_SYSPLL);
    sysconlEnableClocks(SYSCON, CLKCTRL0_IOCON | CLKCTRL0_GPIO0 | CLKCTRL0_SWM, CLKCTRL1_NONE);
    ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_CLKOUT, IOCON_MODE_INACTIVE);
    SwmMovablePinAssign(SWM0, SWM_CLKOUT, SWM_PORTPIN_P0_12);
    swmEnableFixedPin(SWM0, SWM_EN0_XTALIN | SWM_EN0_XTALOUT, SWM_EN1_NONE);
    gpioSetPinDIROutput(GPIO, PORT_LED, PIN_LED);
    gpioPinWrite(GPIO, PORT_LED, PIN_LED, 0);
    // disable all unneeded clocks
    sysconlDisableClocks(SYSCON, CLKCTRL0_SWM, CLKCTRL1_NONE);
    // setup systick
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
