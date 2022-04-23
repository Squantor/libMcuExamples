# build all tests, great to see if something broke during refactoring as the tests use a lot of libmcull
#!/bin/bash
make -j18 PROJECT=tests_LPC812M101DH20 CONFIG=release
make -j18 PROJECT=tests_LPC812M101DH20 CONFIG=debug
make -j18 PROJECT=tests_LPC824M201HI33 CONFIG=release
make -j18 PROJECT=tests_LPC824M201HI33 CONFIG=debug
make -j18 PROJECT=tests_LPC844M201BD64 CONFIG=release
make -j18 PROJECT=tests_LPC844M201BD64 CONFIG=debug
make -j18 clean
