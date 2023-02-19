# build all the templates and clean afterwards
#!/bin/bash
make -j18 PROJECT=LPC812_i2c_example CONFIG=release_size
make -j18 PROJECT=LPC812_i2c_example CONFIG=release_speed
make -j18 PROJECT=LPC812_i2c_example CONFIG=debug
make -j18 PROJECT=LPC812M101DH20_blinky CONFIG=release_size
make -j18 PROJECT=LPC812M101DH20_blinky CONFIG=release_speed
make -j18 PROJECT=LPC812M101DH20_blinky CONFIG=debug
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=rep_int
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=rep_int
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=rep_int
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=blinky_match
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=blinky_match
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=blinky_match
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=match_toggle
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=match_toggle
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=match_toggle
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=simple_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=simple_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=simple_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=center_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=center_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=center_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=2chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=2chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=2chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=deadtime_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=deadtime_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=deadtime_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=4chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=4chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=4chan_pwm
make -j18 PROJECT=LPC812_sct_example CONFIG=release_size EXAMPLE=WS2812_protocol
make -j18 PROJECT=LPC812_sct_example CONFIG=release_speed EXAMPLE=WS2812_protocol
make -j18 PROJECT=LPC812_sct_example CONFIG=debug EXAMPLE=WS2812_protocol
make -j18 PROJECT=LPC812_uart_example CONFIG=release_size
make -j18 PROJECT=LPC812_uart_example CONFIG=release_speed
make -j18 PROJECT=LPC812_uart_example CONFIG=debug
make -j18 PROJECT=LPC824M201DH20_blinky CONFIG=release_size
make -j18 PROJECT=LPC824M201DH20_blinky CONFIG=release_speed
make -j18 PROJECT=LPC824M201DH20_blinky CONFIG=debug
make -j18 PROJECT=LPC824M201HI33_blinky CONFIG=release_size
make -j18 PROJECT=LPC824M201HI33_blinky CONFIG=release_speed
make -j18 PROJECT=LPC824M201HI33_blinky CONFIG=debug
make -j18 PROJECT=LPC845M301HI48_blinky CONFIG=release_size
make -j18 PROJECT=LPC845M301HI48_blinky CONFIG=release_speed
make -j18 PROJECT=LPC845M301HI48_blinky CONFIG=debug
make -j18 PROJECT=LPC1114BD48_323_blinky CONFIG=release_size
make -j18 PROJECT=LPC1114BD48_323_blinky CONFIG=release_speed
make -j18 PROJECT=LPC1114BD48_323_blinky CONFIG=debug
make -j18 PROJECT=LPC1125JBD48_303_blinky CONFIG=release_size
make -j18 PROJECT=LPC1125JBD48_303_blinky CONFIG=release_speed
make -j18 PROJECT=LPC1125JBD48_303_blinky CONFIG=debug
make -j18 PROJECT=PC CONFIG=release_size
make -j18 PROJECT=PC CONFIG=release_speed
make -j18 PROJECT=PC CONFIG=debug
make -j18 PROJECT=RP2040_blinky CONFIG=release_size
make -j18 PROJECT=RP2040_blinky CONFIG=release_speed
make -j18 PROJECT=RP2040_blinky CONFIG=debug
make -j18 PROJECT=STM32F030K6_blinky CONFIG=release_size
make -j18 PROJECT=STM32F030K6_blinky CONFIG=release_speed
make -j18 PROJECT=STM32F030K6_blinky CONFIG=debug
make -j18 PROJECT=STM32F031K6_blinky CONFIG=release_size
make -j18 PROJECT=STM32F031K6_blinky CONFIG=release_speed
make -j18 PROJECT=STM32F031K6_blinky CONFIG=debug
make -j18 PROJECT=LPC812M101DH20_tests CONFIG=release_size
make -j18 PROJECT=LPC812M101DH20_tests CONFIG=release_speed
make -j18 PROJECT=LPC812M101DH20_tests CONFIG=debug
make -j18 PROJECT=LPC824M201HI33_tests CONFIG=release_size
make -j18 PROJECT=LPC824M201HI33_tests CONFIG=release_speed
make -j18 PROJECT=LPC824M201HI33_tests CONFIG=debug
make -j18 PROJECT=LPC844M201BD64_tests CONFIG=release_size
make -j18 PROJECT=LPC844M201BD64_tests CONFIG=release_speed
make -j18 PROJECT=LPC844M201BD64_tests CONFIG=debug
make -j18 PROJECT=RP2040_tests CONFIG=release_size
make -j18 PROJECT=RP2040_tests CONFIG=release_speed
make -j18 PROJECT=RP2040_tests CONFIG=debug
make -j18 PROJECT=tests_template CONFIG=release_size
make -j18 PROJECT=tests_template CONFIG=release_speed
make -j18 PROJECT=tests_template CONFIG=debug
make -j18 clean
