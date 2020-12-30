# MIT License

# Copyright (c) 2020 Bart Bilos

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# project settings
#
# Version: 20200426



# project settings
PROJECT ?= LPC812M101JDH20_test_master
TARGET = MCU
MCU = LPC812M101JDH20
BOARD = LPC812M101JDH20_nuclone


# project sources
FILES += LPC812M101JDH20_test_slave/src/main_test_slave.cpp \
LPC812M101JDH20_test_slave/src/slave_test_gpio.cpp \
LPC812M101JDH20_test_slave/src/startup.cpp \
common/src/$(BOARD).cpp common/src/systick.cpp common/src/test_sync.cpp

LIBS += -lgcc
INCLUDES += -ILPC812M101JDH20_test_slave/inc -IlibMcuLL/inc -Icommon/inc


