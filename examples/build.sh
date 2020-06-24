# build all the examples and clean afterwards to quick check builds
#!/bin/bash
make -j18 PROJECT=CortexM0_example CONFIG=release
make -j18 PROJECT=CortexM0_example CONFIG=debug
make -j18 PROJECT=CortexM0plus_example CONFIG=release
make -j18 PROJECT=CortexM0plus_example CONFIG=debug
make -j18 PROJECT=CortexM3_example CONFIG=release
make -j18 PROJECT=CortexM3_example CONFIG=debug
make -j18 PROJECT=CortexM4_example CONFIG=release
make -j18 PROJECT=CortexM4_example CONFIG=debug
make -j18 PROJECT=LPC812_example CONFIG=release
make -j18 PROJECT=LPC812_example CONFIG=debug
make -j18 PROJECT=LPC824_example CONFIG=release
make -j18 PROJECT=LPC824_example CONFIG=debug
make -j18 PROJECT=CortexM0_example clean
