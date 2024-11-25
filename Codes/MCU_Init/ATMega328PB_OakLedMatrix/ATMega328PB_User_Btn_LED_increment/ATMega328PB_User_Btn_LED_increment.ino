/**********************************************************************************************************
  Simple AVR sketch demonstrate to test UP/DWM/PWR buttons on OAK Main Board. Just light up the LEDs & move. 
  Once power-on, the device is in active. Hour & Minute LED is set to 12 & 0 respectively. Minute & Hour 
  LEDs are moved around by pressing UP & DWN button. The LEDs are cleared by pressing PWR button.
  
  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions 
**********************************************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "OakLedMatrix.h"

#define PWR_BUTTON_PIN PD2
#define UP_BUTTON_PIN PD4
#define DWN_BUTTON_PIN PD5

int hr = 1;
int mn = 1;

void setup(void)
{
  // Set BUTTON_PIN (PD2, PD4, PD5) as input
  DDRD &= ~(1 << UP_BUTTON_PIN);
  DDRD &= ~(1 << DWN_BUTTON_PIN);
  DDRD &= ~(1 << PWR_BUTTON_PIN);

  // Enable pull-up resistor on PD2, PD4, PD5 (if needed)
  PORTD |= (1 << UP_BUTTON_PIN);
  PORTD |= (1 << DWN_BUTTON_PIN);
  PORTD |= (1 << PWR_BUTTON_PIN);
}

int main(void)
{
  setup();
  initMatrix();

  uint8_t up_button_state = 0;
  uint8_t dwn_button_state = 0;
  uint8_t pwr_button_state = 0;
  uint8_t last_button_state = 1;  // Assuming button is not pressed at startup

  while (1)
  {
    // Read the current state of the button
    up_button_state = PIND & (1 << UP_BUTTON_PIN);
    dwn_button_state = PIND & (1 << DWN_BUTTON_PIN);
    pwr_button_state = PIND & (1 << PWR_BUTTON_PIN);

    // Check if button was pressed (low state)
    if ((up_button_state == 0 && last_button_state != 0) || (dwn_button_state == 0 && last_button_state != 0) || (pwr_button_state == 0 && last_button_state != 0))
    {
      // Debounce delay
      _delay_ms(50);

      // Check again to confirm the button is still pressed
      if ((PIND & (1 << UP_BUTTON_PIN)) == 0)
      {
        if (mn < 24)
        {
          mn++;
        }
        else
        {
          mn = 0;
        }
      }

      if ((PIND & (1 << DWN_BUTTON_PIN)) == 0)
      {
        if (hr < 12)
        {
          hr++;
        }
        else
        {
          hr = 0;
        }
      }

      if (((PIND & (1 << PWR_BUTTON_PIN)) == 0))
      {
        hr = 0;
        mn = 0;
        deactivateLedMatrix();
      }
    }

    LedClockMinuteTime(mn);
    LedClockHourTime(hr);

    // Update the last button state
    last_button_state = up_button_state;
    last_button_state = dwn_button_state;
    last_button_state = pwr_button_state;
  }

  return 0;
}
