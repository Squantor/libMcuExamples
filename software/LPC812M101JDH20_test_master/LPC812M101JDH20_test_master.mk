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
FILES += $(PROJECT)/src/main_test_master.cpp \
$(PROJECT)/src/master_test_gpio.cpp \
common/src/$(BOARD).cpp common/src/systick.cpp common/src/test_sync.cpp

INCLUDES += -ILPC812M101JDH20_test_master/inc -Icommon/inc


