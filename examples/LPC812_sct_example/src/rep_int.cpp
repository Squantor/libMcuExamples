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
    Repetitive interrupt example at 1 Hz
*/
#include <board.hpp>
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

volatile static uint32_t interruptCounter = 0;

extern "C" {
    void SCT_IRQHandler(void)
    {
        interruptCounter++;
        SctClearEventFlag(LPC_SCT, SCT_EVT_0_BIT);
    }
}

void setupSct(void)
{
    SctInit(LPC_SCT);
    SctConfig(LPC_SCT, SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_U);
    // set interrupt rate to one second
    SctSetMatchReload(LPC_SCT, SCT_MATCH_0, ClockGetSystemClockRate());
    // allow event in all states
    SctSetEventStateMask(LPC_SCT, SCT_EVT_0_VAL, 0x03);
    SctSetEventControl(LPC_SCT, SCT_EVT_0_VAL, SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) | SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0));
    
    SctEnableEventInt(LPC_SCT, SCT_EVT_0_BIT);
    NVIC_EnableIRQ(SCT_IRQn);
    // clear sct halt to run the timer
    SctClearControl(LPC_SCT, SCT_CTRL_HALT_L);
}

void exampleLoop(void)
{
    
}