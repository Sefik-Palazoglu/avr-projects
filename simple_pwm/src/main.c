#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

uint16_t x = 0;

int main(void)
{
  // set PB5 LED as output
  DDRB |= _BV(PORTB5);

  // enable timer ctc
  TCCR0A |= _BV(WGM01);

  // set output compare
  OCR0A = 125;

  // set prescaler to 1024
  TCCR0B = _BV(CS02) | _BV(CS00);

  // enable interrupts
  sei();
  // enable timer 0 interrupt OCA interrupts
  TIMSK0 = _BV(OCIE0A);

  while (1)
  {
    ;
  }
}

ISR(TIMER0_COMPA_vect)
{
  x++;
  if (125 == x)
  {
    x = 0;
    PORTB |= _BV(PORTB5);
  }
  else if (100 == x)
  {
    PORTB &= ~_BV(PORTB5);
  }
}