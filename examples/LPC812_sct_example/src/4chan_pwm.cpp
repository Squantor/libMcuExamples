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

// PWM cycle values
#define PWM_VAL1    (400000)
#define PWM_VAL2    (500000)
#define PWM_VAL3    (100000)
#define PWM_VAL4    (900000)
#define PWM_CYCLE   (1000000)

volatile uint32_t ticks = 0;

extern "C" 
{
    void SysTick_Handler(void)
    {
        ticks++;
    }

    void SCT_IRQHandler(void)
    {
        SctClearEventFlag(LPC_SCT, SCT_EVENT_0_BIT);
        SctClearEventFlag(LPC_SCT, SCT_EVENT_5_BIT);
        __NOP();
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
    IoconPinSetMode(LPC_IOCON, IOCON_LED_3, PIN_MODE_INACTIVE);
    IoconPinSetMode(LPC_IOCON, IOCON_BUTTON, PIN_MODE_PULLUP);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED_0);
    SwmMovablePinAssign(SWM_CTOUT_1_O, PIN_LED_1);
    SwmMovablePinAssign(SWM_CTOUT_2_O, PIN_LED_2);
    SwmMovablePinAssign(SWM_CTOUT_3_O, PIN_LED_3);
    SwmMovablePinAssign(SWM_CTIN_0_I, PIN_BUTTON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_GPIO);
    GpioSetPinDIROutput(LPC_GPIO_PORT, 0, PIN_TOGGLE);

    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    
    SctInit(LPC_SCT);

    SctSetConfig(LPC_SCT, SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_U);
    
    SctMatchU(LPC_SCT, SCT_MATCH_0, PWM_CYCLE);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_0, PWM_CYCLE);
    SctMatchU(LPC_SCT, SCT_MATCH_1, PWM_VAL1);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_1, PWM_VAL1);
    SctMatchU(LPC_SCT, SCT_MATCH_2, PWM_VAL2);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_2, PWM_VAL2);
    SctMatchU(LPC_SCT, SCT_MATCH_3, PWM_VAL3);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_3, PWM_VAL3);
    SctMatchU(LPC_SCT, SCT_MATCH_4, PWM_VAL4);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_4, PWM_VAL4);

    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_1_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_1_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_1) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_2_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_2_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_2) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_3_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_3_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_3) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_4_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_4_VAL, SCT_EV_CTRL_MATCHSEL(SCT_MATCH_4) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_5_VAL, SCT_STATE_0_BIT | SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_5_VAL, SCT_EV_CTRL_IOCOND(SCT_IOCOND_LOW) | SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_IO));

    SctOutputSet(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_1_BIT | SCT_EVENT_5_BIT);
    SctOutputSet(LPC_SCT, SCT_OUTPUT_1_VALUE, SCT_EVENT_0_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_1_VALUE, SCT_EVENT_2_BIT | SCT_EVENT_5_BIT);
    SctOutputSet(LPC_SCT, SCT_OUTPUT_2_VALUE, SCT_EVENT_3_BIT | SCT_EVENT_5_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_2_VALUE, SCT_EVENT_0_BIT);
    SctOutputSet(LPC_SCT, SCT_OUTPUT_2_VALUE, SCT_EVENT_4_BIT | SCT_EVENT_5_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_2_VALUE, SCT_EVENT_0_BIT);
    SctOutput(LPC_SCT, 
        SCT_OUTPUT_STATE(SCT_OUTPUT_0_VALUE, 0) |
        SCT_OUTPUT_STATE(SCT_OUTPUT_1_VALUE, 0) |
        SCT_OUTPUT_STATE(SCT_OUTPUT_2_VALUE, 1) |
        SCT_OUTPUT_STATE(SCT_OUTPUT_3_VALUE, 1) );
    SctConflictResolution(LPC_SCT, 
        SCT_CONFLICTRES(SCT_OUTPUT_0_VALUE, SCT_CONFLICTRES_CLEAR) |
        SCT_CONFLICTRES(SCT_OUTPUT_1_VALUE, SCT_CONFLICTRES_CLEAR) |
        SCT_CONFLICTRES(SCT_OUTPUT_2_VALUE, SCT_CONFLICTRES_SET) |
        SCT_CONFLICTRES(SCT_OUTPUT_3_VALUE, SCT_CONFLICTRES_SET) );
    SctHaltU(LPC_SCT, SCT_EVENT_5_BIT);
    SctLimitU(LPC_SCT, SCT_EVENT_5_BIT);

    SctEventInt(LPC_SCT, SCT_EVENT_0_BIT | SCT_EVENT_5_BIT);

    NVIC_EnableIRQ(SCT_IRQn);

    SctClearControl(LPC_SCT, SCT_CTRL_HALT_U);

}

void exampleLoop(void)
{
    static uint32_t currentTicks = 5;
    // virtual button that gets pressed 5 seconds
    // wait for 10 ticks to elapse
    if(currentTicks < ticks)
    {
        currentTicks = ticks+5;
    }
}