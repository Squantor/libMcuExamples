# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20201220

include libMcuLL/libMcuLL.mk
include squantorLibC/squantorLibC.mk
include libEmbedded/libEmbedded.mk
include squantorMinUnit/squantorMinUnit.mk

# project settings
MCU = LPC812M101DH20
TARGET = MCU
BOARD = nuclone_LPC812M101DH20_tests

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp

INCLUDES += -I$(PROJECT)/inc

