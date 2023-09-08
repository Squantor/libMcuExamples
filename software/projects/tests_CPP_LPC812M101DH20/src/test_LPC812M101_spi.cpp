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

instances::spi::spi<peripherals::SPI0_cpp, instances::spi::chipEnables> testSpiPeripheral;

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSpi) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_SPI0 | instances::syscon::CLOCK_SWM |
                                          instances::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(instances::syscon::RESET_SPI0);
}

MINUNIT_ADD(LPC812M101CppSpiRxTx, LPC812M101CppSetupSpi, LPC812M101Teardown) {
  // use C++ variants
  swmPeriperhal.setup(test2Pin, spiMainSckFunction);
  swmPeriperhal.setup(test3Pin, spiMainSselFunction);
  swmPeriperhal.setup(test1Pin, spiMainMosiFunction);
  swmPeriperhal.setup(test0Pin, spiMainMisoFunction);
  // undo setup
  swmPeriperhal.clear(test2Pin, spiMainSckFunction);
  swmPeriperhal.clear(test3Pin, spiMainSselFunction);
  swmPeriperhal.clear(test1Pin, spiMainMosiFunction);
  swmPeriperhal.clear(test0Pin, spiMainMisoFunction);
  // TODO, move this to teardown
  sysconPeripheral.disablePeripheralClocks(instances::syscon::CLOCK_SPI0 | instances::syscon::CLOCK_SWM |
                                           instances::syscon::CLOCK_IOCON);
  minUnitPass();
}