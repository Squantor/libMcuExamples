/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for temperature sensing proof of concept board
 */
#ifndef POC_TEMP_SENSE_NUCLONE_HPP
#define POC_TEMP_SENSE_NUCLONE_HPP

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>
#include <mid/display/graphics_terminal.hpp>
#include <fonts/font_6x8_rowflip.hpp>
#include <drivers/memlcd.hpp>
#include <mid/display/memlcd.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN08>;
using pinXtalOutType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN12>;
using pinDebugUartTxType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN25>;
using pinDebugUartRxType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN24>;
using pinDispSpiSckType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN00>;
using pinDispSpiMosiType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN01>;
using pinDispSpiCsType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN02>;
using pinDispEmdType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN03>;
using pinDispDonType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN04>;
using pinDispEinType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN05>;

// function types
using functionXtalInType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kXtalIn>;
using functionXtalOutType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kXtalOut>;
using functionUartDebugTxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kUart0TxOut>;
using functionUartDebugRxType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kUart0RxIn>;
using functionSpiSckType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kSpi0SckInOut>;
using functionSpiMosiType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kSpi0MosiInOut>;
using functionSpiCsType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::kSpi0Ssel0InOut>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;
constexpr pinDispSpiSckType ws2812SpiSckPin;
constexpr pinDispSpiMosiType ws2812SpiMosiPin;
constexpr pinDispSpiCsType dispSpiCsPin;
constexpr pinDispEmdType dispEmdPin;
constexpr pinDispDonType dispDonPin;
constexpr pinDispEinType dispEinPin;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;
constexpr functionSpiSckType spiSckFunction;
constexpr functionSpiMosiType spiMosiFunction;
constexpr functionSpiCsType spiCsFunction;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::ioconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::swmAddress> swmPeriperhal;
extern libmcull::gpio::gpio<libmcuhw::gpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::sysconAddress> sysconPeripheral;
extern libmcull::systick::systick<libmcuhw::systickAddress> systickPeripheral;
extern libmcuhal::usart::SyncUart<libmcuhw::usart0Address, libmcuhw::nvicAddress, char, 128> usartPeripheral;
extern libmcuhal::spi::SpiSyncPol<libmcuhw::spi0Address> spiPeripheral;
extern libMcuDrv::memlcd::memlcd<libMcuDrv::memlcd::LS013B4DN04, libmcuhal::spi::spiSlaveSelects::Select0, spiPeripheral>
  memlcdDriver;
extern libMcuMid::display::displayMemlcd<libMcuDrv::memlcd::LS013B4DN04, memlcdDriver> display;

constexpr inline libmcuhw::clock::mcuClockConfig<libmcuhw::clock::clockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::periSelect::UART0,
                                                  libmcuhw::clock::periSource::MAIN>
  uart0ClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::periSelect::I2C0,
                                                  libmcuhw::clock::periSource::MAIN>
  i2c0ClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::periSelect::SPI0,
                                                  libmcuhw::clock::periSource::MAIN>
  spi0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif