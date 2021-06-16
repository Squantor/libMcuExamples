/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main test entry point for LPC812 libMcuLL tests
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <stream_uart.hpp>

volatile int var;

extern "C" 
{
    void SysTick_Handler(void)
    {

    }
}

void minunitReport( const char* string )
{

}

int main()
{
    boardInit();
    minunitRun();
    if(minunitTestState.failures != 0)
    {
        minunitReport("Test failures detected\n");
    }
    else
    {
        minunitReport("All tests passed\n");
    }
    while (1)
        __BKPT(0xFE);
}
