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
    Simple PWM example
*/
#include <board.hpp>
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

// minimum amount of ticks per second at 30MHz clock
#define TICKS_PER_S     (2)
#define MAX_PWM         (10)

volatile uint32_t ticks = 0;

extern "C" 
{
    void SysTick_Handler(void)
    {
        ticks++;
    }
}

void exampleSetup(void)
{
    // setup SCT out0 to pin 17
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(IOCON, IOCON_LED_0, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED_0);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    
    SctInit(LPC_SCT);
    SctConfig(LPC_SCT, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);
    // divide 30MHz bus clock by 30 to get 1MHz timebase
    SctSetControl(LPC_SCT, SCT_CTRL_BIDIR_L(1) | SCT_CTRL_PRE_L(30-1));
    SctMatchReloadL(LPC_SCT, SCT_MATCH_0, MAX_PWM-1);
    SctMatchReloadL(LPC_SCT, SCT_MATCH_1, 5);
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH)| SCT_EV_CTRL_MATCHSEL(SCT_MATCH_1));
    SctOutputSet(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    SctOutputDirCtrl(LPC_SCT, SCT_OUTPUTDIRCTRL(SCT_OUTPUT_0_VALUE, SCT_OUTPUTDIRCTRL_L));
    SctClearControl(LPC_SCT, SCT_CTRL_HALT_L);
}

void exampleLoop(void)
{
    static uint16_t brightness = 5;
    static uint32_t currentTicks = 0;
    // if a tick has elapsed
    if(currentTicks != ticks)
    {
        // increase brightness
        currentTicks = ticks;
        brightness++;
        if(brightness > MAX_PWM)
        {
            brightness = 0;
        }
        SctMatchReloadL(LPC_SCT, SCT_MATCH_1, brightness);
    }
}