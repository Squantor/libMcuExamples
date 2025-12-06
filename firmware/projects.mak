# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all projects
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_small_blinky/nuclone_LPC845QFP48_small_blinky.mak
include $(BASE_DIR)/projects/PC/PC.mak
include $(BASE_DIR)/projects/RP2040_blinky/RP2040_blinky.mak
include $(BASE_DIR)/projects/STM32F030K6_blinky/STM32F030K6_blinky.mak
include $(BASE_DIR)/projects/STM32F031K6_blinky/STM32F031K6_blinky.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_template/nuclone_LPC845QFP48_template.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_oled_i2c/nuclone_LPC845QFP48_oled_i2c.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_oled_spi/nuclone_LPC845QFP48_oled_spi.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_memlcd/nuclone_LPC845QFP48_memlcd.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_sct_ws2812/nuclone_LPC845QFP48_sct_ws2812.mak
include $(BASE_DIR)/projects/nuclone_LPC845QFP48_SH1106_i2c/nuclone_LPC845QFP48_SH1106_i2c.mak
