/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef NUCLONE_LPC845M301BD48_HPP
#define NUCLONE_LPC845M301BD48_HPP

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (12000000u)
#define CLOCK_AHB           (12000000u)
#define CLOCK_MAIN          (12000000u)

#include <mcu_ll.h>

#define TICKS_PER_S         10

#define IOCON_XTAL_IN       IOCON_PIO0_8
#define IOCON_XTAL_OUT      IOCON_PIO0_9

#define IOCON_UART_TX       IOCON_PIO13
#define PIN_UART_TX         (13u)
#define IOCON_UART_RX       IOCON_PIO17
#define PIN_UART_RX         (17u)

#define UART_DEBUG          LPC_USART0
#define UART_BAUD_RATE      (115200u)

// test pin pair 0, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_0_0   (IOCON_PIO0_1)
#define PORT_TESTPIN_0_0    (GPIO_PORT0)
#define PIN_TESTPIN_0_0     (1u)
#define SWM_TESTPINT_0_0    (SWM_PORTPIN_P0_1)
#define IOCON_TESTPIN_0_1   IOCON_PIO1_4
#define PORT_TESTPIN_0_1    (GPIO_PORT1)
#define PIN_TESTPIN_0_1     (4u)
#define SWM_TESTPINT_0_1    (SWM_PORTPIN_P1_4)
// test pin pair 1, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_1_0   (IOCON_PIO0_15)
#define PORT_TESTPIN_1_0    (GPIO_PORT0)
#define PIN_TESTPIN_1_0     (15u)
#define SWM_TESTPIN_1_0     (SWM_PORTPIN_P0_15)
#define IOCON_TESTPIN_1_1   (IOCON_PIO1_3)
#define PORT_TESTPIN_1_1    (GPIO_PORT1)
#define PIN_TESTPIN_1_1     (3u)
#define SWM_TESTPIN_1_1     (SWM_PORTPIN_P1_3)

void boardInit(void);

#endif