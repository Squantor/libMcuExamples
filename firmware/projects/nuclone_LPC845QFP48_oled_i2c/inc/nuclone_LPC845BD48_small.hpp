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
#include <mid/display/graphics_terminal.hpp>
#include <fonts/font_6x8_rowflip.hpp>
#include <drivers/SSD1306_i2c.hpp>
#include <drivers/SSD1306/SSD1306_conf_gen_128x32.hpp>
#include <mid/display/display_dir_SSD1306.hpp>

#define TICKS_PER_S 100

// pin types
// Crystal osillator pins
using pinXtalInType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using pinXtalOutType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// bootloader and uart pins
using pinBootloaderType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;
using pinDebugUartTxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using pinDebugUartRxType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
using pinI2cSclType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin10>;
using pinI2cSdaType = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin11>;

// function types
using functionXtalInType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALIN>;
using functionXtalOutType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::XTALOUT>;
using functionUartDebugTxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_TXD_O>;
using functionUartDebugRxType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::U0_RXD_I>;
using functionI2cSclType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::I2C0_SCL_IO>;
using functionI2cSdaType = libmcuhw::swm::pinFunction<libmcuhw::swm::PinFunctions::I2C0_SDA_IO>;

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

constexpr inline libmcu::i2cDeviceAddress SSD1306_I2C_ADDRESS{0x3C};

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
extern libMcuHal::usart::uartSync<libmcuhw::Usart0Address, libmcuhw::NvicAddress, char, 128> usartPeripheral;
extern libMcuHal::i2c::i2cSyncPol<libmcuhw::i2c0Address, 128> i2cPeripheral;
extern libMcuDriver::SSD1306::generic128x32 testDisplay;
extern libMcuDriver::SSD1306::SSD1306<i2cPeripheral, SSD1306_I2C_ADDRESS, testDisplay> SSD1306;
extern libMcuMid::display::displayDirSSD1306<testDisplay, SSD1306> display;
extern sqEmbedded::fonts::mono6x8RowFlip font;
extern libMcuMid::display::graphicsTerminal<display, font> displayTerminal;

constexpr inline libmcuhw::clock::mcuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nucloneClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0ClockConfig;
constexpr inline libmcuhw::clock::periClockConfig<nucloneClockConfig, libmcuhw::clock::PeriSelect::I2C0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  i2c0ClockConfig;

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

void boardInit(void);

#endif