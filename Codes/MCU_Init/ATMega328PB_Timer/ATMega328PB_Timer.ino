/*********************************************************
  This sketch makes the LED to toggle once every minute.
  This sketch uses internal 8MHz oscillator.
  It uses Timer0 or Timer0B, and divide the clock frequncy by 1024.
 ********************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init(void)
{
  // Set Timer1 in CTC mode
  TCCR1B |= (1 << WGM12);

  // Set the prescaler to 1024 (8 MHz / 1024 = 7812.5 Hz)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Set the compare value for 1 second
  OCR1A = 7812;  // Compare value for 1 second

  // Enable the Timer1 compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Initialize the counter
  TCNT1 = 0;

  // Enable global interrupts
  sei();
}

void togglePin(volatile uint8_t *port, uint8_t pin)
{
  *port ^= (1 << pin);  // XOR the pin with 1 to toggle it
}

ISR(TIMER1_COMPA_vect)
{
  static uint16_t seconds = 0;

  // Increment the seconds counter
  seconds++;

  if (seconds >= 60)
  {
    // 1 minute has passed
    togglePin(&PORTB, PB1);
    togglePin(&PORTC, PC3);
    togglePin(&PORTD, PD0);
    togglePin(&PORTD, PD1);
    togglePin(&PORTD, PD6);
    togglePin(&PORTD, PD7);
    togglePin(&PORTE, PE1);
    seconds = 0;          // Reset the counter
  }
}

int main (void)
{
  DDRB |= _BV(PB1);  // Set PB0 as output, ignore the rest
  DDRC |= _BV(PC3);
  DDRD |= _BV(PD0);
  DDRD |= _BV(PD1);
  DDRD |= _BV(PD6);
  DDRD |= _BV(PD7);
  DDRE |= _BV(PE3);

  timer1_init();

  while (1)
  {
    
  }
  return 0;
}
