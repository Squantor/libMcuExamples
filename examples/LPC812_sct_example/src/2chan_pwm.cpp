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
    // setup SCT out0,1,2 to pin 17,13,12
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(LPC_IOCON, IOCON_LED_0, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_LED_1, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_LED_2, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_BUTTON, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED_0);
    SwmMovablePinAssign(SWM_CTOUT_1_O, PIN_LED_1);
    SwmMovablePinAssign(SWM_CTIN_0_I, PIN_BUTTON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_GPIO);
    GpioSetPinDIROutput(LPC_GPIO_PORT, 0, PIN_TOGGLE);

    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    
    SctInit(LPC_SCT);
    SctControl(LPC_SCT, SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_U);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_0, 30000000);    // cycle speed
    SctMatchReloadU(LPC_SCT, SCT_MATCH_1, 20000000);    // LED 1 off
    SctMatchReloadU(LPC_SCT, SCT_MATCH_2, 10000000);    // LED 1 on
    SctMatchReloadU(LPC_SCT, SCT_MATCH_3, 20000000);    // LED 0 off
    SctMatchReloadU(LPC_SCT, SCT_MATCH_4, 10000000);    // LED 0 on
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) |
        SCT_EV_CTRL_IOCOND(SCT_IOCOND_LOW) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_AND) |
        SCT_EV_CTRL_STATEV(SCT_STATE_1_VAL) |
        SCT_EV_CTRL_STATELD_LOAD );
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_1_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_1_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_3) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) );
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_2_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_2_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_4) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) );
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_3_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_3_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) |
        SCT_EV_CTRL_IOCOND(SCT_IOCOND_HIGH) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_AND) |
        SCT_EV_CTRL_STATEV(SCT_STATE_0_VAL) |
        SCT_EV_CTRL_STATELD_LOAD );
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_4_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_4_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_3) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) );
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_5_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_5_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_4) |
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) );    
    

    
}

void exampleLoop(void)
{
    static uint32_t currentTicks = 5;
    // virtual button that gets pressed 5 seconds
    // wait for 10 ticks to elapse
    if(currentTicks < ticks)
    {
        currentTicks = ticks+5;
        GpioSetPinToggle(LPC_GPIO_PORT, 0, PIN_TOGGLE);
    }
}