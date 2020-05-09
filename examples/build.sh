# build all the examples and clean afterwards to quick check builds
#!/bin/bash
make -j18 PROJECT=CortexM0_example config=release
make -j18 PROJECT=CortexM0_example config=debug
make -j18 PROJECT=CortexM0plus_example config=release
make -j18 PROJECT=CortexM0plus_example config=debug
make -j18 PROJECT=CortexM3_example config=release
make -j18 PROJECT=CortexM3_example config=debug
make -j18 PROJECT=CortexM4_example config=release
make -j18 PROJECT=CortexM4_example config=debug
make -j18 PROJECT=LPC812_example config=release
make -j18 PROJECT=LPC812_example config=debug
make -j18 PROJECT=LPC824_example config=release
make -j18 PROJECT=LPC824_example config=debug
make -j18 PROJECT=CortexM0_example clean
