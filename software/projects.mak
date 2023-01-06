# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all projects
include $(BASE_DIR)/projects/LPC812_i2c_example/LPC812_i2c_example.mak
include $(BASE_DIR)/projects/LPC812M101DH20_blinky/LPC812M101DH20_blinky.mak
include $(BASE_DIR)/projects/LPC812_sct_example/LPC812_sct_example.mak
include $(BASE_DIR)/projects/LPC812_uart_example/LPC812_uart_example.mak
include $(BASE_DIR)/projects/LPC824M201DH20_blinky/LPC824M201DH20_blinky.mak
include $(BASE_DIR)/projects/LPC824M201HI33_blinky/LPC824M201HI33_blinky.mak
include $(BASE_DIR)/projects/LPC845M301HI48_blinky/LPC845M301HI48_blinky.mak
include $(BASE_DIR)/projects/LPC1114BD48_323_blinky/LPC1114BD48_323_blinky.mak
include $(BASE_DIR)/projects/LPC1125JBD48_303_blinky/LPC1125JBD48_303_blinky.mak
include $(BASE_DIR)/projects/PC/PC.mak
include $(BASE_DIR)/projects/RP2040_blinky/RP2040_blinky.mak
include $(BASE_DIR)/projects/STM32F030K6_blinky/STM32F030K6_blinky.mak
include $(BASE_DIR)/projects/STM32F031K6_blinky/STM32F031K6_blinky.mak
include $(BASE_DIR)/projects/tests_LPC812M101DH20/tests_LPC812M101DH20.mak
include $(BASE_DIR)/projects/tests_LPC824M201HI33/tests_LPC824M201HI33.mak
include $(BASE_DIR)/projects/tests_LPC844M201BD64/tests_LPC844M201BD64.mak
include $(BASE_DIR)/projects/tests_RP2040/tests_RP2040.mak
include $(BASE_DIR)/projects/tests_template/tests_template.mak

