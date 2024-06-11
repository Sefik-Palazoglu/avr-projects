#include <avr/io.h>

int main(void)
{
    DDRC |= (1 << DDC0);
    PORTC |= (1 << PC1);

    while (1) 
	{
        if (PINC & (1 << PC1))
            PORTC &= ~(1 << PC0);
        else
            PORTC |= 1 << PC0;
	}

    return 0;
}

