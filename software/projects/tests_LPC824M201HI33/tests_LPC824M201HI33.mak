# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 202221229

# project settings
NAME := tests_LPC824M201HI33
BOARD := nuclone_LPC824M201HI33_tests
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC824M201HI33

$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded squantorLibEmbeddedCortexM squantorMinUnit

$(NAME)_DEFINES += -DMINUNIT_MAX_TESTS=100 
$(NAME)_DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project sources
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp \
$(PROJ_DIR)/src/LPC82X_interrupts.cpp \
$(PROJ_DIR)/src/LPC824M201HI33_teardown.cpp \
$(PROJ_DIR)/src/test_LPC824M201HI33_gpio.cpp \
$(PROJ_DIR)/src/test_LPC824M201HI33_iocon.cpp \
$(PROJ_DIR)/src/test_LPC824M201HI33_usart_polled.cpp \
$(PROJ_DIR)/src/test_LPC824M201HI33_pinint.cpp


$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc -Icommon/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
