# avr-projects
Collection of comprehensive example projects on AVR architecture

## Things to do After a Fresh Ubuntu Install
This repository is configured to use with Linux. We need to follow these steps.
### SSH Connection Steps
#### Create an ssh key
`ssh-keygen -t ed25519 -C "<my.mail@example.com>"`
#### Add to ssh agent
run ssh-agent

`eval "$(ssh-agent -s)"`

add key to ssh-agent

`ssh-add ~/.ssh/id_ed25519`

#### Add ssh key to Github
Follow these https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account

### Git Related Steps
`sudo apt install git`

installs `git`, `git-man`, and `liberror-perl`

Clone the repository

`git clone git@github.com:Sefik-Palazoglu/avr-projects.git`

## AVR related steps
### Installing `binutils-avr`
Install the binary utilities.

run `sudo apt install binutils-avr`

You can reveal files maintained by a package with `dpkg -L <package-name>`

Notable tools from this package:
- `/usr/bin/avr-ar`
- `/usr/bin/avr-as`
- `/usr/bin/avr-ld`
- `/usr/bin/avr-nm`
- `/usr/bin/avr-objcopy`
- `/usr/bin/avr-objdump`
- `/usr/bin/avr-readelf`
- `/usr/bin/avr-strip`

### installing `gcc-avr`
Install the compiler.

run `sudo apt install gcc-avr`

You can reveal files maintained by a package with `dpkg -L <package-name>`

Notable tools from this package:
- `/usr/lib/gcc/avr/7.3.0/device-specs`
- `/usr/bin/avr-gcc`
- `/usr/bin/avr-gcc-ar`
- `/usr/bin/avr-gcc-nm`

### Installing `avr-libc`
Install the libraries for ease-of-use functions. For example a function for delaying in milliseconds.

You can reveal files maintained by a package with `dpkg -L <package-name>`

Notable tools from this package:
- `/usr/lib/avr/include/alloca.h`
- `/usr/lib/avr/include/avr/boot.h`
- `/usr/lib/avr/include/avr/delay.h`
- `/usr/lib/avr/include/avr/eeprom.h`
- `/usr/lib/avr/include/avr/fuse.h`
- `/usr/lib/avr/include/avr/interrupt.h`
- `/usr/lib/avr/include/avr/io.h`
- `/usr/lib/avr/include/avr/iom328p.h`
- `/usr/lib/avr/include/avr/lock.h`
- `/usr/lib/avr/include/avr/parity.h`
- `/usr/lib/avr/include/avr/pgmspace.h`
- `/usr/lib/avr/include/avr/portpins.h`
- `/usr/lib/avr/include/avr/power.h`
- `/usr/lib/avr/include/avr/sfr_defs.h`
- `/usr/lib/avr/include/avr/signal.h`
- `/usr/lib/avr/include/avr/signature.h`
- `/usr/lib/avr/include/avr/sleep.h`
- `/usr/lib/avr/include/avr/version.h`
- `/usr/lib/avr/include/avr/wdt.h`
- `/usr/lib/avr/include/util/delay.h`
- `/usr/lib/avr/include/util/delay_basic.h`
- `/usr/lib/avr/lib/avr5/crtatmega328p.o`
- `/usr/lib/avr/lib/avr5/libc.a`
- `/usr/lib/avr/lib/avr5/libm.a`
- `/usr/lib/avr/lib/avr5/libm3000.a`

### Installing `avrdude`
avrdude is a program for uploading and downloading form avr board.

Run
`sudo apt install avrdude`

This installs
- `avrdude`
- `libftdi1`
- `libhidapi-libusb0`
- `libusb-0.1-4`

## What to do after plugging in an avr board like an Arduino Uno?
run `sudo dmesg` before plugging in Arduino Uno.

Then, run `sudo dmesg` again after plugging in Arduino Uno. And examine the last messages. It will tell you which ttyUSB port the board has attached to. Example output:

```
[ 1965.812479] usb 1-1: new full-speed USB device number 7 using xhci_hcd
[ 1965.941439] usb 1-1: New USB device found, idVendor=1a86, idProduct=7523, bcdDevice= 2.64
[ 1965.941459] usb 1-1: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[ 1965.941467] usb 1-1: Product: USB Serial
[ 1966.034286] usbcore: registered new interface driver usbserial_generic
[ 1966.034299] usbserial: USB Serial support registered for generic
[ 1966.045550] usbcore: registered new interface driver ch341
[ 1966.045568] usbserial: USB Serial support registered for ch341-uart
[ 1966.045580] ch341 1-1:1.0: ch341-uart converter detected
[ 1966.045982] usb 1-1: ch341-uart converter now attached to ttyUSB0
```
This output means the board is attached to `/dev/ttyUSB0`

## What next?
After learning the usb port of the plugged in you can use `upload_hex_via_usb.sh`. It uses `/dev/ttyUSB0` by default, if yours is different edit and change the script!

Example usage: `sudo ../upload_scripts/upload_hex_via_usb.sh ./main.hex` 

### Pull the flash memory to a file as .hex format
`sudo avrdude -C /etc/avrdude.conf -v -V -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:r:./file:i`

### Disassemble the pulled hex file
`avr-objdump -d ./file -j .sec1 -m avr:5 > file.dump`

#### Disassemble the tiny bootloader section
`avr-objdump -d ./file -j .sec1 -m avr:5 --start-address=0x7e00 > bootloader.dump`
