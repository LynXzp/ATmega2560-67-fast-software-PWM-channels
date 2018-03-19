# Fast software PWM for independent LED slow fade flashing. Maximum channels, no visible flashing.

Project for ATtiny167 use first version of software PWM - just simulation of hardware TCNT and OCR registers. Maximum is 20 channel, or it become visible unpleasent flashing.

Project for ATmega2560 use advanced algorithm. It allow to use much more channels (at least 67). Algorithm description: in main infinity cycle code prepearing array of bytes that will be wroten directly to the ports, so in memory always excists data for on/off each pin all time, and in interrut it cycling sended to the PORTs.

All software wrotten using C99/C++, avr-gcc compiler, and contain linux script for compilation and programming. Compatible with Atmel Studio.

Video of result working is attached.