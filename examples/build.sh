# build all the templates and clean afterwards
#!/bin/bash
make -j18 PROJECT=LPC812_clock_redesign CONFIG=release
make -j18 PROJECT=LPC812_clock_redesign CONFIG=debug
make -j18 PROJECT=LPC812_cpp_tests CONFIG=release
make -j18 PROJECT=LPC812_cpp_tests CONFIG=debug
make -j18 PROJECT=LPC812_i2c_example CONFIG=release
make -j18 PROJECT=LPC812_i2c_example CONFIG=debug
make -j18 PROJECT=LPC812_uart_example CONFIG=release
make -j18 PROJECT=LPC812_uart_example CONFIG=debug
make -j18 PROJECT=LPC812_uart_example clean
