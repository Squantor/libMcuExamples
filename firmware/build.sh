# build all the templates and clean afterwards
#!/bin/bash
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
make -j18 PROJECT=RP2040_tests CONFIG=release_size
make -j18 PROJECT=RP2040_tests CONFIG=release_speed
make -j18 PROJECT=RP2040_tests CONFIG=debug
make -j18 PROJECT=nuclone_LPC845QFP48_small_blinky CONFIG=release_size
make -j18 PROJECT=nuclone_LPC845QFP48_small_blinky CONFIG=release_speed
make -j18 PROJECT=nuclone_LPC845QFP48_small_blinky CONFIG=debug
make -j18 clean
