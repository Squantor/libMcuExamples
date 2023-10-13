/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 SPI peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>
#include <array>

using namespace libMcuLL::sw::spi;
using namespace libMcuLL::hw::spi;

static constexpr libMcuLL::hwAddressType spi0Address = libMcuLL::hw::SPI0_cpp;
libMcuLL::hw::spi::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::spi::peripheral *>(spi0Address)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSpiAsync) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_SPI0 | libMcuLL::sw::syscon::CLOCK_SWM |
                                          libMcuLL::sw::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_SPI0);
  swmPeriperhal.setup(test2Pin, spiMainSckFunction);
  swmPeriperhal.setup(test1Pin, spiMainMosiFunction);
  swmPeriperhal.setup(test0Pin, spiMainMisoFunction);
}

MINUNIT_ADD(LPC812M101CppSpiAsyncInits, LPC812M101CppSetupSpiAsync, LPC812M101Teardown) {
  uint32_t actualClock;
  actualClock = spiAsyncPeripheral.initMaster(100000);
  minUnitCheck(actualClock == 100000);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == 0x00000005);
  minUnitCheck(dutRegisters->DIV == 299);
  dutRegisters->CFG = 0x00000000;
  actualClock = spiAsyncPeripheral.initMaster(65399, CPHA1_CPOL1_LSB, SPOL_HIGH);
  minUnitCheck(actualClock == 65502);
  minUnitCheck((dutRegisters->CFG & CFG::MASK) == 0x0000013D);
  minUnitCheck(dutRegisters->DIV == 457);
}

MINUNIT_ADD(LPC812M101CppSpiAsyncClaimUnclaim, LPC812M101CppSetupSpiAsync, LPC812M101Teardown) {
  minUnitCheck(spiAsyncPeripheral.claim() == libMcuLL::results::CLAIMED);
  minUnitCheck(spiAsyncPeripheral.claim() == libMcuLL::results::IN_USE);
  minUnitCheck(spiAsyncPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
  minUnitCheck(spiAsyncPeripheral.unclaim() == libMcuLL::results::ERROR);
}