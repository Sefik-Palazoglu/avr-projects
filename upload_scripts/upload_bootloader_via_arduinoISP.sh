#!/bin/bash

# Example usage on MacOS:
# ./upload_bootloader_via_arduinoISP.sh -c /opt/homebrew/Cellar/avrdude/8.0/.bottle/etc/avrdude.conf -p /dev/cu.usbserial-10 -b <path_to_bootloader_hex>

# Usage message function
usage() {
    echo "Usage: $0 -c <config_file> -p <upload_port> -b <bootloader_path>"
    exit 1
}

# Default values
AVRDUDE=avrdude
PROCESSOR=atmega328p
PROGRAMMER=stk500v1
BAUD_RATE=19200

# Parse command line arguments
while getopts ":c:p:b:" opt; do
    case ${opt} in
        c)
            CONFIG_FILE=${OPTARG}
            ;;
        p)
            UPLOAD_PORT=${OPTARG}
            ;;
        b)
            BOOTLOADER_PATH=${OPTARG}
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

# Check if CONFIG_FILE, UPLOAD_PORT, and BOOTLOADER_PATH are set
if [ -z "$CONFIG_FILE" ] || [ -z "$UPLOAD_PORT" ] || [ -z "$BOOTLOADER_PATH" ]; then
    echo "Error: Configuration file, upload port, and bootloader path are required."
    usage
fi

# Set AVRDUDE flags
AVRDUDE_FLAGS="-C ${CONFIG_FILE} -v -p ${PROCESSOR} -c ${PROGRAMMER} -P ${UPLOAD_PORT} -b ${BAUD_RATE}"

# Chip erase flag
CHIP_ERASE=-e

# Fuse and lock byte settings
LOCK_BYTE_NOLOCKS=0xFF
EXTENDED_FUSE_BYTE=0xFD
FUSE_HIGH_BYTE=0xDE
FUSE_LOW_BYTE=0xFF
LOCK_BYTE_LOCK_BOOT_SECTION=0xCF

# AVRDUDE write commands
WRITE_LOCK_NOLOCKS="-U lock:w:${LOCK_BYTE_NOLOCKS}:m"
WRITE_EFUSE="-U efuse:w:${EXTENDED_FUSE_BYTE}:m"
WRITE_HFUSE="-U hfuse:w:${FUSE_HIGH_BYTE}:m"
WRITE_LFUSE="-U lfuse:w:${FUSE_LOW_BYTE}:m"
WRITE_BOOTLOADER="-U flash:w:${BOOTLOADER_PATH}:i"
WRITE_LOCK_BOOT_SECTION="-U lock:w:${LOCK_BYTE_LOCK_BOOT_SECTION}:m"

# Enable command tracing
set -x

# Execute avrdude commands
$AVRDUDE $AVRDUDE_FLAGS $CHIP_ERASE $WRITE_LOCK_NOLOCKS $WRITE_EFUSE $WRITE_HFUSE $WRITE_LFUSE
$AVRDUDE $AVRDUDE_FLAGS $WRITE_BOOTLOADER $WRITE_LOCK_BOOT_SECTION

# Disable command tracing
set +x
