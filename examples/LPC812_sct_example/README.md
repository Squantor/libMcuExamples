# SCT cookbook implementations
This project contains all the examples from the [SCT cookbook by NXP](https://www.nxp.com/docs/en/application-note/AN11538.zip) ported to libMcuLL.
## Usage
If you want to try out the example, add the example to the build command like this:
```
make PROJECT=LPC812_sct_example EXAMPLE=match_toggle
```
Possible options are:
* ```rep_int``` demonstrating a repetitive interrupt per second.
* ```blinky_match``` demonstrating a blinking LED with the 32 bit timer on a match event
* ```match_toggle``` demonstrating a blinking LED with the Low 16 bit timer on match event with use of the toggle functionality
* ```simple_pwm``` demonstrating a pwm generator that increments step by step by a systick event, uses a 16bit timer
* ```center_pwm``` demonstrating a pwm generator that uses a up/down counter to center the pwm, incremented step by step by a systick event, uses a 16 bit timer
* ```2chan_pwm``` demonstrating a two channel PWM generator and switching between those depending on an external input, this external input is periodically turned on ad off by another pin. See the required hardware for pinning.
## Hardware
The following hardware was used:
* [Black Magic Probe](https://github.com/blacksphere/blackmagic/wiki)
* [Nuclone board for LPC812](https://github.com/Squantor/squantorDevelBoards/tree/master/hardware/nuclone_LPC812M101JDH20)
Each example requires some additional hardware
### Repetitive interrupt
No additional hardware required, place a breakpoint in the ISR to observe operation.
### Blinky match
One LED with series resistor on PIN17.
### Match toggle
One LED with series resistor on PIN17.
### simple pwm
One LED with series resistor on PIN17.
### center_pwm
One LED with series resistor on PIN17.
### 2 channel pwm
One LED on PIN17 and one LED on PIN13, one wire from PIN16 to PIN4.
## TODO
* implement the PWM with deadtime example
* implement the match reload example
* implement the four channel PWM example
* implement the decoding PWM example
* implement the WS2812 LED driver example
* implement the PWM with 0 to 100% duty cycle
* implement the PWM with Low and High timer example
* pictures/scope shots per example
