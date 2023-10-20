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

static constexpr int maxIterations = 1000;
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
  swmPeriperhal.setup(test3Pin, spiMainSselFunction);
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
  spiAsyncPeripheral.initMaster(100000);
  minUnitCheck(spiAsyncPeripheral.claim() == libMcuLL::results::CLAIMED);
  minUnitCheck(spiAsyncPeripheral.claim() == libMcuLL::results::IN_USE);
  minUnitCheck(spiAsyncPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
  minUnitCheck(spiAsyncPeripheral.unclaim() == libMcuLL::results::ERROR);
}

MINUNIT_ADD(LPC812M101CppSpiAsyncReadWrite, LPC812M101CppSetupSpiAsync, LPC812M101Teardown) {
  int iterationCount = 0;
  libMcuLL::results status;
  std::array<uint16_t, 5> testDataSend{0x1234, 0x4567, 0x89AB, 0xCDEF, 0x5A5A};
  std::array<uint16_t, 5> testDataReceive;
  testDataReceive.fill(0x0000u);
  spiAsyncPeripheral.initMaster(1000000);
  minUnitCheck(spiAsyncPeripheral.claim() == libMcuLL::results::CLAIMED);
  minUnitCheck(spiAsyncPeripheral.startReadWrite(chipEnables::SSEL, testDataSend, testDataReceive, 8, true) ==
               libMcuLL::results::STARTED);
  minUnitCheck(spiAsyncPeripheral.startReadWrite(chipEnables::SSEL, testDataSend, testDataReceive, 8, true) ==
               libMcuLL::results::ERROR);
  minUnitCheck(spiAsyncPeripheral.progress() == libMcuLL::results::BUSY);

  iterationCount = 0;
  do {
    status = spiAsyncPeripheral.progress();
    iterationCount++;
  } while (status == libMcuLL::results::BUSY && iterationCount < maxIterations);

  minUnitCheck(status == libMcuLL::results::DONE);
  minUnitCheck(iterationCount < maxIterations);
  minUnitCheck((testDataSend[0] & 0xFF) == testDataReceive[0]);
  // TODO check register statuses?
  testDataReceive.fill(0x0000u);
  minUnitCheck(spiAsyncPeripheral.startReadWrite(chipEnables::SSEL_NONE, testDataSend, testDataReceive, 24, true) ==
               libMcuLL::results::STARTED);
  iterationCount = 0;
  do {
    status = spiAsyncPeripheral.progress();
    iterationCount++;
  } while (status == libMcuLL::results::BUSY && iterationCount < maxIterations);

  minUnitCheck(status == libMcuLL::results::DONE);
  minUnitCheck(iterationCount < maxIterations);
  minUnitCheck(testDataSend[0] == testDataReceive[0]);
  minUnitCheck((testDataSend[1] & 0xFF) == testDataReceive[1]);

  minUnitCheck(spiAsyncPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
}