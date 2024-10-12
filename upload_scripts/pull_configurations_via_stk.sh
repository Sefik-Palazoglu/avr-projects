#!/bin/bash

AVRDUDE=avrdude

CONFIG_FILE=/etc/avrdude.conf
PROCESSOR=atmega328p
PROGRAMMER=arduino
UPLOAD_PORT=/dev/ttyUSB0
BAUD_RATE=115200
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -V -p ${PROCESSOR} -c ${PROGRAMMER} -P ${UPLOAD_PORT} -b ${BAUD_RATE} -D"

$AVRDUDE $AVRDUDE_FLAGS -U lfuse:r:lfuse.hex:h -U hfuse:r:hfuse.hex:h -U efuse:r:efuse.hex:h -U lock:r:lock.hex:h -U signature:r:signature.hex:h -U calibration:r:calibration.hex:h -U flash:r:flash.dump:i
