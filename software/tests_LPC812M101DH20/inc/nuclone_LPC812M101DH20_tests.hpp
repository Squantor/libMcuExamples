/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef NUCLONE_LPC812M101DH20_HPP
#define NUCLONE_LPC812M101DH20_HPP

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (12000000u)
#define CLOCK_AHB           (12000000u)
#define CLOCK_MAIN          (12000000u)

#include <mcu_ll.h>

#define TICKS_PER_S         10

#define IOCON_XTAL_IN       IOCON_PIO0_8
#define IOCON_XTAL_OUT      IOCON_PIO0_9

/*

Parking these defines until we have UART output 

#define IOCON_UART_TX       IOCON_PIO13
#define PIN_UART_TX         (13u)
#define IOCON_UART_RX       IOCON_PIO17
#define PIN_UART_RX         (17u)

#define UART_DEBUG          LPC_USART0
#define UART_BAUD_RATE      (115200u)
*/

// test pin pair 0, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_0_0   (IOCON_PIO0_17)
#define PORT_TESTPIN_0_0    (GPIO_PORT0)
#define PIN_TESTPIN_0_0     (17u)
#define SWM_TESTPIN_0_0     (SWM_PORTPIN_P0_17)
#define IOCON_TESTPIN_0_1   (IOCON_PIO0_13)
#define PORT_TESTPIN_0_1    (GPIO_PORT0)
#define PIN_TESTPIN_0_1     (13u)
#define SWM_TESTPIN_0_1     (SWM_PORTPIN_P0_13)
// test pin pair 1, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_1_0   (IOCON_PIO0_4)
#define PORT_TESTPIN_1_0    (GPIO_PORT0)
#define PIN_TESTPIN_1_0     (4u)
#define SWM_TESTPIN_1_0     (SWM_PORTPIN_P0_4)
#define IOCON_TESTPIN_1_1   (IOCON_PIO0_16)
#define PORT_TESTPIN_1_1    (GPIO_PORT0)
#define PIN_TESTPIN_1_1     (16u)
#define SWM_TESTPIN_1_1     (SWM_PORTPIN_P0_16)
// loose test pins
#define IOCON_TESTPIN_2     (IOCON_PIO0_15)
#define PORT_TESTPIN_2      (GPIO_PORT0)
#define PIN_TESTPIN_2       (15u)
#define SWM_TESTPIN_2       (SWM_PORTPIN_P0_15)

void boardInit(void);

#endif