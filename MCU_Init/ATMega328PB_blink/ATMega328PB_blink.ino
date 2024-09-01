/***************************************************
 Simple AVR sketch to blink an LED (or similar)
***************************************************/ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{       
  /************************************************ 
   A few different ways to set a pin as output and 
   ignore the rest of the pins. Pick your favorite!
  *************************************************/
  //DDRB |= 0x20;     // XXXXXXXX | 00100000 = XX1XXXXX
  DDRB |= _BV(PB1);  // Set PB0 as output, ignore the rest
  DDRC |= _BV(PC3);
  DDRD |= _BV(PD0);
  DDRD |= _BV(PD1);
  DDRD |= _BV(PD6);
  DDRD |= _BV(PD7);
  DDRE |= _BV(PE3);
  //DDRB |= (1 << PB5); // Shift the number '1' left 'PB5' times (PB0 = 6)

  /************************************************ 
   A few different ways to set a pin as input and 
   ignore the rest of the pins.
  *************************************************/
  //DDRB &= ~0x20; //00100000 -> 11011111 & XXXXXXXX = XX0XXXXX
  //DDRD &= ~_BV(PD6); 
  //DDRC &= ~(1 << PC3);
    
  // Infinite loop
  while(1)
  {
    /*********************************************** 
     A few different ways to set a pin high and 
     ignore the rest of the pins. 
    ************************************************/
    PORTB |= (1 << PB1);
    PORTC &= ~(1 << PC3);
    PORTD &= ~(1 << PD0);
    PORTD &= ~(1 << PD1);
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    PORTE &= ~(1 << PE3);
    //SetPinHigh(&PORTB, 5); 
    _delay_ms(1000);
    
    /*********************************************** 
     A few different ways to set a pin low and 
     ignore the rest of the pins.
    ************************************************/
    PORTB &= ~(1 << PB1); 
    PORTC |= (1 << PC3);
    PORTD |= (1 << PD0);
    PORTD |= (1 << PD1);
    PORTD |= (1 << PD6);
    PORTD |= (1 << PD7);
    PORTE |= (1 << PE3);
    //SetPinLow(&PORTB, 5);
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
