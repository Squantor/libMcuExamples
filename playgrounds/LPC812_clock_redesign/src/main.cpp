/*
 * This is simple example file which does do any I/O and thus
 * can be compiled and run on any Cortex-M MCU. However, to see
 * its effect, you'll need to use debugger.
 */
#include <mcu_ll.h>
#include <board.hpp>
int main()
{
    boardInit();
    while (1) {
        __WFI();
    }
}
