/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for modifications to small LPC845BD48 nuclone
 */
#ifndef NUCLONE_LPC845BD48_SMALL_NUCLONE_TEMPLATE_HPP
#define NUCLONE_LPC845BD48_SMALL_NUCLONE_TEMPLATE_HPP

#include <nuclone_LPC845BD48_small_common.hpp>

#define TICKS_PER_S 100

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

/**
 * @brief initializes the board
 */
void BoardInit(void);

#endif