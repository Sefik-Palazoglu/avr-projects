#include <avr/io.h>
#include <avr/boot.h>
#include <avr/wdt.h>

void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags);
uint8_t BOOTLOADER_SECTION Read_USART();

void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags)
{
	WDTCSR = ((0x01 << WDCE) | (0x01 << WDE));
	WDTCSR = flags;
}

void BOOTLOADER_SECTION __attribute((noreturn)) Go_To_Application_Start(void)
{
	Configure_Watchdog_Timer(0x00); // ignore watchdog timeout
	// RunApp();
	asm volatile (
		"eor r30, r30\n"
		"eor r31, r31\n"
		"ijmp\n"
	);
}

void BOOTLOADER_SECTION Init_UART(void)
{
	UCSR0A = (1 << U2X0);
	UCSR0B = ((1 << RXEN0) | (1 << TXEN0));
	UCSR0C = ((1 << UCSZ01) | (1 << UCSZ00));
	UBRR0L = 0x10;
}

uint8_t BOOTLOADER_SECTION Read_USART()
{
	while (UCSR0A & (1 << RXC0)) ;

	if (!(UCSR0A & (1 << FE0)))
	{
		wdt_reset();
	}

	return UDR0;
}
