/**********************************************************************************************************
  Simple AVR sketch demonstrate the interface of RTC sensor RV-8263-C7 with ATMega328PB. This code is to
  execute HMI (Half Minute Interrupt) / MI (Minute Interrupt) functions of the RTC sensor. Up on interrupt,
  RTC sensors sends interrupt pulse to MCU on PD3 pin. This interrupt wakes the MCU up and blinks all
  the LEDs on the main baord for 100ms and then goes back to sleep.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions

  |Register|         |Function|      |Bit7|  |Bit6|  |Bit5|  |Bit4|  |Bit3|  |Bit2|  |Bit1|  |Bit0|
  |                                                                                               |
  |  01h   |         |Control2|      |AIE|   | AF |  | MI |  |HMI |  | TF |  | FD |  | FD |  | FD |
  |  11h   |        |Timer Mode|     | X |   | X  |  | X  |  | TD |  | TD |  | TE |  | TIE| |TI_TP|
**********************************************************************************************************/

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <Wire.h>
#include "OakLedMatrix.h"

#define RTC_ADDRESS 0x51
#define INTERRUPT_PIN PD3
#define REGISTER_ADDRESS_CTRL2 0x01
#define REGISTER_ADDRESS_TIM_MODE 0x11

void initRTC() {
  Wire.begin();

  // Set periodic interrupt to 1/2 minute
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(REGISTER_ADDRESS_CTRL2); // Control register
  Wire.write(0x10); // Enable 1/2 minute interrupt
  Wire.endTransmission();

  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(REGISTER_ADDRESS_TIM_MODE); // Periodic Interrupt register
  Wire.write(0x19);
  Wire.endTransmission();
}

void initInterrupt() {
  // Set PD3 as input
  DDRD &= ~(1 << INTERRUPT_PIN);

  // Enable pull-up resistor on PD3 (optional, depends on external circuit)
  PORTD |= (1 << PORTD3);

  // Enable external interrupt on INT1 (PD3)
  EICRA |= (1 << ISC11); // Falling edge generates interrupt
  EICRA &= ~(1 << ISC10);
  EIMSK |= (1 << INT1);  // Enable INT1
}

void setup() {
  // Initialize OakLedMatrix
  initMatrix();

  // Initialize RTC and interrupt
  initRTC();
  initInterrupt();

  // Enable global interrupts
  sei();
}

ISR(INT1_vect) {
  activateLedMatrixAll(); // Toggle the LED
  _delay_ms(100);
  deactivateLedMatrix();
}

void loop()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sleep_cpu();                         // Enter sleep mode

  // MCU wakes up here after INT1 interrupt
  sleep_disable();                     // Disable sleep mode on wake-up
  initRTC();
}
