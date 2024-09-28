#include <avr/io.h>
#include <avr/boot.h>
#include <avr/wdt.h>

void BOOTLOADER_SECTION __attribute((noreturn)) Go_To_Application_Start(void);
void BOOTLOADER_SECTION Init_UART(void);
void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags);
uint8_t BOOTLOADER_SECTION Read_USART();
void BOOTLOADER_SECTION Write_USART(uint8_t data);

void BOOTLOADER_SECTION __attribute__ ((used)) _Noreturn my_bootloader(void)
{
	asm volatile ("eor r1, r1");
	uint8_t mcusr = MCUSR;
	MCUSR = 0x00;

	if (mcusr & (1 << EXTRF))
	{
		Init_UART();
		Configure_Watchdog_Timer((1 << WDE) | (1 << WDP2) | (1 << WDP1));
		wdt_reset();
		uint8_t usart_read_0 = Read_USART();
		if (usart_read_0 == 0x41)
		{
			uint8_t usart_read_1 = Read_USART();
		}
		else
		{
		}
	}
	else
	{
		Go_To_Application_Start();
	}
}
