/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief LPC82X interrupt multiplexer
 */
#include <board.hpp>
#include <stdlib.h>

void (*interrupt_SPI0)(void);
void (*interrupt_SPI1)(void);
void (*interrupt_UART0)(void);
void (*interrupt_UART1)(void);
void (*interrupt_UART2)(void);
void (*interrupt_I2C1)(void);
void (*interrupt_I2C0)(void);
void (*interrupt_SCT)(void);
void (*interrupt_MRT)(void);
void (*interrupt_CMP)(void);
void (*interrupt_WDT)(void);
void (*interrupt_BOD)(void);
void (*interrupt_FLASH)(void);
void (*interrupt_WKT)(void);
void (*interrupt_ADC_SEQA)(void);
void (*interrupt_ADC_SEQB)(void);
void (*interrupt_ADC_THCMP)(void);
void (*interrupt_ADC_OVR)(void);
void (*interrupt_DMA)(void);
void (*interrupt_I2C2)(void);
void (*interrupt_I2C3)(void);
void (*interrupt_PIN_INT0)(void);
void (*interrupt_PIN_INT1)(void);
void (*interrupt_PIN_INT2)(void);
void (*interrupt_PIN_INT3)(void);
void (*interrupt_PIN_INT4)(void);
void (*interrupt_PIN_INT5)(void);
void (*interrupt_PIN_INT6)(void);
void (*interrupt_PIN_INT7)(void);

extern "C" {

void SPI0_IRQHandler(void) {
  if (interrupt_SPI0 != NULL)
    interrupt_SPI0();
  else
    __BKPT(1);
}
void SPI1_IRQHandler(void) {
  if (interrupt_SPI1 != NULL)
    interrupt_SPI1();
  else
    __BKPT(1);
}
void UART0_IRQHandler(void) {
  if (interrupt_UART0 != NULL)
    interrupt_UART0();
  else
    __BKPT(1);
}
void UART1_IRQHandler(void) {
  if (interrupt_UART1 != NULL)
    interrupt_UART1();
  else
    __BKPT(1);
}
void UART2_IRQHandler(void) {
  if (interrupt_UART2 != NULL)
    interrupt_UART2();
  else
    __BKPT(1);
}
void I2C1_IRQHandler(void) {
  if (interrupt_I2C1 != NULL)
    interrupt_I2C1();
  else
    __BKPT(1);
}
void I2C0_IRQHandler(void) {
  if (interrupt_I2C0 != NULL)
    interrupt_I2C0();
  else
    __BKPT(1);
}
void SCT_IRQHandler(void) {
  if (interrupt_SCT != NULL)
    interrupt_SCT();
  else
    __BKPT(1);
}
void MRT_IRQHandler(void) {
  if (interrupt_MRT != NULL)
    interrupt_MRT();
  else
    __BKPT(1);
}
void CMP_IRQHandler(void) {
  if (interrupt_CMP != NULL)
    interrupt_CMP();
  else
    __BKPT(1);
}
void WDT_IRQHandler(void) {
  if (interrupt_WDT != NULL)
    interrupt_WDT();
  else
    __BKPT(1);
}
void BOD_IRQHandler(void) {
  if (interrupt_BOD != NULL)
    interrupt_BOD();
  else
    __BKPT(1);
}
void FLASH_IRQHandler(void) {
  if (interrupt_FLASH != NULL)
    interrupt_FLASH();
  else
    __BKPT(1);
}
void WKT_IRQHandler(void) {
  if (interrupt_WKT != NULL)
    interrupt_WKT();
  else
    __BKPT(1);
}
void ADC_SEQA_IRQHandler(void) {
  if (interrupt_ADC_SEQA != NULL)
    interrupt_ADC_SEQA();
  else
    __BKPT(1);
}
void ADC_SEQB_IRQHandler(void) {
  if (interrupt_ADC_SEQB != NULL)
    interrupt_ADC_SEQB();
  else
    __BKPT(1);
}
void ADC_THCMP_IRQHandler(void) {
  if (interrupt_ADC_THCMP != NULL)
    interrupt_ADC_THCMP();
  else
    __BKPT(1);
}
void ADC_OVR_IRQHandler(void) {
  if (interrupt_ADC_OVR != NULL)
    interrupt_ADC_OVR();
  else
    __BKPT(1);
}
void DMA_IRQHandler(void) {
  if (interrupt_DMA != NULL)
    interrupt_DMA();
  else
    __BKPT(1);
}
void I2C2_IRQHandler(void) {
  if (interrupt_I2C2 != NULL)
    interrupt_I2C2();
  else
    __BKPT(1);
}
void I2C3_IRQHandler(void) {
  if (interrupt_I2C3 != NULL)
    interrupt_I2C3();
  else
    __BKPT(1);
}
void PIN_INT0_IRQHandler(void) {
  if (interrupt_PIN_INT0 != NULL)
    interrupt_PIN_INT0();
  else
    __BKPT(1);
}
void PIN_INT1_IRQHandler(void) {
  if (interrupt_PIN_INT1 != NULL)
    interrupt_PIN_INT1();
  else
    __BKPT(1);
}
void PIN_INT2_IRQHandler(void) {
  if (interrupt_PIN_INT2 != NULL)
    interrupt_PIN_INT2();
  else
    __BKPT(1);
}
void PIN_INT3_IRQHandler(void) {
  if (interrupt_PIN_INT3 != NULL)
    interrupt_PIN_INT3();
  else
    __BKPT(1);
}
void PIN_INT4_IRQHandler(void) {
  if (interrupt_PIN_INT4 != NULL)
    interrupt_PIN_INT4();
  else
    __BKPT(1);
}
void PIN_INT5_IRQHandler(void) {
  if (interrupt_PIN_INT5 != NULL)
    interrupt_PIN_INT5();
  else
    __BKPT(1);
}
void PIN_INT6_IRQHandler(void) {
  if (interrupt_PIN_INT6 != NULL)
    interrupt_PIN_INT6();
  else
    __BKPT(1);
}
void PIN_INT7_IRQHandler(void) {
  if (interrupt_PIN_INT7 != NULL)
    interrupt_PIN_INT7();
  else
    __BKPT(1);
}
}