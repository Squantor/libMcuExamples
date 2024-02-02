/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef NUCLONE_CORTEXM0PLUS_TESTS_HPP
#define NUCLONE_CORTEXM0PLUS_TESTS_HPP

#define CLOCK_XTAL (12000000u)
#define CLOCK_CPU (12000000u)

#include <mcu_ll.hpp>

#define TICKS_PER_S 10

void boardInit(void);
void crudeDelay(uint32_t iterations);

#endif