/*********************************************************************
  Simple AVR sketch to blink Hour & Minute LEDs
  For WATCH LEDs mapping, check the Project_OAK_MCU_Pinouts.xlsx excel
**********************************************************************/

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  /***********************************************************
    Way to set a pin as output and ignore the rest of the pins.
  ************************************************************/
  //  DDRB |= _BV(PB0);  // Set PB0 as output, ignore the rest
  //  DDRB |= _BV(PB1);
  DDRB |= _BV(PB2);
  DDRC |= _BV(PC3);
  //  DDRD |= _BV(PD0);
  DDRD |= _BV(PD1);
  //  DDRD |= _BV(PD6);
  //  DDRD |= _BV(PD7);
  DDRE |= _BV(PE3);

  /************************************************************
    Keep all the LEDs in OFF state (default state)
  *************************************************************/
  //  PORTB &= ~(1 << PB0);
  //  PORTB &= ~(1 << PB1);
  PORTB &= ~(1 << PB2);
  PORTC |= (1 << PC3);
  //  PORTD |= (1 << PD0);
  PORTD |= (1 << PD1);
  //  PORTD |= (1 << PD6);
  //  PORTD |= (1 << PD7);
  PORTE |= (1 << PE3);

  while (1)
  {
    /*******************************************************
      Toggle the LED pins and ignore the rest of the pins.
    ********************************************************/
    //    PORTB ^= (1 << PB0);
    //    PORTB ^= (1 << PB1);
    PORTB ^= (1 << PB2);
    PORTC ^= (1 << PC3);
    //    PORTD ^= (1 << PD0);
    PORTD ^= (1 << PD1);
    //    PORTD ^= (1 << PD6);
    //    PORTD ^= (1 << PD7);
    PORTE ^= (1 << PE3);
    _delay_ms(1000);
  }

  return 0;
}


// Method to set a pin HIGH
void SetPinHigh(volatile byte *port, byte pin)
{
  *port |= (1 << pin); // The number '1' are shifted left 'pin' times
}

// Method to set pin LOW
void SetPinLow(volatile byte *port, byte pin)
{
  *port &= ~(1 << pin); // The number '1' are shifted left 'pin' times
}
