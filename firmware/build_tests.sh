# build all tests, great to see if something broke during refactoring as the tests use a lot of libmcull
#!/bin/bash
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
