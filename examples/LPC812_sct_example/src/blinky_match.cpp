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
/*
    blink pin at 1 Hz
*/
#include <board.hpp>
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

void setupSct(void)
{
    // setup SCT out0 to pin 17
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(LPC_IOCON, IOCON_LED, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);

    SctInit(LPC_SCT);    
    //LPC_SCT->CONFIG |= 1;
    SctConfig(LPC_SCT, SCT_CONFIG_32BIT_COUNTER);
    //LPC_SCT->MATCHREL[0].U = ClockGetSystemClockRate();
    SctSetMatchReload(LPC_SCT, SCT_MATCH_0, ClockGetSystemClockRate());
    // LPC_SCT->EV[0].STATE = (1 << 0);
    SctSetEventStateMask(LPC_SCT, SCT_EVT_0_VAL, SCT_STATE_0_BIT);
    //LPC_SCT->EV[0].CTRL = (0 << 0) | (1 << 12) | (1 << 14) | (1 << 15);
    SctSetEventControl(LPC_SCT, SCT_EVT_0_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) | 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) |
        SCT_EV_CTRL_STATELD_LOAD | 
        SCT_EV_CTRL_STATEV(SCT_STATE_1_VAL));
    //LPC_SCT->EV[1].STATE = (1 << 1);
    SctSetEventStateMask(LPC_SCT, SCT_EVT_1_VAL, SCT_STATE_1_BIT);
    //LPC_SCT->EV[1].CTRL = (0 << 0) | (1 << 12) | (1 << 14) | (0 << 15);
    SctSetEventControl(LPC_SCT, SCT_EVT_1_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) | 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) |
        SCT_EV_CTRL_STATELD_LOAD | 
        SCT_EV_CTRL_STATEV(SCT_STATE_0_VAL));
    //LPC_SCT->OUT[0].SET = (1 << 0);
    SctSetOutputSet(LPC_SCT, SCT_OUT_0_VALUE, SCT_EVT_0_BIT);
    //LPC_SCT->OUT[0].CLR = (1 << 1);
    SctSetOutputClear(LPC_SCT, SCT_OUT_0_VALUE, SCT_EVT_1_BIT);
    //LPC_SCT->LIMIT_L = 0x0003;
    SctSetLimitL(LPC_SCT, SCT_EVT_0_BIT | SCT_EVT_1_BIT);
    SctClearControl(LPC_SCT, SCT_CTRL_HALT_L);
}