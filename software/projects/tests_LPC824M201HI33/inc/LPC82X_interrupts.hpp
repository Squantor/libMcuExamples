/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef LPC82X_INTERRUPTS_HPP
#define LPC82X_INTERRUPTS_HPP

extern void (*interrupt_SPI0)(void);
extern void (*interrupt_SPI1)(void);
extern void (*interrupt_UART0)(void);
extern void (*interrupt_UART1)(void);
extern void (*interrupt_UART2)(void);
extern void (*interrupt_I2C1)(void);
extern void (*interrupt_I2C0)(void);
extern void (*interrupt_SCT)(void);
extern void (*interrupt_MRT)(void);
extern void (*interrupt_CMP)(void);
extern void (*interrupt_WDT)(void);
extern void (*interrupt_BOD)(void);
extern void (*interrupt_FLASH)(void);
extern void (*interrupt_WKT)(void);
extern void (*interrupt_ADC_SEQA)(void);
extern void (*interrupt_ADC_SEQB)(void);
extern void (*interrupt_ADC_THCMP)(void);
extern void (*interrupt_ADC_OVR)(void);
extern void (*interrupt_DMA)(void);
extern void (*interrupt_I2C2)(void);
extern void (*interrupt_I2C3)(void);
extern void (*interrupt_PIN_INT0)(void);
extern void (*interrupt_PIN_INT1)(void);
extern void (*interrupt_PIN_INT2)(void);
extern void (*interrupt_PIN_INT3)(void);
extern void (*interrupt_PIN_INT4)(void);
extern void (*interrupt_PIN_INT5)(void);
extern void (*interrupt_PIN_INT6)(void);
extern void (*interrupt_PIN_INT7)(void);

#endif