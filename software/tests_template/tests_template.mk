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
MCU = CortexM0
TARGET = MCU
BOARD = board_tests

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/microcontroller_teardown.cpp \
$(PROJECT)/src/test_microcontroller_teardown.cpp \

INCLUDES += -I$(PROJECT)/inc -Icommon/inc

DEFINES += -DMINUNIT_MAX_TESTS=10
DEFINES += -DMINUNIT_REPORT_DISABLE # saves load of flash space
