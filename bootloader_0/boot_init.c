#include <avr/io.h>
#include <avr/boot.h>

void BOOTLOADER_SECTION Go_To_Application_Start(void);
void BOOTLOADER_SECTION Init_Timer1(void);

void BOOTLOADER_SECTION __attribute__ ((used)) my_bootloader(void)
{
	if (MCUSR & (1 << EXTRF))
	{
		MCUSR = 0x00;
		Init_Timer1();
	}
	else
	{
		MCUSR = 0x00;
		Go_To_Application_Start();
	}
}
