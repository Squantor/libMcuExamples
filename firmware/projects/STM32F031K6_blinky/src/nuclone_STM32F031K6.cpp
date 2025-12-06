/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <nuclone_STM32F031K6.hpp>

libmcull::systick::Systick<libmcuhw::SystickAddress> systickPeripheral;
libmcull::nvic::Nvic<libmcuhw::NvicAddress, libmcuhw::ScbAddress> nvicPeripheral;

volatile std::uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}
}

auto systickIsrLambda = []() {
  ticks = ticks + 1;
  gpioaRegisters->ODR = gpioaRegisters->ODR ^ 0x01;
};

void boardInit(void) {
  rccRegisters->AHBENR = 0x00020014;
  gpioaRegisters->MODER = 0x28000001;

  systickPeripheral.Init(CLOCK_HCLK / TICKS_PER_S);
  systickPeripheral.Start(systickIsrLambda);
}
