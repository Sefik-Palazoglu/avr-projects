#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include "uart.h"

int main(void)
{
  init_uart();
  // set PB5 LED as output
  DDRB |= _BV(PORTB5);

  // enable timer ctc
  TCCR0A |= _BV(WGM01);

  // set output compare to 12
  OCR0A = 12;

  // set prescaler to 64
  TCCR0B = _BV(CS01) | _BV(CS00);

  // interrupt every 48 microseconds

  // activate noise canceller
  // select positive edge input capture
  // start timer with prescaler == 1
  TCCR1B = _BV(ICNC1) | _BV(ICES1) | _BV(CS11) | _BV(CS10);

  // enable interrupts
  sei();
  // enable timer 0 interrupt OCA interrupts
  TIMSK0 = _BV(OCIE0A);
  // enable timer1 input capture interrupt
  TIMSK1 = _BV(ICIE1);

  while (1)
  {
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

ISR(TIMER1_CAPT_vect)
{
  static uint8_t capture_falling = 0;
  static uint16_t capture_value = 0;
  static char sending_char[5];

  uint16_t capture_value_old = capture_value;
  capture_value = ICR1L;
  capture_value |= (ICR1H << 8);

  if (capture_falling)
  {
    // capture rising edge next
    TCCR1B |= _BV(ICES1);

    capture_falling = 0;

    uint16_t captured_pulse_width = capture_value - capture_value_old;
    utoa(captured_pulse_width, sending_char, 10);
    write_usart(sending_char[0]);
    write_usart(sending_char[1]);
    write_usart(sending_char[2]);
    write_usart(sending_char[3]);
    write_usart(sending_char[4]);
    write_usart('\r');
    write_usart('\n');
  }
  else
  {
    // capture falling edge next
    TCCR1B &= ~_BV(ICES1);
    capture_falling = 1;
  }
}