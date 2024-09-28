#include <avr/io.h>

int main(void)
{
	DDRB |= 1 << DDB5;

	while (1) 
	{
		PORTB |= 1 << PB5;
	}

    return 0;
}

