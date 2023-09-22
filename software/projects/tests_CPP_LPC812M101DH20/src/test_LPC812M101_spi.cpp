/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC812M101 SPI peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>

registers::spi::registers *const dutRegisters{reinterpret_cast<registers::spi::registers *>(peripherals::SPI0_cpp)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSpi) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_SPI0 | instances::syscon::CLOCK_SWM |
                                          instances::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_SPI0);
}

MINUNIT_ADD(LPC812M101CppSpiInits, LPC812M101CppSetupSpi, LPC812M101Teardown) {
  uint32_t actualClock;
  actualClock = spiPeripheral.initMaster(100000);
  minUnitCheck(actualClock == 100000);
  minUnitCheck((dutRegisters->CFG & instances::spi::CFG::MASK) == 0x00000005);
  minUnitCheck((dutRegisters->DIV == 299));
  dutRegisters->CFG = 0x00000000;
  actualClock = spiPeripheral.initMaster(65399, instances::spi::CPHA1_CPOL1_LSB, instances::spi::SPOL_HIGH);
  minUnitCheck(actualClock == 65502);
  minUnitCheck((dutRegisters->CFG & instances::spi::CFG::MASK) == 0x0000013D);
  minUnitCheck((dutRegisters->DIV == 457));
}

MINUNIT_ADD(LPC812M101CppSpiRxTx, LPC812M101CppSetupSpi, LPC812M101Teardown) {
  swmPeriperhal.setup(test2Pin, spiMainSckFunction);
  swmPeriperhal.setup(test3Pin, spiMainSselFunction);
  swmPeriperhal.setup(test1Pin, spiMainMosiFunction);
  swmPeriperhal.setup(test0Pin, spiMainMisoFunction);
  minUnitPass();
}