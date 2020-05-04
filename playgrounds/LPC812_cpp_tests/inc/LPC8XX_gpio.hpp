/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/
/* 
LPC800 series common GPIO registers, defines and functions.
*/
#ifndef LPC8XX_GPIO_HPP
#define LPC8XX_GPIO_HPP

namespace mcuLL 
{
    static inline void GpioInit()
    {
        ClockEnablePeriphClock(SYSCTL_CLOCK_GPIO);
    }

    static inline void GpioDeInit()
    {
        ClockDisablePeriphClock(SYSCTL_CLOCK_GPIO);
    }

    static inline void GpioWritePortBit(uint32_t port, uint8_t pin, bool setting)
    {
        LPC_GPIO_PORT->B[port][pin] = setting;
    }

    static inline void GpioSetPinState(uint8_t port, uint8_t pin, bool setting)
    {
        LPC_GPIO_PORT->B[port][pin] = setting;
    }

    static inline bool GpioReadPortBit(uint32_t port, uint8_t pin)
    {
        return (bool) LPC_GPIO_PORT->B[port][pin];
    }

    static inline bool GpioGetPinState(uint8_t port, uint8_t pin)
    {
        return (bool) LPC_GPIO_PORT->B[port][pin];
    }

    static inline void GpioWriteDirBit(uint32_t port, uint8_t pin, bool setting)
    {
        if(setting)
        {
            LPC_GPIO_PORT->DIR[port] |= 1UL << pin;
        }
        else
        {
            LPC_GPIO_PORT->DIR[port] &= ~(1UL << pin);
        }
    }

    static inline void GpioSetPinDir(uint8_t port, uint8_t pin, bool output)
    {
        if (output) {
            GpioSetPinDIROutput(port, pin);
        }
        else {
            GpioSetPinDIRInput(port, pin);
        }
    }

    static inline bool GpioReadDirBit(uint32_t port, uint8_t bit)
    {
        return (bool) (((LPC_GPIO_PORT->DIR[port]) >> bit) & 1);
    }

    static inline bool GpioGetPinDIR(uint8_t port, uint8_t pin)
    {
        return GpioReadDirBit(port, pin);
    }

    static inline void GpioSetPortDIR(uint8_t port, uint32_t pinMask, bool outSet)
    {
        if(outSet) 
        {
            GpioSetPortDIROutput(port, pinMask);
        }
        else 
        {
            GpioSetPortDIRInput(port, pinMask);
        }
    }

    static inline void GpioSetPortDIRMask(uint8_t port, uint32_t pinMask, uint32_t outMask)
    {
        GpioSetPortDIRInput(port, pinMask & ~outMask);
        GpioSetPortDIROutput(port, pinMask & outMask);
    }

    static inline uint32_t GpioGetPortDIR(uint8_t port)
    {
        return LPC_GPIO_PORT->DIR[port];
    }

    static inline void GpioSetPortMask(uint8_t port, uint32_t mask)
    {
        LPC_GPIO_PORT->MASK[port] = mask;
    }

    static inline uint32_t GpioGetPortMask(uint8_t port)
    {
        return LPC_GPIO_PORT->MASK[port];
    }

    static inline void GpioSetPortValue(uint8_t port, uint32_t value)
    {
        LPC_GPIO_PORT->PIN[port] = value;
    }

    static inline uint32_t GpioGetPortValue(uint8_t port)
    {
        return LPC_GPIO_PORT->PIN[port];
    }

    static inline void GpioSetMaskedPortValue(uint8_t port, uint32_t value)
    {
        LPC_GPIO_PORT->MPIN[port] = value;
    }

    static inline uint32_t GpioGetMaskedPortValue(uint8_t port)
    {
        return LPC_GPIO_PORT->MPIN[port];
    }

    static inline void GpioSetValue(uint8_t portNum, uint32_t bitValue)
    {
        LPC_GPIO_PORT->SET[portNum] = bitValue;
    }

    static inline void GpioSetPortOutHigh(uint8_t port, uint32_t pins)
    {
        LPC_GPIO_PORT->SET[port] = pins;
    }

    static inline void GpioSetPinOutHigh(uint8_t port, uint8_t pin)
    {
        LPC_GPIO_PORT->SET[port] = (1 << pin);
    }

    static inline void GpioClearValue(uint8_t portNum, uint32_t bitValue)
    {
        LPC_GPIO_PORT->CLR[portNum] = bitValue;
    }

    static inline void GpioSetPortOutLow(uint8_t port, uint32_t pins)
    {
        LPC_GPIO_PORT->CLR[port] = pins;
    }

    static inline void GpioSetPinOutLow(uint8_t port, uint8_t pin)
    {
        LPC_GPIO_PORT->CLR[port] = (1 << pin);
    }

    static inline void GpioSetPortToggle(uint8_t port, uint32_t pins)
    {
        LPC_GPIO_PORT->NOT[port] = pins;
    }

    static inline void GpioSetPinToggle(uint8_t port, uint8_t pin)
    {
        LPC_GPIO_PORT->NOT[port] = (1 << pin);
    }

    static inline uint32_t GpioReadValue(uint8_t portNum)
    {
        return LPC_GPIO_PORT->PIN[portNum];
    }
}

#endif
