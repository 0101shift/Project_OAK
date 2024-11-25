/**********************************************************************************************************
  Simple AVR sketch demonstrate the usage of UP/DWN/PWR buttons on OAK Main Board as part of "Update Time"
  Once power-on, the device goes to pwr-down mode (default). When PWR button is pressed, based on the 
  duration, specific set of actions are performed. If button press short (50ms), the device lights up the
  LEDs (Time Indication) and goes back to sleep. If button press long (1000ms), the device wakes up from 
  pwr-down mode and stays in active state. This allows user to update Time by pressing UP & DWN button to 
  adjust Minute & Hour time respectively. Once updated time, the device can put back to sleep by pressing 
  short PWR button.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions 
**********************************************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "OakLedMatrix.h"

#define PWR_BUTTON_PIN PD2
#define UP_BUTTON_PIN PD4
#define DWN_BUTTON_PIN PD5
#define SHORT_PRESS_DURATION 50   // Duration in milliseconds
#define LONG_PRESS_DURATION 1000  // Duration in milliseconds

volatile uint8_t buttonPressed = 0;   // Interrupt flag
volatile uint16_t pressDuration = 0;  // To measure button press duration
volatile uint8_t stayAwake = 0;       // Flag to keep MCU awake

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

  // Configure INT0 to trigger on falling edge
  EICRA |= (1 << ISC01);  // ISC01 = 1, ISC00 = 0: Falling edge
  EICRA &= ~(1 << ISC00);

  // Enable INT0 interrupt
  EIMSK |= (1 << INT0);
}

void enter_power_down_mode(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sei();                               // Enable global interrupts
  sleep_cpu();                         // Enter sleep mode
  sleep_disable();                     // Disable sleep mode on wake-up
}

ISR(INT0_vect)
{
  buttonPressed = 1;  // Flag to handle the button press in the main loop
}

int main(void)
{
  setup();
  initMatrix();
  sei(); // Enable global interrupts

  while (1) {
    if (buttonPressed) {
      _delay_ms(50);  // Basic debounce delay
      buttonPressed = 0;

      // Measure press duration
      pressDuration = 0;
      while (!(PIND & (1 << PWR_BUTTON_PIN))) {
        _delay_ms(10);  // Increment duration in 10ms steps
        pressDuration += 10;
        if (pressDuration >= LONG_PRESS_DURATION) {
          break;  // Stop counting if long press is detected
        }
      }

      if (pressDuration >= LONG_PRESS_DURATION) {
        activateLedMatrixAll();
        _delay_ms(50);
        deactivateLedMatrix();
        stayAwake = 1;  // Set stayAwake, preventing sleep
      } else if (pressDuration >= SHORT_PRESS_DURATION) {
        ledMatrixBlink();
        stayAwake = 0;  // Allow sleep
      }
    }
    if (!stayAwake) {
      // Enter sleep mode if stayAwake is not set
      enter_power_down_mode();
    } else {
      navigateBtn();
    }
  }
}

void navigateBtn()
{
  uint8_t up_button_state = 0;
  uint8_t dwn_button_state = 0;
  uint8_t last_button_state = 1;  // Assuming button is not pressed at startup

  // Read the current state of the button
  up_button_state = PIND & (1 << UP_BUTTON_PIN);
  dwn_button_state = PIND & (1 << DWN_BUTTON_PIN);

  // Check if button was pressed (low state)
  if ((up_button_state == 0 && last_button_state != 0) || (dwn_button_state == 0 && last_button_state != 0))
  {
    // Debounce delay
    _delay_ms(50);

    // Check again to confirm the button is still pressed
    if ((PIND & (1 << UP_BUTTON_PIN)) == 0)
    {
      if (mn < 24) {
        mn++;
      }
      else {
        mn = 0;
      }
    }

    if ((PIND & (1 << DWN_BUTTON_PIN)) == 0)
    {
      if (hr < 12) {
        hr++;
      }
      else {
        hr = 0;
      }
    }
  }

  LedClockMinuteTime(mn);
  LedClockHourTime(hr);

  // Update the last button state
  last_button_state = up_button_state;
  last_button_state = dwn_button_state;
}

void ledMatrixBlink()
{
  for (int i = 0; i < 10; i++)
  {
    LedClockMinuteTime(mn);
    _delay_ms(5);
    LedClockHourTime(hr);
    _delay_ms(5);
  }
  deactivateLedMatrix();
}
