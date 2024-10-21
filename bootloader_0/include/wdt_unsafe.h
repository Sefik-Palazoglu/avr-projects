#ifndef WDT_UNSAFE_H
#define WDT_UNSAFE_H

void disable_wdt_unsafe(void);
void enable_wdt_timeout15ms_unsafe(void);
void enable_wdt_timeout1s_unsafe(void);
void wdt_reset_unsafe(void);

#endif // WDT_UNSAFE_H