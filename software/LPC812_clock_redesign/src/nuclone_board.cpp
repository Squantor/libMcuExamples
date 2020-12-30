/*
MIT License

Copyright (c) 2020 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <board.hpp>

// set CPU frequency to outFreq using xtal frequency
void setupXtalClocking()
{
	/* EXT oscillator < 15MHz */
	ClockSetPLLBypass(false, false);

	// Turn on the SYSOSC by clearing the power down bit
	SysctlPowerUp(SYSCTL_SLPWAKE_SYSOSC_PD);

	// Select the PLL input to the external oscillator
	ClockSetSystemPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);

	// Setup FLASH access to 2 clocks (up to 30MHz)
	FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);

	// Power down PLL to change the PLL divider ratio
	SysctlPowerDown(SYSCTL_SLPWAKE_SYSPLL_PD);

	// Setup PLL dividers ((FCLKIN = 12MHz) * 5)/2 = 30MHz 
	ClockSetupSystemPLL(4, 1);

	// Turn on the PLL by clearing the power down bit
	SysctlPowerUp(SYSCTL_SLPWAKE_SYSPLL_PD);

	// Wait for PLL to lock
	while (!ClockIsSystemPLLLocked()) {}

	// set AHB clock divider
	ClockSetSysClockDiv(2);

	// Set main clock source to the system PLL.
	ClockSetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);
}

void boardInit(void)
{
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
	ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
	
    SwmMovablePinAssign(SWM_CLKOUT_O, PIN_CLOCK_OUT);
	SwmFixedPinEnable(SWM_FIXED_XTALIN, true);
	SwmFixedPinEnable(SWM_FIXED_XTALOUT, true);

	IoconPinSetMode(LPC_IOCON, IOCON_XTAL_IN, PIN_MODE_INACTIVE);
	IoconPinSetMode(LPC_IOCON, IOCON_XTAL_OUT, PIN_MODE_INACTIVE);

    ClockSetCLKOUTSource(SYSCTL_CLKOUTSRC_MAINSYSCLK, 2);
	ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    // Setup clocking
    setupXtalClocking();
    // Setup Pin muxing/settings
}
