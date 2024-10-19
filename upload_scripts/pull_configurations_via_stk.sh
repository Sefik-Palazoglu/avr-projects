#!/bin/bash

# Example usage on MacOS:
# ./pull_configurations_via_stk.sh -c /opt/homebrew/Cellar/avrdude/8.0/.bottle/etc/avrdude.conf -p /dev/cu.usbserial-10

# Usage message function
usage() {
    echo "Usage: $0 -c <config_file> -p <upload_port>"
    exit 1
}

# Default values
AVRDUDE=avrdude
PROCESSOR=atmega328p
PROGRAMMER=arduino
BAUD_RATE=115200

# Parse command line arguments
while getopts ":c:p:" opt; do
    case ${opt} in
        c)
            CONFIG_FILE=${OPTARG}
            ;;
        p)
            UPLOAD_PORT=${OPTARG}
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            usage
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            usage
            ;;
    esac
done

# Check if CONFIG_FILE and UPLOAD_PORT are set
if [ -z "$CONFIG_FILE" ] || [ -z "$UPLOAD_PORT" ]; then
    echo "Error: Configuration file and upload port are required."
    usage
fi

# Set AVRDUDE flags
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -V -p ${PROCESSOR} -c ${PROGRAMMER} -P ${UPLOAD_PORT} -b ${BAUD_RATE} -D"

# Run avrdude command
$AVRDUDE $AVRDUDE_FLAGS -U lfuse:r:lfuse.hex:h -U hfuse:r:hfuse.hex:h -U efuse:r:efuse.hex:h -U lock:r:lock.hex:h -U signature:r:signature.hex:h -U calibration:r:calibration.hex:h -U flash:r:flash.hex:i
