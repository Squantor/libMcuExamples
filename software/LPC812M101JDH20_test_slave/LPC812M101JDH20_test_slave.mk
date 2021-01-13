# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20210113

include libMcuLL/libMcuLL.mk

# project settings
MCU = LPC812M101DH20
TARGET = MCU
BOARD = LPC812M101JDH20_nuclone

# project sources
FILES += $(PROJECT)/src/main_test_slave.cpp \
$(PROJECT)/src/slave_test_gpio.cpp \
common/src/$(BOARD).cpp common/src/systick.cpp common/src/test_sync.cpp

INCLUDES += -I$(PROJECT)/inc -Icommon/inc


