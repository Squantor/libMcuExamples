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
#define MAX_DUTY        (180)

#define PWM_DUTY_0      (130)
#define PWM_DUTY_1      (140)
#define PWM_PERIOD      (180)



volatile uint32_t ticks = 0;

extern "C" 
{
    void SysTick_Handler(void)
    {
        ticks++;
    }

    void SCT_IRQHandler(void)
    {
        __NOP();
        SctClearEventFlag(LPC_SCT, SCT_EVENT_1_BIT);
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
    ClockEnablePeriphClock(SYSCTL_CLOCK_GPIO);
    GpioSetPinDIROutput(LPC_GPIO_PORT, 0, PIN_TOGGLE);
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
       
    SctInit(LPC_SCT);

    SctConfig(LPC_SCT, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);
    SctSetControl(LPC_SCT, SCT_CTRL_BIDIR_L(1));

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

    SctOutputSet(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT | SCT_EVENT_2_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_2_BIT);
    SctOutputSet(LPC_SCT, SCT_OUTPUT_1_VALUE, SCT_EVENT_3_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_1_VALUE, SCT_EVENT_0_BIT | SCT_EVENT_3_BIT);
    SctConflictResolution(LPC_SCT, 
        SCT_CONFLICTRES(SCT_OUTPUT_0_VALUE, SCT_CONFLICTRES_TOGGLE) | 
        SCT_CONFLICTRES(SCT_OUTPUT_1_VALUE, SCT_CONFLICTRES_TOGGLE) );
    SctOutput(LPC_SCT, SCT_OUTPUT_STATE(SCT_OUTPUT_0_VALUE, 1) | SCT_OUTPUT_STATE(SCT_OUTPUT_1_VALUE, 0));

    SctStopL(LPC_SCT, SCT_EVENT_0_BIT);
    SctEventInt(LPC_SCT, SCT_EVENT_1_BIT);
    SctStartL(LPC_SCT, SCT_EVENT_1_BIT);

    NVIC_EnableIRQ(SCT_IRQn);

    SctClearControl(LPC_SCT, SCT_CTRL_HALT_L);
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
        dutycycle+=10;
        if(dutycycle > MAX_DUTY-20)
        {
            dutycycle = 0;
            // toggle to shut down PWM outputs
            GpioSetPinToggle(LPC_GPIO_PORT, 0, PIN_TOGGLE);
        }
        SctSetConfig(LPC_SCT, SCT_CONFIG_NORELOAD_L);
        SctMatchReloadL(LPC_SCT, SCT_MATCH_1, dutycycle+1);
        SctMatchReloadL(LPC_SCT, SCT_MATCH_2, dutycycle+9);
        SctClearConfig(LPC_SCT, SCT_CONFIG_NORELOAD_L);
    }
}