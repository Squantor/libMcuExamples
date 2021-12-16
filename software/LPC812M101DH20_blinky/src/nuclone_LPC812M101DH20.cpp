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

void crudeDelay(uint32_t iterations) {
  for (uint32_t i = iterations; i > 0; i--) {
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

void boardInit(void) {
  sysconEnableClocks(SYSCON, SYSCTL_CLOCK_SWM | SYSCTL_CLOCK_IOCON);
  // crystal oscillator pin setup
  swmEnableFixedPin(SWM, SWM_EN0_XTALIN | SWM_EN0_XTALOUT);
  IoconPinSetMode(IOCON, IOCON_XTAL_IN, PIN_MODE_INACTIVE);
  IoconPinSetMode(IOCON, IOCON_XTAL_OUT, PIN_MODE_INACTIVE);
  sysconDisableClocks(SYSCON, SYSCTL_CLOCK_SWM | SYSCTL_CLOCK_IOCON);

  // setup system clocks
  sysconSysOscControl(SYSCON, SYSOSCCTRL_FREQ_1_20MHZ);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
  crudeDelay(6000);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSPLL);
  ClockSetPLLBypass(false, false);
  SysctlPowerUp(SYSCTL_SLPWAKE_SYSOSC_PD);
  ClockSetSystemPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);
  FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);
  SysctlPowerDown(SYSCTL_SLPWAKE_SYSPLL_PD);
  ClockSetupSystemPLL(4, 1);
  SysctlPowerUp(SYSCTL_SLPWAKE_SYSPLL_PD);
  while (!ClockIsSystemPLLLocked())
    ;
  ClockSetSysClockDiv(2);
  ClockSetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);
}
