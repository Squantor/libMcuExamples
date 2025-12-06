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
using pinWs2812SpiSckType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin00>;
using pinWs2812SpiMosiType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin01>;
using pinWs2812DataPinType = libmcuhw::Pin<libmcuhw::IoPorts::Port1, libmcuhw::IoPins::Pin02>;

// function types
using functionXtalInType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALIN>;
using functionXtalOutType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALOUT>;
using functionUartDebugTxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_RXD_I>;
using functionSpiSckType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::SPI0_SCK_IO>;
using functionSpiMosiType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::SPI0_MOSI_IO>;
using functionSctIn0Type = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::SCT_PIN0_I>;
using functionSctIn1Type = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::SCT_PIN1_I>;
using functionSctOut0Type = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::SCT_OUT0_O>;

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
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
extern libMcuHal::spi::SpiSyncPol<libmcuhw::spi0Address> spiPeripheral;

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