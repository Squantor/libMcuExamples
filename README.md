# libMcuLL examples and tests repository
This repository contains examples and tests for the [libMcuLL](https://github.com/Squantor/libMcuLL.git) library. The tests directory contains the integration tests for the library and are good examples in their own right. The examples directory contains templates what you can base your own projects on. 
## Checking out
use ```git clone --recurse-submodules https://github.com/Squantor/$(PROJECT).git``` to clone the repository and its submodules.
## Compiling
This project uses gnu make as its build system on a Linux platform. There are two build targets: release and debug. Release builds with optimizations and minimal debugging information. Debug builds with no optimization and full debug information.
```
$ make CONFIG=debug
$ make CONFIG=release
```
### Embedded targets
For debugging on embedded targets, the [Black Magic Probe](https://github.com/blacksphere/blackmagic/wiki) is used, scripts to use this debugger are present in the ```gdb_scripts``` directory. make can be used to invoke debugging:
```
make gdbbmp
```
This will build and debug the debug configuration of the executable as the release version contains minimal debugging information and is optimized, thus hard to debug.
```
make tpwrdisable
make tpwrenable
```
The black magic probe is capable of powering the target, these commands enable/disable this function.
### Depedencies
This program depends on [libMcuLL](https://github.com/Squantor/libMcuLL.git). This is automatically checked out when using ```git clone --recurse-submodules```.
## Usage
To use the software you need the following hardware:
* [Black magic probe](https://github.com/blacksphere/blackmagic)
But any other debugger can be used but would require some work to get working.
For running the tests, special hardware is required connecting up two microcontrollers and running the master and slave test projects. See the tests directory for more details.
# Visual Studio Code
The project examples and tests are developed using [Visual Studio Code](https://code.visualstudio.com/), debugging can also be done from the IDE but for now only with the black magic probe.
# TODO
The following tasks are still open:
* Completing the tests for the LPC812
* Completing the tests for the LPC824
* Completing the tests for the STM32F103
