/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef NUCLONE_LPC812M101DH20_HPP
#define NUCLONE_LPC812M101DH20_HPP

#define CLOCK_MAIN_SOURCE SYSCTL_MAINCLKSRC_PLLOUT

#define CLOCK_XTAL (12000000u)
#define CLOCK_EXT_IN (0u)
#define CLOCK_CPU (30000000u)
#define CLOCK_AHB (30000000u)
#define CLOCK_MAIN (60000000u)

#include <mcu_ll.hpp>

#define TICKS_PER_S 10

// main gpio port
using gpioPort = libMcuLL::hw::port<libMcuLL::hw::IOports::PORT0>;

// Crystal osillator pins
using xtalInPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN08>;
using xtalOutPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN09>;
// test pin pair 0, connected to eachother via 3.3KOhm resistor, testboard PIN1
using test0PinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN00>;
using test1PinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN14>;
// auxillary test pin, connected to nothing, testboard PIN2
using test2PinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN07>;
// auxillary test pin, connected to nothing, testboard PIN3
using test3PinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN06>;
// PWM test pin pair, connected to 1K 10uF RC, testboard RC_out1
using testPwmInType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN01>;
// PWM test pin pair, connected to 1K 10uF RC, testboard RC_in1
using testPwmOutType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN15>;
// I2C Clock pin pair, pulled up to 2.2K to 3.3V
using i2cSclOutPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN10>;
// I2C Data pin pair, pulled up to 2.2K to 3.3V
using i2cSdaOutPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN11>;

// Peripheral functions
using mainI2cSdaFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::I2C_SDA_IO>;
using mainI2cSclFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::I2C_SCL_IO>;
using xtalInFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALOUT>;
using mainSpiSckFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_SCK_IO>;
using mainSpiSselFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_SSEL_IO>;
using mainSpiMosiFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_MOSI_IO>;
using mainSpiMisoFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_MISO_IO>;
using mainUartTxFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_TXD_O>;
using mainUartRxFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_RXD_I>;

constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr test0PinType test0Pin;
constexpr test1PinType test1Pin;
constexpr test2PinType test2Pin;
constexpr test3PinType test3Pin;
constexpr i2cSclOutPinType i2cSclOutPin;
constexpr i2cSdaOutPinType i2cSdaOutPin;
constexpr testPwmInType pwmInPin;
constexpr testPwmOutType pwmOutPin;
constexpr gpioPort mainPort;

constexpr xtalInFunctionType xtalInFunction;
constexpr xtalOutFunctionType xtalOutFunction;
constexpr mainI2cSclFunctionType i2cMainSclFunction;
constexpr mainI2cSdaFunctionType i2cMainSdaFunction;
constexpr mainSpiSckFunctionType spiMainSckFunction;
constexpr mainSpiSselFunctionType spiMainSselFunction;
constexpr mainSpiMosiFunctionType spiMainMosiFunction;
constexpr mainSpiMisoFunctionType spiMainMisoFunction;
constexpr mainUartTxFunctionType uartMainTxFunction;
constexpr mainUartRxFunctionType uartMainRxFunction;

extern libMcuLL::sw::iocon::iocon<libMcuLL::hw::IOCON_cpp> ioconPeripheral;
extern libMcuLL::sw::swm::swm<libMcuLL::hw::SWM_cpp> swmPeriperhal;
extern libMcuLL::sw::gpio::gpio<libMcuLL::hw::GPIO_cpp> gpioPeripheral;
extern libMcuLL::sw::spi::spiSync<libMcuLL::hw::SPI0_cpp, libMcuLL::sw::spi::chipEnables, std::uint16_t> spiSyncPeripheral;
extern libMcuLL::sw::spi::spiAsync<libMcuLL::hw::SPI0_cpp, libMcuLL::sw::spi::chipEnables, std::uint16_t> spiAsyncPeripheral16;
extern libMcuLL::sw::spi::spiAsync<libMcuLL::hw::SPI0_cpp, libMcuLL::sw::spi::chipEnables, std::uint8_t> spiAsyncPeripheral8;
extern libMcuLL::sw::syscon::syscon<libMcuLL::hw::SYSCON_cpp> sysconPeripheral;
extern libMcuLL::sw::usart::usartSync<libMcuLL::hw::USART0_cpp, std::uint8_t> usartSyncPeripheral;
extern libMcuLL::sw::usart::usartAsync<libMcuLL::hw::USART0_cpp, std::uint8_t> usartAsyncPeripheral;
extern libMcuLL::sw::i2c::i2c<libMcuLL::hw::I2C0_cpp> i2cPeripheral;
extern libMcuLL::sw::sct::sct<libMcuLL::hw::SCT0_cpp> sctPeripheral;

void boardInit(void);
void crudeDelay(uint32_t iterations);

#endif