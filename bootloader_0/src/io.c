#include <avr/io.h>
#include "io.h"

uint8_t* ram_buffer = (uint8_t*) RAMSTART;

uint8_t read_and_zero_mcusr(void)
{
  uint8_t mcusr = MCUSR;
  MCUSR = 0x00;
  return mcusr;
}

uint8_t was_external_reset(uint8_t previous_mcusr)
{
  return previous_mcusr & _BV(EXTRF);
}