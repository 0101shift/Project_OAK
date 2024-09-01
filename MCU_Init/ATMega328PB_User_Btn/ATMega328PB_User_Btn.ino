#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD4

void setup(void)
{
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

  // Set BUTTON_PIN (PD4) as input
  DDRD &= ~(1 << BUTTON_PIN);

  // Enable pull-up resistor on PD4 (if needed)
  PORTD |= (1 << BUTTON_PIN);
}

int main(void)
{
  setup();

  uint8_t button_state = 0;
  uint8_t last_button_state = 1;  // Assuming button is not pressed at startup

  while (1)
  {
    // Read the current state of the button
    button_state = PIND & (1 << BUTTON_PIN);

    // Check if button was pressed (low state)
    if (button_state == 0 && last_button_state != 0)
    {
      // Debounce delay
      _delay_ms(50);

      // Check again to confirm the button is still pressed
      if ((PIND & (1 << BUTTON_PIN)) == 0)
      {
        // Toggle the LED
        PORTB ^= (1 << PB1);
        PORTC ^= (1 << PC3);
        PORTD ^= (1 << PD0);
        PORTD ^= (1 << PD1);
        PORTD ^= (1 << PD6);
        PORTD ^= (1 << PD7);
        PORTE ^= (1 << PE3);
      }
    }

    // Update the last button state
    last_button_state = button_state;
  }

  return 0;
}
