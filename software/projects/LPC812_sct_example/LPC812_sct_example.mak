# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := LPC812_sct_examples
BOARD := nuclone_board
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC812M101DH20
$(NAME)_DEFINES := 
$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded

# example handling
$(NAME)_EXAMPLES = rep_int blinky_match match_toggle simple_pwm center_pwm 2chan_pwm deadtime_pwm 4chan_pwm WS2812_protocol

# check if valid example is defined
ifeq ($(PROJECT),$(NAME))
ifndef EXAMPLE
$(error No example is defined, define with EXAMPLES=examplefile . \
You can choose from: $($(NAME)_EXAMPLES))
else
ifeq (, $(findstring $(EXAMPLE),$($(NAME)_EXAMPLES)))
$(error Unknown example $(EXAMPLE)! Possible choices: $($(NAME)_EXAMPLES))
endif
endif
endif

$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp \
$(PROJ_DIR)/src/$(EXAMPLE).cpp
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
$(NAME)_DEFINES += -D$(BOARD)