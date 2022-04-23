/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main test entry point for LPC824 libMcuLL tests
 */
#include <nuclone_LPC824M201HI33_tests.hpp>
#include <MinUnit.h>
#include <stream_uart.hpp>

void minunitReport(const char* string) {}

void minunitFailCallback(void) {
  __BKPT(0x00);
}

int main() {
  boardInit();
  minunitRun();
  if (minunitTestState.failures != 0) {
    minunitReport("Test failures detected\n");
  } else {
    minunitReport("All tests passed\n");
  }
  while (1) __BKPT(0xFE);
}
