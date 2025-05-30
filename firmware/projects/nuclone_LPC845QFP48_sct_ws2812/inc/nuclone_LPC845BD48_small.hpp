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
using pinXtalInType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN08>;
using pinXtalOutType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN12>;
using pinDebugUartTxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN25>;
using pinDebugUartRxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN24>;
using pinWs2812SpiSckType = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN00>;
using pinWs2812SpiMosiType = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN01>;
using pinWs2812DataPinType = libMcuHw::pin<libMcuHw::IOports::PORT1, libMcuHw::IOpins::PIN02>;

// function types
using functionXtalInType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_RXD_I>;
using functionSpiSckType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::SPI0_SCK_IO>;
using functionSpiMosiType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::SPI0_MOSI_IO>;
using functionSctIn0Type = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::SCT_PIN0_I>;
using functionSctIn1Type = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::SCT_PIN1_I>;
using functionSctOut0Type = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::SCT_OUT0_O>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;
constexpr pinWs2812SpiSckType ws2812SpiSckPin;
constexpr pinWs2812SpiMosiType ws2812SpiMosiPin;
constexpr pinWs2812DataPinType ws2812DataPin;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;
constexpr functionSpiSckType spiSckFunction;
constexpr functionSpiMosiType spiMosiFunction;
constexpr functionSctIn0Type sctIn0Function;
constexpr functionSctIn1Type sctIn1Function;
constexpr functionSctOut0Type sctOut0Function;

// peripheral externs
extern libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
extern libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
extern libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
extern libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
extern libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libMcuHw::usart0Address, libMcuHw::nvicAddress, char, 128> usartPeripheral;
extern libMcuHal::spi::SpiSyncPol<libMcuHw::spi0Address> spiPeripheral;

constexpr inline libMcuHw::clock::mcuClockConfig<libMcuHw::clock::clockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::UART0,
                                                  libMcuHw::clock::periSource::MAIN>
  uart0ClockConfig;
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::I2C0,
                                                  libMcuHw::clock::periSource::MAIN>
  i2c0ClockConfig;
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::SPI0,
                                                  libMcuHw::clock::periSource::MAIN>
  spi0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif