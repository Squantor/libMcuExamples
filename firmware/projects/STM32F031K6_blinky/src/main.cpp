/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <nuclone_STM32F031K6.hpp>

int main() {
  boardInit();
  while (1) {
    libmcull::nop();
  }
}
