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
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

void setupRepetitiveInterrupt(void)
{
    LPC_SCT->CONFIG = (1 << 0) | (1 << 17); // unified 32-bit timer, auto limit
    LPC_SCT->MATCHREL[0].U = ClockGetSystemClockRate()/1; // match 0 @ 100 Hz = 10 msec
    LPC_SCT->EV[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
    LPC_SCT->EV[0].CTRL = (1 << 12); // match 0 condition only
    
    LPC_SCT->EVEN = (1 << 0); // event 0 generates an interrupt
    NVIC_EnableIRQ(SCT_IRQn); // enable SCTimer/PWM interrupt
    LPC_SCT->CTRL_U &= ~(1 << 2); // unhalt by clearing bit 2 of the CTRL
}