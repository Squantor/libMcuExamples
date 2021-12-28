/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

volatile int var;

int main() {
  while (1) {
    var = var ^ 0x55;
    __NOP();
  }
}
