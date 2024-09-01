#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void setup_external_interrupt(void)
{
  // Set INT0 (PD2) as input
  DDRD &= ~(1 << DDD2);  // Clear PD2 to make it an input

  // Enable pull-up resistor on PD2 (optional, depends on external circuit)
  PORTD |= (1 << PORTD2);

  // Configure INT0 to trigger on falling edge
  EICRA |= (1 << ISC01);  // ISC01 = 1, ISC00 = 0: Falling edge
  EICRA &= ~(1 << ISC00);

  // Enable INT0 interrupt
  EIMSK |= (1 << INT0);

  // Enable global interrupts
  sei();
}

void enter_power_down_mode(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sleep_cpu();                         // Enter sleep mode

  // MCU wakes up here after INT0 interrupt
  sleep_disable();                     // Disable sleep mode on wake-up
}

ISR(INT0_vect)
{
  // INT0 ISR: Executed when INT0 pin is triggered
  // You can perform any task here after waking up
  // Toggle PB0 as an example action
  PORTB |= (1 << PB1);
  PORTC &= ~(1 << PC3);
  PORTD &= ~(1 << PD0);
  PORTD &= ~(1 << PD1);
  PORTD &= ~(1 << PD6);
  PORTD &= ~(1 << PD7);
  PORTE &= ~(1 << PE3);
  _delay_ms(100);            // Delay for 0.5 second
  PORTB &= ~(1 << PB1);
  PORTC |= (1 << PC3);
  PORTD |= (1 << PD0);
  PORTD |= (1 << PD1);
  PORTD |= (1 << PD6);
  PORTD |= (1 << PD7);
  PORTE |= (1 << PE3);
}

int main(void)
{
  // Set PB0 as output (e.g., for toggling an LED)
  DDRB |= _BV(PB1);  // Set PB0 as output, ignore the rest
  DDRC |= _BV(PC3);
  DDRD |= _BV(PD0);
  DDRD |= _BV(PD1);
  DDRD |= _BV(PD6);
  DDRD |= _BV(PD7);
  DDRE |= _BV(PE3);

  PORTB &= ~(1 << PB1);
  PORTC |= (1 << PC3);
  PORTD |= (1 << PD0);
  PORTD |= (1 << PD1);
  PORTD |= (1 << PD6);
  PORTD |= (1 << PD7);
  PORTE |= (1 << PE3);

  // Setup external interrupt on INT0
  setup_external_interrupt();

  while (1)
  {
    // Enter power-down mode
    enter_power_down_mode();

    // MCU will sleep here and wake up on INT0 interrupt
    // The ISR will handle the wake-up
  }

  return 0;
}
