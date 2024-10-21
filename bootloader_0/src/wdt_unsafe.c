#include <sys/types.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include "wdt_unsafe.h"

static void configure_wdt_unsafe(uint8_t flags);

static void configure_wdt_unsafe(uint8_t flags)
{
  _WD_CONTROL_REG = (_BV(_WD_CHANGE_BIT) | _BV(WDE));
  _WD_CONTROL_REG = flags;
}

void disable_wdt_unsafe(void)
{
  configure_wdt_unsafe(0x00);
}

void enable_wdt_timeout15ms_unsafe(void)
{
  configure_wdt_unsafe(_BV(WDE) | WDTO_15MS);
}

void enable_wdt_timeout1s_unsafe(void)
{
  configure_wdt_unsafe(_BV(WDE) | WDTO_1S);
}

void wdt_reset_unsafe(void)
{
  wdt_reset();
}