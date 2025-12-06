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

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using pinXtalOutType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// bootloader and uart pins
using pinBootloaderType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;
using pinDebugUartTxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using pinDebugUartRxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;

// function types
using functionXtalInType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALIN>;
using functionXtalOutType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALOUT>;
using functionUartDebugTxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_RXD_I>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
constexpr inline libmcuhw::clock::mcuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);
/**
 * @brief checks if mains power is present
 * @return true mains power present
 * @return false mains power not present
 */
bool isMainsPresent(void);

/**
 * @brief Set the iron pin multiplexers
 * @param mux1 mux value, see HSI for what pins these are
 * @param mux2 mux value, see HSI for what pins these are
 */
void setMultiplexers(std::uint32_t mux1, std::uint32_t mux2);

/**
 * @brief Setup hardware to be safe when USB powered
 * This entails setting muxes to 0, power stage to 0 and resetting power control states
 */
void setSafeUsbPowered(void);

#endif