/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>

void boardInit(void)
{
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(LPC_IOCON, IOCON_UART_RX, PIN_MODE_PULLUP);
    IoconPinSetMode(LPC_IOCON, IOCON_UART_TX, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_U0_TXD_O, PIN_UART_TX);
    SwmMovablePinAssign(SWM_U0_RXD_I, PIN_UART_RX);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);

    // setup UART peripheral
    UartInit(UART_DEBUG);
    UartConfigData(UART_DEBUG, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
    ClockSetUSARTNBaseClockRate((UART_BAUD_RATE * 16), true);
    UartSetBaud(UART_DEBUG, UART_BAUD_RATE);
    UartEnable(UART_DEBUG);
    UartTXEnable(UART_DEBUG);
}
