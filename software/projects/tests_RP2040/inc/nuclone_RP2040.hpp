/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef NUCLONE_RP2040_HPP
#define NUCLONE_RP2040_HPP

#define FREQ_XTAL (12000000u)       /**< Crystal oscillator frequncy */
#define FREQ_CPU (125000000u)       /**< CPU frequency */
#define FREQ_USB (48000000u)        /**< USB frequency */
#define FREQ_ADC (48000000u)        /**< ADC frequency */
#define FREQ_RTC (CLOCK_XTAL / 256) /**< RTC frequency */
#define FREQ_PERI (CLOCK_CPU)       /**< Peripherals frequency */

#include <mcu_ll.h>

#define TICKS_PER_S (8u)

void boardInit(void);

#endif