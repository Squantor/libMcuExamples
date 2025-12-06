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
using pinXtalInType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using pinXtalOutType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// bootloader and uart pins
using pinBootloaderType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;
using pinDebugUartTxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using pinDebugUartRxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
using pinDispSpiSckType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin00>;
using pinDispSpiMosiType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin01>;
using pinDispSpiCsType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin02>;
using pinDispEmdType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin03>;
using pinDispDonType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin04>;
using pinDispEinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin05>;

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

using TestDisplay = libMcuDrv::memlcd::LS013B7DH05;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
extern libmcuhal::usart::SyncUart<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
extern libmcuhal::spi::SpiSyncPol<libmcuhw::spi0Address> spiPeripheral;
extern libMcuDrv::memlcd::memlcd<TestDisplay, libmcuhal::spi::spiSlaveSelects::Select0, spiPeripheral> memlcdDriver;
extern libMcuMid::display::displayMemlcd<TestDisplay, memlcdDriver> display;

constexpr inline libmcuhw::clock::mcuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0ClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::I2C0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  i2c0ClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::SPI0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  spi0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif