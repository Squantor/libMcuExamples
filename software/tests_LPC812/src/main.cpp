/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>
#include <MinUnit.h>

void printStringStdout( const char* string )
{
   volatile const char* data = string;
}

int main()
{
    boardInit();
    minunitRun();
    if(minunitTestState.failures != 0)
    {
        printStringStdout("Test failures detected\n");
    }
    else
    {
        printStringStdout("All tests passed\n");
    }
    while (1)
        ;
}
