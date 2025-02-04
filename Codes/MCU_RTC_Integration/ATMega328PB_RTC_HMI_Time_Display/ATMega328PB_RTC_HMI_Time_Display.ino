/**********************************************************************************************************
  Simple AVR sketch demonstrate the interface of RTC sensor RV-8263-C7 with ATMega328PB. This code is to
  execute Hour, Minute & MI functions of the RTC sensor and outputs the data using on-board LEDs (visulization).
  Post power on, MCU goes to sleep and wakes up on interrupt generated either by the RTC sensor (every minute)
  or with the button press (PWR button). post wakeup, MCU reads the RTC time data and sets the on-board LEDs 
  accordingly and goes back to sleep.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions
  Sketch uses "RV-8263-C7" lib which takes care of interface between MCU and RV-8263-C7 RTC sensor

  |Register|         |Function|      |Bit7|  |Bit6|  |Bit5|  |Bit4|  |Bit3|  |Bit2|  |Bit1|  |Bit0|
  |                                                                                               |
  |  01h   |         |Control2|      |AIE |  | AF |  | MI |  |HMI |  | TF |  | FD|   | FD |  | FD |
  |  04h   |         |Seconds|       | OS |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  05h   |         |minutes|       | X  |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  06h   |          |Hours|        | X  |  | X  |  |AMPM|  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  07h   |          |Date|         | X  |  | X  |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  08h   |         |Weekday|       | X  |  | X  |  | X  |  | X  |  | X  |  | 4 |   | 2 |   | 1  |
  |  09h   |          |Month|        | X  |  | X  |  | X  |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  0Ah   |          |Year|         | 80 |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  11h   |       |Timer Mode|      | X  |  | X  |  | X  |  | TD |  | TD |  |TE |   |TIE|  |TI_TP|
**********************************************************************************************************/

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <RV-8263-C7.h>
#include <OakLedMatrix.h>
#include <math.h>

#define HMI_INTERRUPT_PIN PD3   // RTC interrupt (INT1)
#define BTN_INTERRUPT_PIN PD2   // Push button interrupt (INT0)

// Interrupt flag to indicate wake-up event
volatile bool wakeUpFlag = false;

void setup() {
  initMatrix();
  initRTC();
  _delay_ms(1000);

  // Configure RTC for Half-Minute Interrupt (HMI)
  writeRegister(0x01, 0b00100000); // Enable periodic interrupt
  writeRegister(0x11, 0b00011001); // Set periodic interrupt to Half-Minute

  // Configure PD3 (INT1) for RTC interrupt (falling edge)
  DDRD &= ~(1 << HMI_INTERRUPT_PIN); // Set PD3 as input
  PORTD |= (1 << HMI_INTERRUPT_PIN); // Enable pull-up resistor on PD3
  EICRA |= (1 << ISC11); // Falling edge triggers INT1
  EICRA &= ~(1 << ISC10);
  EIMSK |= (1 << INT1);  // Enable INT1 interrupt

  // Configure PD2 (INT0) for push-button wake-up (falling edge)
  DDRD &= ~(1 << BTN_INTERRUPT_PIN); // Set PD2 as input
  PORTD |= (1 << BTN_INTERRUPT_PIN); // Enable pull-up resistor on PD3
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  EIMSK |= (1 << INT0);  // Enable INT0 interrupt

  sei(); // Enable global interrupts
}

// Interrupt Service Routine (ISR) for RTC wake-up on PD3 (INT1)
ISR(INT1_vect) {
  wakeUpFlag = true;
}

// Interrupt Service Routine (ISR) for push-button wake-up on PD2 (INT0)
ISR(INT0_vect) {
  wakeUpFlag = true;
}

void loop() {
  if (!wakeUpFlag) {
    enterSleepMode();  // Put MCU to sleep
  } else {
    wakeUpFlag = false;  // Reset wake-up flag
    displayTime();       // Display RTC time on LED matrix
  }
}

// Function to enter power-down sleep mode
void enterSleepMode() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Power-down mode
  sleep_enable(); // Enable sleep mode
  sleep_cpu(); // Enter sleep mode (wait for interrupt)
  sleep_disable(); // Disable sleep after waking up
}

// Function to get RTC time and display it using LED matrix
void displayTime() {
  uint8_t hours, minutes, seconds, date, day, month, year;
  const char period[3];

  getTime(hours, minutes, seconds, date, day, month, year, period);

  // Convert minutes to corresponding LED index (2.5 min per LED)
  uint8_t minuteMap = round(minutes / 2.5);

  // Show hour and minute time for 1 second
  uint16_t displayDuration = 500 / 10;  // 100ms per toggle for 0.5 second

  for (uint16_t i = 0; i < displayDuration; i++) {
    LedClockHourTime(hours);
    _delay_ms(5);
    LedClockMinuteTime(minuteMap);
    _delay_ms(5);
  }

  deactivateLedMatrix(); // Turn off LEDs
}
