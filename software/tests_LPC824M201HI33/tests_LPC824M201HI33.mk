# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210116

#additional library includes
include libMcuLL/libMcuLL.mk
include squantorLibC/squantorLibC.mk
include squantorLibEmbedded/squantorLibEmbedded.mk
include squantorMinUnit/squantorMinUnit.mk

# project settings
MCU = LPC824M201HI33
TARGET = MCU
BOARD = nuclone_LPC824M201HI33_tests

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/LPC824M201HI33_teardown.cpp \
$(PROJECT)/src/test_LPC824M201HI33_gpio.cpp \
$(PROJECT)/src/test_LPC824M201HI33_iocon.cpp


INCLUDES += -I$(PROJECT)/inc -Icommon/inc

DEFINES += -DMINUNIT_MAX_TESTS=100 
DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space
