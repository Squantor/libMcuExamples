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
#define TICKS_PER_S         (2)

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
    IoconPinSetMode(LPC_IOCON, IOCON_LED, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    
    SctInit(LPC_SCT);
    LPC_SCT->CONFIG |= (1 << 17);
    // divide 30MHz bus clock by 30 to get 1MHz timebase
    LPC_SCT->CTRL_L |= (30-1) << 5;
    LPC_SCT->MATCHREL[0].L = 10-1;
    LPC_SCT->MATCHREL[1].L = 1;
    LPC_SCT->EV[0].STATE = 0xFFFF;
    LPC_SCT->EV[0].CTRL = (1 << 12);
    LPC_SCT->EV[1].STATE = 0xFFFF;
    LPC_SCT->EV[1].CTRL = (1 << 0) | (1 << 12);
    LPC_SCT->OUT[0].SET = (1 << 0);
    LPC_SCT->OUT[0].CLR = (1 << 1);
    LPC_SCT->CTRL_L &= ~(1 << 2);

}

void exampleLoop(void)
{
    static uint16_t brightness = 0;
    static uint32_t currentTicks = 0;
    if(currentTicks != ticks)
    {
        currentTicks = ticks;
        brightness++;
        if(brightness > 9)
        {
            brightness = 0;
        }
        LPC_SCT->MATCHREL[1].L = brightness;
    }
}