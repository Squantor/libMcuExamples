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
using pinXtalInType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN08>;
using pinXtalOutType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN12>;
using pinDebugUartTxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN25>;
using pinDebugUartRxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN24>;

// function types
using functionXtalInType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_RXD_I>;

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
extern libMcuLL::iocon::iocon<libMcuHw::ioconAddress> ioconPeripheral;
extern libMcuLL::swm::swm<libMcuHw::swmAddress> swmPeriperhal;
extern libMcuLL::gpio::gpio<libMcuHw::gpioAddress> gpioPeripheral;
extern libMcuLL::syscon::syscon<libMcuHw::sysconAddress> sysconPeripheral;
extern libMcuLL::systick::systick<libMcuHw::systickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libMcuHw::usart0Address, libMcuHw::nvicAddress, char, 128> usartPeripheral;
constexpr inline libMcuHw::clock::mcuClockConfig<libMcuHw::clock::clockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::UART0,
                                                  libMcuHw::clock::periSource::MAIN>
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