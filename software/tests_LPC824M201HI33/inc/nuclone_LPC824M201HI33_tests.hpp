/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef NUCLONE_LPC824M201HI33_HPP
#define NUCLONE_LPC824M201HI33_HPP

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (12000000u)
#define CLOCK_AHB           (12000000u)
#define CLOCK_MAIN          (12000000u)

#include <mcu_ll.h>

#define TICKS_PER_S         10

#define IOCON_XTAL_IN       IOCON_PIO0_8
#define IOCON_XTAL_OUT      IOCON_PIO0_9

// test pin pair 0, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_0_0   (IOCON_PIO0_12)
#define PORT_TESTPIN_0_0    (GPIO_PORT0)
#define PIN_TESTPIN_0_0     (12u)
#define SWM_TESTPIN_0_0     (SWM_PORTPIN_P0_12)
#define IOCON_TESTPIN_0_1   (IOCON_PIO0_13)
#define PORT_TESTPIN_0_1    (GPIO_PORT0)
#define PIN_TESTPIN_0_1     (13u)
#define SWM_TESTPIN_0_1     (SWM_PORTPIN_P0_13)
// test pin pair 1, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_1_0   (IOCON_PIO0_28)
#define PORT_TESTPIN_1_0    (GPIO_PORT0)
#define PIN_TESTPIN_1_0     (28u)
#define SWM_TESTPIN_1_0     (SWM_PORTPIN_P0_28)
#define IOCON_TESTPIN_1_1   (IOCON_PIO0_16)
#define PORT_TESTPIN_1_1    (GPIO_PORT0)
#define PIN_TESTPIN_1_1     (16u)
#define SWM_TESTPIN_1_1     (SWM_PORTPIN_P0_16)
// loose test pins
//#define IOCON_TESTPIN_2     (IOCON_PIO1_14)
//#define PORT_TESTPIN_2      (GPIO_PORT1)
//#define PIN_TESTPIN_2       (14u)
//#define SWM_TESTPIN_2       (SWM_PORTPIN_P1_14)

void boardInit(void);

#endif