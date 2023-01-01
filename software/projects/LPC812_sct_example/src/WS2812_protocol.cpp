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
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(IOCON, IOCON_SPI_MOSI, PIN_MODE_INACTIVE);
    IoconPinSetMode(IOCON, IOCON_SPI_SCK, PIN_MODE_INACTIVE);
    IoconPinSetMode(IOCON, IOCON_WS2812_OUT, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_SPI0_MOSI_IO, PIN_SPI_MOSI);
    SwmMovablePinAssign(SWM_SPI1_SCK_IO, PIN_SPI_SCK);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_WS2812_OUT);
    // connect the SCT inputs to the SPI outputs
    SwmMovablePinAssign(SWM_CTIN_0_I, PIN_SPI_SCK);
    SwmMovablePinAssign(SWM_CTIN_1_I, PIN_SPI_MOSI);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_GPIO);

    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
    
    SctInit(LPC_SCT);

}

#define TICKS_DELAY_ABORT   5

void exampleLoop(void)
{
    static uint32_t currentTicks = 5;
    // virtual button that gets pressed 5 seconds
    // wait for 10 ticks to elapse
    if(currentTicks < ticks)
    {
        currentTicks = ticks + TICKS_DELAY_ABORT;
    }
}