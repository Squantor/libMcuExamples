# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 202221229

# project settings
NAME := LPC812M101DH20_tests
BOARD := nuclone_LPC812M101DH20_tests
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC812M101DH20

$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded squantorLibEmbeddedCortexM squantorMinUnit

$(NAME)_DEFINES += -DMINUNIT_MAX_TESTS=100 
$(NAME)_DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project sources
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp \
$(PROJ_DIR)/src/LPC812M101DH20_teardown.cpp \
$(PROJ_DIR)/src/test_LPC812M101DH20_gpio.cpp \
$(PROJ_DIR)/src/test_LPC812M101DH20_iocon.cpp \
$(PROJ_DIR)/src/test_LPC812M101DH20_usart_polled.cpp

$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)


