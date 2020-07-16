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
# Version: 20200625

# project settings
MCU = LPC812M101JDH20
TARGET = MCU
BOARD = nuclone_board

# valid examples
EXAMPLES = rep_int blinky_match match_toggle simple_pwm

# check if valid example is defined
ifndef EXAMPLE
$(error No example is defined, define with EXAMPLES=examplefile . \
You can choose from: $(EXAMPLES))
else
ifeq (, $(findstring $(EXAMPLE),$(EXAMPLES)))
$(error Unknown example $(EXAMPLE)! Possible choices: $(EXAMPLES))
endif
endif

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/$(BOARD).cpp \
$(PROJECT)/src/$(EXAMPLE).cpp

INCLUDES += -IlibMcuLL/inc -I$(PROJECT)/inc


