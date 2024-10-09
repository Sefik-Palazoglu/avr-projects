#!/bin/bash

AVRDUDE=avrdude

CONFIG_FILE=/etc/avrdude.conf
PROCESSOR=atmega328p
PROGRAMMER=usbtiny
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -p ${PROCESSOR} -c ${PROGRAMMER}"

$AVRDUDE $AVRDUDE_FLAGS -U lfuse:r:lfuse.hex:h -U hfuse:r:hfuse.hex:h -U efuse:r:efuse.hex:h -U lock:r:lock.hex:h -U signature:r:signature.hex:h -U calibration:r:calibration.hex:h
