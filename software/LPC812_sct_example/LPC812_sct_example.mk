# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210113

# project settings
MCU = LPC812M101DH20
TARGET = MCU
BOARD = nuclone_board

# valid examples
EXAMPLES = rep_int blinky_match match_toggle simple_pwm center_pwm 2chan_pwm deadtime_pwm 4chan_pwm WS2812_protocol

# check if valid example is defined
ifndef EXAMPLE
$(error No example is defined, define with EXAMPLES=examplefile . \
You can choose from: $(EXAMPLES))
else
ifeq (, $(findstring $(EXAMPLE),$(EXAMPLES)))
$(error Unknown example $(EXAMPLE)! Possible choices: $(EXAMPLES))
endif
endif

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/$(EXAMPLE).cpp

INCLUDES += -IlibMcuLL/inc -I$(PROJECT)/inc


