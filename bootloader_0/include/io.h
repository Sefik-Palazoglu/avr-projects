#ifndef BOOTLOADER_IO_H
#define BOOTLOADER_IO_H

#include <stdint.h>

uint8_t read_and_zero_mcusr(void);
uint8_t was_external_reset(uint8_t previous_mcusr);

extern uint8_t* ram_buffer;


#endif // BOOTLOADER_IO_H