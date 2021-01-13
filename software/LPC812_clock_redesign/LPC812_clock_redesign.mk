# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210113

# project settings
MCU = LPC812M101DH20
TARGET = MCU
BOARD ?= nuclone_board

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp

LIBS +=
INCLUDES += -IlibMcuLL/inc -I$(PROJECT)/inc


