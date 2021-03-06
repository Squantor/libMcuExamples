/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>
#include <MinUnit.h>
#include <stream_uart.hpp>

void minunitReport( const char* string )
{
   dsPuts(&streamUart, string);
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
        ;
}
