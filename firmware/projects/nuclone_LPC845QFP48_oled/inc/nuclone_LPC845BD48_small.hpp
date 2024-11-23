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
// #include <SSD1306_direct.hpp>
// #include <graphicalconsole.hpp>
#include <fonts/font_8x8.hpp>
#include <drivers/SSD1306_i2c.hpp>
#include <drivers/SSD1306/SSD1306_conf_gen_128x32.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN08>;
using pinXtalOutType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN09>;
// bootloader and uart pins
using pinBootloaderType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN12>;
using pinDebugUartTxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN25>;
using pinDebugUartRxType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN24>;
using pinI2cSclType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN10>;
using pinI2cSdaType = libMcuHw::pin<libMcuHw::IOports::PORT0, libMcuHw::IOpins::PIN11>;

// function types
using functionXtalInType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALIN>;
using functionXtalOutType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::XTALOUT>;
using functionUartDebugTxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::U0_RXD_I>;
using functionI2cSclType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::I2C0_SCL_IO>;
using functionI2cSdaType = libMcuHw::swm::pinFunction<libMcuHw::swm::pinFunctions::I2C0_SDA_IO>;

// pin instances
constexpr pinXtalInType xtalInPin;
constexpr pinXtalOutType xtalOutPin;
constexpr pinBootloaderType bootloadPin;
constexpr pinDebugUartTxType debugUartTxPin;
constexpr pinDebugUartRxType debugUartRxPin;
constexpr pinI2cSclType i2cSclPin;
constexpr pinI2cSdaType i2cSdaPin;

// function instances
constexpr functionXtalInType xtalInFunction;
constexpr functionXtalOutType xtalOutFunction;
constexpr functionUartDebugTxType uartDebugTxFunction;
constexpr functionUartDebugRxType uartDebugRxFunction;
constexpr functionI2cSclType i2cSclFunction;
constexpr functionI2cSdaType i2cSdaFunction;

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
constexpr inline libMcuHw::clock::periClockConfig<nucloneClockConfig, libMcuHw::clock::periSelect::I2C0,
                                                  libMcuHw::clock::periSource::MAIN>
  i2c0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif