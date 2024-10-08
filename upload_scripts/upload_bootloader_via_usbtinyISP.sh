#!/bin/bash
#
# avrdude -p m328p -c usbtiny -v -U lfuse:r:lfuse.hex:h -U hfuse:r:hfuse.hex:h -U efuse:r:efuse.hex:h -U lock:r:lock.hex:h -U signature:r:signature.hex:h -U calibration:r:calibration.hex:h


AVRDUDE=avrdude

CONFIG_FILE=/etc/avrdude.conf
PROCESSOR=atmega328p
PROGRAMMER=usbtiny
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -p ${PROCESSOR} -c ${PROGRAMMER}"

BOOTLOADER_PATH=/home/losus/Desktop/avr-projects/optiboot_atmega328.hex
CHIP_ERASE=-e

# No locks
LOCK_BYTE_NOLOCKS=0xFF

# Enable Brown Out Detector with Vtyp=2.7V, Vmin=2.5V, Vmax=2.9V
EXTENDED_FUSE_BYTE=0xFD		

# Enable External Reset
# Disable debugWIRE
# Enable Serial program and data downloading
# Disable "Watchdog timer always on"
# EEPROM memory not preserved through chip erase
# Boot size is 256 words == 512 bytes
# Reset on Boot Section Start
FUSE_HIGH_BYTE=0xDE

# Disable Divide Clock by 8
# Disable Clock Output
# Start-up time 16KCK
# Low Power Crystal Oscillator External Clock 16.0Mhz, Slowly Rising Power 14CK + 65ms
FUSE_LOW_BYTE=0xFF

# Self programming and program memory read disabled for boot section from application section
LOCK_BYTE_LOCK_BOOT_SECTION=0xCF

WRITE_LOCK_NOLOCKS="-U lock:w:${LOCK_BYTE_NOLOCKS}:m"
WRITE_EFUSE="-U efuse:w:${EXTENDED_FUSE_BYTE}:m"
WRITE_HFUSE="-U hfuse:w:${FUSE_HIGH_BYTE}:m"
WRITE_LFUSE="-U lfuse:w:${FUSE_LOW_BYTE}:m"

WRITE_BOOTLOADER="-U flash:w:${BOOTLOADER_PATH}:i"
WRITE_LOCK_BOOT_SECTION="-U lock:w:${LOCK_BYTE_LOCK_BOOT_SECTION}:m"

set -x
$AVRDUDE $AVRDUDE_FLAGS $CHIP_ERASE $WRITE_LOCK_NOLOCKS $WRITE_EFUSE $WRITE_HFUSE $WRITE_LFUSE
$AVRDUDE $AVRDUDE_FLAGS $WRITE_BOOTLOADER $WRITE_LOCK_BOOT_SECTION
set +x
