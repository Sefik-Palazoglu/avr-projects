#!/bin/bash

# Example usage on MacOS:
# ./pull_configurations_via_usbtinyISP.sh -c /opt/homebrew/Cellar/avrdude/8.0/.bottle/etc/avrdude.conf

# Usage message function
usage() {
    echo "Usage: $0 -c <config_file>"
    exit 1
}

# Default values
AVRDUDE=avrdude
PROCESSOR=atmega328p
PROGRAMMER=usbtiny

# Parse command line arguments
while getopts ":c:" opt; do
    case ${opt} in
        c)
            CONFIG_FILE=${OPTARG}
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

# Check if CONFIG_FILE is set
if [ -z "$CONFIG_FILE" ]; then
    echo "Error: Configuration file is required."
    usage
fi

# Set AVRDUDE flags
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -p ${PROCESSOR} -c ${PROGRAMMER}"

# Run avrdude command
$AVRDUDE $AVRDUDE_FLAGS -U lfuse:r:lfuse.hex:h -U hfuse:r:hfuse.hex:h -U efuse:r:efuse.hex:h -U lock:r:lock.hex:h -U signature:r:signature.hex:h -U calibration:r:calibration.hex:h
