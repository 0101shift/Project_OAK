/*********************************************************************
  Simple AVR sketch to blink Hour & Minute LEDs in a random loop
  For WATCH LEDs mapping, check the Project_OAK_MCU_Pinouts.xlsx excel
**********************************************************************/

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
  volatile uint8_t *port;
  uint8_t pin;
} led;

led leds[] = {
  {&PORTB, PB0}, {&PORTB, PB1}, {&PORTB, PB2},
  {&PORTC, PC0}, {&PORTC, PC1}, {&PORTC, PC2},
  {&PORTC, PC3}, {&PORTD, PD0}, {&PORTD, PD1},
  {&PORTD, PD6}, {&PORTD, PD7}, {&PORTE, PE3}
};

uint8_t ledcount = sizeof(leds) / sizeof(leds[0]);

void setup()
{
  for (uint8_t i = 0; i < ledcount; i++)
  {
    if (leds[i].port == &PORTB)
    {
      DDRB |= (1 << leds[i].pin);
    }
    else if (leds[i].port == &PORTC)
    {
      DDRC |= (1 << leds[i].pin);
    }
    else if (leds[i].port == &PORTD)
    {
      DDRD |= (1 << leds[i].pin);
    }
    else if (leds[i].port == &PORTE)
    {
      DDRE |= (1 << leds[i].pin);
    }
  }
}

int main (void)
{
  setup();

  while (1) {
    ledblink(100);
  }
  return 0;
}

void ledblink (uint16_t delaytime)
{
  for (uint8_t i = 0; i < ledcount / 2; i++)
  {
    *(leds[i].port) ^= (1 << leds[i].pin);
    _delay_ms(delaytime);
    for (uint8_t j = ledcount / 2; j < ledcount; j++)
    {
      *(leds[j].port) ^= (1 << leds[j].pin);
      _delay_ms(delaytime);
    }
  }
}
