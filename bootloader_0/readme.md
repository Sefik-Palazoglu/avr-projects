## IDE Configuration

### Include Directory
Depending on your avr installation you need to instruct your IDE to 'see' avr library headers.

Supposing your avr library base is located at ${AVR_ROOT}, your IDE needs to 'see' these include directories

* ${AVR_ROOT}/lib/avr-gcc/9/gcc/avr/9.4.0/include
* ${AVR_ROOT}/lib/avr-gcc/9/gcc/avr/9.4.0/include-fixed
* ${AVR_ROOT}/avr/include

You need to instruct you IDE to 'see' default header directory

* ${WORKSPACE_DIRECTORY}/include

### C Defines
Depending on your avr device, you need to instruct your IDE to consider some C defines as defined (some with values)

* __AVR_ATmega328P__
  * This is used for io.h header, we are using atmega328p chip on Arduino Uno.
* __AVR_DEVICE_NAME__=atmega328p
  * This is used for io.h header, we are using atmega328p chip on Arduino Uno. This is only for device name.
* F_CPU=16000000L
  * This is the default CPU frequency. If you change the CPU frequency,