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
MCU = LPC844M201BD64
TARGET = MCU
BOARD = nuclone_LPC844M201BD64_tests

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/LPC844M201_teardown.cpp \
$(PROJECT)/src/test_LPC844M201_teardown.cpp \
$(PROJECT)/src/test_LPC844M201_gpio.cpp \
$(PROJECT)/src/test_LPC844M201_iocon.cpp \
$(PROJECT)/src/test_LPC844M201_usart_polled.cpp \
$(PROJECT)/src/test_LPC844M201_spi_polled.cpp \
$(PROJECT)/src/test_LPC844M201_i2c_polled.cpp

INCLUDES += -I$(PROJECT)/inc -Icommon/inc

DEFINES += -DMINUNIT_MAX_TESTS=100 
DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space
