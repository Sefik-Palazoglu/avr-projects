#include <avr/io.h>
#include <avr/boot.h>

void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags)
{
	WDTCSR = ((0x01 << WDCE) | (0x01 << WDE));
	WDTCSR = flags;
}

void BOOTLOADER_SECTION Go_To_Application_Start(void)
{
	Configure_Watchdog_Timer(0x00); // ignore watchdog timeout
	asm("eor r30, r30");
	asm("eor r31, r31");
	asm("ijmp");
}

void BOOTLOADER_SECTION Init_Timer1(void)
{
	TCCR1B = (1 << CS12) | (1 << CS10);
}
