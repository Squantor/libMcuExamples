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
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=rep_int
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=rep_int
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=blinky_match
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=blinky_match
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=match_toggle
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=match_toggle
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=simple_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=simple_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=center_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=center_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=2chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=2chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release EXAMPLE=deadtime_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=deadtime_pwm
make -j18 PROJECT=LPC812_uart_example clean
