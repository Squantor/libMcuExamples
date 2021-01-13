# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210113

# includes of additional libraries
include squantorLibC/squantorLibC.mk
include squantorLibEmbeddedC/squantorLibEmbeddedC.mk

# project settings
MCU = LPC812M101DH20
TARGET = MCU
BOARD ?= nuclone_board

# project sources
FILES +=  $(PROJECT)/src/strings.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/stream_uart.cpp \
$(PROJECT)/src/main.cpp

LIBS +=
INCLUDES += -IlibMcuLL/inc -I$(PROJECT)/inc

