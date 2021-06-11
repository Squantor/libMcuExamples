# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210116

#additional library includes
include libMcuLL/libMcuLL.mk
include squantorLibC/squantorLibC.mk
include libEmbedded/libEmbedded.mk
include squantorMinUnit/squantorMinUnit.mk

# project settings
MCU = LPC845M301BD48
TARGET = MCU
BOARD = nuclone_LPC845M301BD48_tests

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/LPC845M301_teardown.cpp \
$(PROJECT)/src/test_LPC845M301_teardown.cpp \
$(PROJECT)/src/test_LPC845M301_gpio.cpp \
$(PROJECT)/src/test_LPC845M301_iocon.cpp \
$(PROJECT)/src/test_LPC845M301_usart_polled.cpp \
$(PROJECT)/src/test_LPC845M301_spi_polled.cpp

INCLUDES += -I$(PROJECT)/inc -Icommon/inc

DEFINES += -DMINUNIT_MAX_TESTS=100 
DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space
