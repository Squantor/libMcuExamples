/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC824M201HI33_tests.hpp>

void crudeDelay(uint32_t iterations)
{
    for(uint32_t i = iterations; i > 0; i--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

void boardInit(void)
{
    sysconEnableClocks(SYSCON, CLKCTRL_IOCON | CLKCTRL_SWM);
    // setup crystal oscillator to run core at 12MHz
    ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE_INACTIVE);
    swmEnableFixedPin(SWM, SWM_EN0_XTALIN | SWM_EN0_XTALOUT);
    sysconSysOscControl(SYSCON, SYSOSCCTRL_FREQ_1_20MHZ);
    sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
    // wait until crystal oscillator stabilizes
    crudeDelay(6000);
    sysconSysPllClockSelect(SYSCON, SYSPLLCLKSEL_SYSOSC);
    sysconMainClockSelect(SYSCON, MAINCLKSEL_PLL_IN);
    // setup clock output
    //sysconClkoutSource(SYSCON, CLKOUT_SYSOSC);
    //sysconClkoutDivider(SYSCON, 1);
    //SwmMovablePinAssign(SWM, SWM_CLKOUT_O, SWM_PORTPIN_P0_1);
    // disable all unneeded clocks
    sysconDisableClocks(SYSCON, CLKCTRL_IOCON | CLKCTRL_SWM);
    // setup systick
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
