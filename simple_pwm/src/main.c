#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

int main(void)
{
  // set PB5 LED as output
  DDRB |= _BV(PORTB5);

  // enable timer ctc
  TCCR0A |= _BV(WGM01);

  // set output compare to 12
  OCR0A = 12;

  // set prescaler to 64
  TCCR0B = _BV(CS01) | _BV(CS00);

  // interrupt every 48 microseconds

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
  static uint16_t x = 0;

  x++;
  if (1100 == x)
  {
    x = 0;
    PORTB |= _BV(PORTB5);
  }
  else if (1 == x)
  {
    PORTB &= ~_BV(PORTB5);
  }
}