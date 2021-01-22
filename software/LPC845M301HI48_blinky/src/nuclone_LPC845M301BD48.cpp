/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48.hpp>

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
    sysconEnableClocks(SYSCON, CLKCTRL0_IOCON | CLKCTRL0_GPIO0 | CLKCTRL0_SWM, CLKCTRL1_NONE);
    ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE_INACTIVE);
    swmEnableFixedPin(SWM0, SWM_EN0_XTALIN | SWM_EN0_XTALOUT, SWM_EN1_NONE);
    ioconSetupPin(IOCON, IOCON_CLKOUT, IOCON_MODE_INACTIVE);
    sysconSysOscControl(SYSCON, SYSOSCCTRL_FREQ_1_20MHZ);
    sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
    crudeDelay(6000);
    sysconExternalClockSelect(SYSCON, EXTCLKSEL_SYSOSC);
    sysconMainClockSelect(SYSCON, MAINCLKSEL_EXTCLK);
    SwmMovablePinAssign(SWM0, SWM_CLKOUT, SWM_PORTPIN_CLKOUT);
    gpioSetPinDIROutput(GPIO, PORT_LED, PIN_LED);
    gpioSetPinDIROutput(GPIO, PORT_LED, PIN_CLKOUT);
    gpioPinWrite(GPIO, PORT_LED, PIN_LED, 0);
    gpioPinWrite(GPIO, PORT_LED, PIN_CLKOUT, 0);
    // disable all unneeded clocks
    sysconDisableClocks(SYSCON, CLKCTRL0_SWM, CLKCTRL1_NONE);
    // setup SCKOUT
    sysconClkoutDivider(SYSCON, 1);
    sysconClkoutSource(SYSCON, CLKOUT_MAIN);
    // setup systick
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
