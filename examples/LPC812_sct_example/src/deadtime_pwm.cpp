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
#define MAX_DUTY        (10)

#define PWM_DUTY_0      (130)
#define PWM_DUTY_1      (135)
#define PWM_PERIOD      (180)



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
    IoconPinSetMode(LPC_IOCON, IOCON_LED_0, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_LED_1, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_BUTTON, PIN_MODE_PULLUP);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED_0);
    SwmMovablePinAssign(SWM_CTOUT_1_O, PIN_LED_1);
    SwmMovablePinAssign(SWM_CTIN_0_I, PIN_BUTTON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
       
    SctInit(LPC_SCT);
    SctConfig(LPC_SCT, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);
    SctMatchCountL(LPC_SCT, SCT_MATCH_0, PWM_PERIOD);
    SctMatchReloadL(LPC_SCT, SCT_MATCH_0, PWM_PERIOD);
    SctMatchCountL(LPC_SCT, SCT_MATCH_1, PWM_DUTY_0);
    SctMatchReloadL(LPC_SCT, SCT_MATCH_1, PWM_DUTY_0);
    SctMatchCountL(LPC_SCT, SCT_MATCH_2, PWM_DUTY_1);
    SctMatchReloadL(LPC_SCT, SCT_MATCH_2, PWM_DUTY_1);

    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, SCT_EV_CTRL_IOCOND(SCT_IOCOND_FALL) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_IO));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_1_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_1_VAL, SCT_EV_CTRL_IOCOND(SCT_IOCOND_RISE) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_IO));

    SctSetEventStateMask(LPC_SCT, SCT_EVENT_2_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_2_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_1) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_3_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_3_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_2) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));

    
}

void exampleLoop(void)
{
    static uint16_t dutycycle = 5;
    static uint32_t currentTicks = 0;
    // if a tick has elapsed
    if(currentTicks != ticks)
    {
        // increase brightness
        currentTicks = ticks;
        dutycycle++;
        if(dutycycle > MAX_DUTY)
        {
            dutycycle = 0;
        }
        SctMatchReloadL(LPC_SCT, SCT_MATCH_1, dutycycle);
    }
}