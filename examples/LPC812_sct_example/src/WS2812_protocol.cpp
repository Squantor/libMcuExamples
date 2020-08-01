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
    }
}

void exampleSetup(void)
{
    // setup SCT out0,1,2,2 to pin 17,13,12,14
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

}

#define TICKS_DELAY_ABORT   5

void exampleLoop(void)
{
    static bool pinstate = true;
    static uint32_t currentTicks = 5;
    // virtual button that gets pressed 5 seconds
    // wait for 10 ticks to elapse
    if(currentTicks < ticks)
    {
        currentTicks = ticks + TICKS_DELAY_ABORT;
    }
}