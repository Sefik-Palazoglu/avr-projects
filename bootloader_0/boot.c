#include <avr/io.h>
#include <avr/boot.h>
#include <avr/wdt.h>

void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags);
uint8_t BOOTLOADER_SECTION Read_USART();
void BOOTLOADER_SECTION Write_USART(uint8_t data);

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

void BOOTLOADER_SECTION Write_USART(uint8_t data)
{
	while (!(UCSR0A & (1 < UDRE0))) ;

	UDR0 = data;
}

void BOOTLOADER_SECTION read_another_0x20_and_write_0x14()
{
	uint8_t data = Read_USART();
	if (data == 0x20)
	{
		Write_USART(0x14);
	}
	else
	{
		Configure_Watchdog_Timer((1 << WDE));
		while (1) ;
	}
}

void BOOTLOADER_SECTION Read_N_Characters(uint8_t count)
{
	for (uint8_t i = 0; i < count; i++)
	{
		Read_USART();
	}
	read_another_0x20_and_write_0x14();
}
