#include <avr/io.h>
#include <util/delay.h>

unsigned char digit_segs[16] = {
    0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,
    0x7f,0x73,0x77,0x1f,0x4e,0x3d,0x4f,0x47 };

void display_digit(unsigned char);

#define C1BIT         (1 << PC1)
#define C0BIT         (1 << PC0)
#define SEG_DATA_B     0x03     // Bits in Port B for LED display
#define SEG_DATA_D     0xfc     // Bits in Port D for LED display

int main(void) {
    uint16_t cnt = 0;

    DDRB |= SEG_DATA_B;         // Set PORTB bits 0-1 for output
    DDRD |= SEG_DATA_D;         // Set PORTD bits 2-6 for output
    DDRC |= (C0BIT | C1BIT);         // Set PORTD bits 2-6 for output

    while(1) {                  // Loop forever
		char u = 80;
		while (u--)
		{
			PORTC |= C1BIT;
			PORTC |= C0BIT;
        	_delay_ms(1);         // wait 1000 ms
        	display_digit((cnt & 0xF0) >> 0x04);
        	_delay_ms(1);         // wait 1000 ms
			PORTC &= ~C0BIT;
        	_delay_ms(5);         // wait 1000 ms

			PORTC |= C1BIT;
			PORTC |= C0BIT;
        	_delay_ms(1);         // wait 1000 ms
        	display_digit(cnt & 0x0F);
        	_delay_ms(1);         // wait 1000 ms
			PORTC &= ~C1BIT;
        	_delay_ms(5);         // wait 1000 ms
		}

        if (++cnt > 255)     // and we count up in hex
        	cnt = 0;
    }
    return 0;   /* never reached */
}

void display_digit(unsigned char digit)
{
    unsigned char x;
    // x = digit_segs[digit] ^ 0xff;  // invert bits (active low outputs)
    x = digit_segs[digit];  // invert bits (active low outputs)
    PORTB |= x & SEG_DATA_B;    // put low two bits in B
    PORTB &= (x | ~SEG_DATA_B);
    PORTD |= x & SEG_DATA_D;    // put high five bits in D
    PORTD &= (x | ~SEG_DATA_D);
}

