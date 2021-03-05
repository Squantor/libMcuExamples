/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef BOARD_HPP
#define BOARD_HPP

#define IOCON_UART_TX       IOCON_PIO13
#define PIN_UART_TX         (13u)
#define IOCON_UART_RX       IOCON_PIO17
#define PIN_UART_RX         (17u)

#define UART_DEBUG          LPC_USART0
#define UART_BAUD_RATE      (115200u)

// we just run from crystal, we will switch PLL in some of the tests
#define CLOCK_MAIN_SOURCE   SYSCTL_MAINCLKSRC_IRC
#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (12000000u)
#define CLOCK_AHB           (12000000u)
#define CLOCK_MAIN          (12000000u)

#include <mcu_ll.h>

void boardInit(void);


#endif