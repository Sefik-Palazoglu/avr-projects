#!/bin/bash

if [ $# -lt 1 ]; then
  echo 1>&2 "$0: not enough arguments"
  exit 2
elif [ $# -gt 1 ]; then
  echo 1>&2 "$0: too many arguments"
  exit 2
fi

AVRDUDE=avrdude

CONFIG_FILE=/etc/avrdude.conf
PROCESSOR=atmega328p
PROGRAMMER=arduino
UPLOAD_PORT=/dev/ttyUSB0
BAUD_RATE=115200
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -V -p ${PROCESSOR} -c ${PROGRAMMER} -P ${UPLOAD_PORT} -b ${BAUD_RATE} -D"

HEX_PATH=$(realpath "$1")

WRITE_HEX="-U flash:w:${HEX_PATH}:i"

if [[ -f "$HEX_PATH" ]]; then
	set -x
	$AVRDUDE $AVRDUDE_FLAGS $WRITE_HEX
	set +x
else
	echo "Hex file not found: $HEX_PATH"
fi
