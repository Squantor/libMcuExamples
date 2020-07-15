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
    blink pin at 1 Hz using the match toggle
*/
#include <board.hpp>
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

void exampleSetup(void)
{
    // setup SCT out0 to pin 17
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(LPC_IOCON, IOCON_LED, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);

    SctInit(LPC_SCT);
    //LPC_SCT->CONFIG |= (1 << 17);
    SctConfig(LPC_SCT, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);
    // divide clock by 250 to get a 120Khz rate
    //LPC_SCT->CTRL_L |= (249 << 5);
    // TODO make low control set
    SctSetControlU(LPC_SCT, SCT_CTRL_PRE_L(249));
    // 2Hz rate
    //LPC_SCT->MATCHREL[0].L = 60000-1;
    SctMatchReloadL(LPC_SCT, SCT_MATCH_0, 60000-1);

    //LPC_SCT->EV[0].STATE = 0xFFFF;
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    //LPC_SCT->EV[0].CTRL = (1 << 12);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));

    //LPC_SCT->OUT[0].SET = (1 << 0);
    SctSetOutputSet(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    //LPC_SCT->OUT[0].CLR = (1 << 0);
    SctSetOutputClear(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    //LPC_SCT->RES = (3 << 0);
    SctSetupConflictResolution(LPC_SCT, SCT_RES(SCT_OUTPUT_0_VALUE, SCT_RES_TOGGLE));

    //LPC_SCT->CTRL_L &= ~(1 << 2);
    SctClearControlL(LPC_SCT, SCT_CTRL_HALT_L);
}

void exampleLoop(void)
{
    __NOP();
}