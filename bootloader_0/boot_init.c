#include <avr/io.h>
#include <avr/boot.h>
#include <avr/wdt.h>

void BOOTLOADER_SECTION __attribute((noreturn)) Go_To_Application_Start(void);
void BOOTLOADER_SECTION Init_UART(void);
void BOOTLOADER_SECTION Configure_Watchdog_Timer(uint8_t flags);
uint8_t BOOTLOADER_SECTION Read_USART();
void BOOTLOADER_SECTION Write_USART(uint8_t data);
void BOOTLOADER_SECTION read_another_0x20_and_write_0x14();
void BOOTLOADER_SECTION Read_N_Characters(uint8_t count);

void BOOTLOADER_SECTION __attribute__ ((used)) _Noreturn my_bootloader(void)
{
	asm volatile ("eor r1, r1");
	uint8_t mcusr = MCUSR;
	uint16_t cursor;
	MCUSR = 0x00;

	if (mcusr & (1 << EXTRF))
	{
		Init_UART();
		Configure_Watchdog_Timer((1 << WDE) | (1 << WDP2) | (1 << WDP1));
		wdt_reset();
		while (1)
		{
			uint8_t usart_read_0 = Read_USART();
			if (usart_read_0 == 0x41)
			{
				uint8_t usart_read_1 = Read_USART();
				read_another_0x20_and_write_0x14();
				if (usart_read_1 == 0x81 || usart_read_1 == 0x82)
					Write_USART(0x04);
				else
					Write_USART(0x03);
			}
			else if (usart_read_0 == 0x42)
			{
				Read_N_Characters(0x14);
			}
			else if (usart_read_0 == 0x45)
			{
				Read_N_Characters(0x05);
			}
			else if (usart_read_0 == 0x55)
			{
				cursor = 0;
				cursor = Read_USART();
				cursor |= (Read_USART() << 8);
				cursor *= 2;
				read_another_0x20_and_write_0x14();
			}
			else if (usart_read_0 == 0x56)
			{
				Read_N_Characters(0x04);
				Write_USART(0x00);
			}
			else if (cursor == 0)
			{
				Write_USART(0xDD);
			}

			Write_USART(0x10);
		}
	}
	else
	{
		Go_To_Application_Start();
	}
}
