#include <avr/io.h>
#include <avr/boot.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

void Configure_Watchdog_Timer(uint8_t flags)
{
	WDTCSR = (_BV(WDCE) | _BV(WDE));
	WDTCSR = flags;
}

void _Noreturn Go_To_Application_Start(void)
{
	Configure_Watchdog_Timer(0x00);
	asm volatile (
		"ijmp\n\t"
		:
		: "z" ((uint16_t)(0x0000))
	);
}

void Init_UART(void)
{
	UCSR0A = _BV(U2X0);
	UCSR0B = (_BV(RXEN0) | _BV(TXEN0));
	UCSR0C = (_BV(UCSZ01) | _BV(UCSZ00));
	UBRR0L = 0x10;
}

uint8_t Read_USART()
{
	loop_until_bit_is_set(UCSR0A, RXC0);

	if (bit_is_clear(UCSR0A, FE0))
	{
		wdt_reset();
	}

	return UDR0;
}

void Write_USART(uint8_t data)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);

	UDR0 = data;
}

void read_another_0x20_and_write_0x14()
{
	uint8_t data = Read_USART();
	if (data == 0x20)
	{
		Write_USART(0x14);
	}
	else
	{
		Configure_Watchdog_Timer(_BV(WDE));
		while (1) ;
	}
}

void Read_N_Characters(uint8_t count)
{
	while (count)
	{
		Read_USART();
		count -= 1;
	}
}

#define boot_page_erase_small(address)        \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),        \
          "r" ((uint8_t)(__BOOT_PAGE_ERASE)),    \
          "z" ((uint16_t)(address))              \
    );                                           \
}))

uint8_t* ram_buffer = (uint8_t*) RAMSTART;

void __attribute__ ((used)) _Noreturn __attribute__ ((section(".text.my_bootloader"))) main(void)
{
	asm volatile ("eor r1, r1");
	uint8_t mcusr = MCUSR;
	uint16_t cursor;
	MCUSR = 0x00;

	if (mcusr & _BV(EXTRF))
	{
		Init_UART();
		Configure_Watchdog_Timer(_BV(WDE) | _BV(WDP2) | _BV(WDP1));
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
				read_another_0x20_and_write_0x14();
			}
			else if (usart_read_0 == 0x45)
			{
				Read_N_Characters(0x05);
				read_another_0x20_and_write_0x14();
			}
			else if (usart_read_0 == 0x55)
			{
				cursor = (uint16_t) Read_USART() | ((uint16_t) Read_USART() << 8);
				cursor *= 2;
				read_another_0x20_and_write_0x14();
			}
			else if (usart_read_0 == 0x56)
			{
				Read_N_Characters(0x04);
				read_another_0x20_and_write_0x14();
				Write_USART(0x00);
			}
			else if (usart_read_0 == 0x64)
			{
				Read_USART();
				uint8_t usart_read_2 = Read_USART();
				Read_USART();

				boot_page_erase_small(cursor);
				for (uint8_t i = 0; i < usart_read_2; i++)
				{
					ram_buffer[i] = Read_USART();
				}
				read_another_0x20_and_write_0x14();
				boot_spm_busy_wait();
				
				for (uint8_t i = 0; i < SPM_PAGESIZE; i += 2)
				{
					uint16_t data = (uint16_t) ram_buffer[i] | ((uint16_t) ram_buffer[i + 1] << 8);
					boot_page_fill(cursor + i, data);
				}
				boot_page_write(cursor);
				boot_spm_busy_wait();
				boot_rww_enable();
			}
			else if (usart_read_0 == 0x74)
			{
				Read_USART();
				uint8_t usart_read_2 = Read_USART();
				Read_USART();
				read_another_0x20_and_write_0x14();

				do {
					Write_USART(pgm_read_byte_near(cursor++));
					usart_read_2--;
				} while (0 != usart_read_2);
			}
			else if (usart_read_0 == 0x75)
			{
				read_another_0x20_and_write_0x14();
				Write_USART(0x1E);
				Write_USART(0x95);
				Write_USART(0x0F);
			}
			else if (usart_read_0 == 0x51)
			{
				Configure_Watchdog_Timer(0x08);
				read_another_0x20_and_write_0x14();
			}
			else
			{
				read_another_0x20_and_write_0x14();
			}

			Write_USART(0x10);
		}
	}
	else
	{
		Go_To_Application_Start();
	}
}
