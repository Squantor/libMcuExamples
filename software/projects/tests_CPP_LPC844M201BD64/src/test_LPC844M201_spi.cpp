/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC844M201 SPI peripheral polling mode
 */
#include <nuclone_LPC844M201BD64_tests.hpp>
#include <MinUnit.h>
#include <LPC844M201_teardown.hpp>
#include <common.hpp>

LPC844M201BD64::instances::spi<LPC844M201BD64::peripherals::SPI0_cpp, LPC844M201BD64::spiChipEnables> testSpiPeripheral;

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC844M201CppSetupSpi) {
  minUnitCheck(LPC844M201TeardownCorrect() == true);
}

MINUNIT_ADD(LPC844M201CppSpiRxTx, LPC844M201CppSetupSpi, LPC844M201Teardown) {
  sysconEnableClocks(SYSCON, CLKCTRL0_SPI0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
  sysconEnableResets(SYSCON, RESETCTRL0_SPI0 | RESETCTRL0_SWM | RESETCTRL0_IOCON, RESETCTRL1_NONE);
  sysconPeripheralClockSelect(SYSCON, SPI0CLKSEL, CLKSRC_MAIN);
  SwmMovablePinAssign(SWM, SWM_SPI0_SCK, SWM_TESTPIN_0_0);
  SwmMovablePinAssign(SWM, SWM_SPI0_MOSI, SWM_TESTPIN_1_0);
  SwmMovablePinAssign(SWM, SWM_SPI0_MISO, SWM_TESTPIN_1_1);
  SwmMovablePinAssign(SWM, SWM_SPI0_SSEL0, SWM_TESTPIN_2);
  __NOP();
  uint32_t actualDivider = testSpiPeripheral.init(999999);
  minUnitCheck(actualDivider == 1000000);
  minUnitCheck(SPI0->DIV == 11);
  minUnitCheck((spiSetGetStatus(SPI0, 0x0) & 0x10F) == 0x102);  // masking off relevant bits
  // test 16 bit transfer with receive
  spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(0xA55A) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_LEN(16));
  int i = 0;
  while (i < 10000 && !(spiSetGetStatus(SPI0, 0x0) & SPI_STAT_RXRDY)) i++;
  minUnitCheck(i != 10000);
  uint32_t rxData = spiGetRxData(SPI0);
  minUnitCheck(SPI_RXDAT_DATA(rxData) == 0xA55A);
  minUnitCheck((rxData & 0xF0000) == SPI_TXDATCTL_TXSSEL0);
  // small transfer without received data
  spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(0x5) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                           SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(4));
  minUnitCheck((spiSetGetStatus(SPI0, 0x0) & SPI_STAT_RXRDY) == 0);
  SwmMovablePinAssign(SWM, SWM_SPI0_SSEL0, SWM_PORTPIN_Reset);
  SwmMovablePinAssign(SWM, SWM_SPI0_MOSI, SWM_PORTPIN_Reset);
  SwmMovablePinAssign(SWM, SWM_SPI0_MISO, SWM_PORTPIN_Reset);
  SwmMovablePinAssign(SWM, SWM_SPI0_SCK, SWM_PORTPIN_Reset);
  sysconDisableClocks(SYSCON, CLKCTRL0_I2C0 | CLKCTRL0_SWM | CLKCTRL0_IOCON, CLKCTRL1_NONE);
}