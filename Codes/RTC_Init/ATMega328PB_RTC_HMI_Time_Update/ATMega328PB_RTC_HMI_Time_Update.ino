/**********************************************************************************************************
  Simple AVR sketch demonstrate the interface of RTC sensor RV-8263-C7 with ATMega328PB. This code is to
  execute Hour, Minute & Seconds, date, day, month & year functions of the RTC sensor along with HMI 
  function. Post start-up, MCU straightaway goes to sleep till external wake-up event is triggered from 
  the RTC. Since RTC is configured to HMI, it provides an interrupt every 30s. With the interrupt, MCU 
  wakes up from sleep, reads the RTC time, send it out through serial interface and goes bacl to sleep. 
  The LEDs on the main baord blinks for 100ms on every successful data sent out through serial interface.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions

  |Register|         |Function|      |Bit7|  |Bit6|  |Bit5|  |Bit4|  |Bit3|  |Bit2|  |Bit1|  |Bit0|
  |                                                                                               |
  |  00h   |         |Control1|      |Test|  | SR |  |STOP|  | SR |  | SR |  |CIE|   |12_24| | CAP|
  |  01h   |         |Control2|      |AIE|   | AF |  | MI |  |HMI |  | TF |  | FD|   | FD |  | FD |
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
#include <Wire.h>
#include "OakLedMatrix.h"

#define RTC_ADDRESS 0x51
#define INTERRUPT_PIN PD3

// Function to write a value to a specific RTC register
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(RTC_ADDRESS); // Start communication with RTC
  Wire.write(reg);                     // Set the register pointer
  Wire.write(value);                   // Write the value to the register
  Wire.endTransmission();              // End transmission
}

// Function to read a value from a specific RTC register in binary
uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(RTC_ADDRESS); // Start communication with RTC
  Wire.write(reg);                     // Set the register pointer
  Wire.endTransmission();              // End transmission

  Wire.requestFrom(RTC_ADDRESS, 1);    // Request 1 byte from the register
  while (Wire.available() == 0);       // Wait for the data to arrive
  return Wire.read();                  // Read and return the value
}

// Function to convert BCD to Decimal
uint8_t BCDtoDecimal(uint8_t bcdValue, uint8_t bitMask) {
  bcdValue &= bitMask;                // Mask to consider only the required bits
  return ((bcdValue >> 4) * 10) + (bcdValue & 0x0F); // Convert BCD to decimal
}

void setup() {
  Wire.begin();             // Initialize I2C
  Serial.begin(9600);       // Initialize Serial Communication

  initMatrix();             // Initialize OakLedMatrix

  writeRegister(0x00, 0b00000010); // 12 hour mode
  writeRegister(0x01, 0b00010000); // HMI enable
  writeRegister(0x11, 0b00011001); // TI_TP = 1

  // Initialize external interrupt
  DDRD &= ~(1 << INTERRUPT_PIN); // Set PD3 as input
  PORTD |= (1 << INTERRUPT_PIN); // Enable pull-up resistor on PD3
  EICRA |= (1 << ISC11);         // Falling edge generates interrupt
  EIMSK |= (1 << INT1);          // Enable INT1
  UCSR0B |= (1 << TXCIE0);  // Enable TX Complete Interrupt

  sei();                         // Enable global interrupts
}

ISR(INT1_vect) {
  activateLedMatrixAll();   // Toggle the LED
  _delay_ms(100);
  deactivateLedMatrix();
}

void loop() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sleep_cpu();                         // Enter sleep mode

  sleep_disable();                     // Disable sleep mode on wake-up
  Serial.println("System awake.");
  getTime();
}

void getTime() {
  uint8_t seconds, minutes, hours, Date, Day, Month, Year, control1;
  uint8_t secondsDec, minutesDec, hoursDec, dateDec, dayDec, monthDec, yearDec;

  // Read individual RTC registers in binary
  control1 = readRegister(0x00);
  seconds = readRegister(0x04); // Read seconds register
  minutes = readRegister(0x05); // Read minutes register
  hours = readRegister(0x06);   // Read hours register
  Date = readRegister(0x07);    // Read Date register
  Day = readRegister(0x08);     // Read Day register
  Month = readRegister(0x09);   // Read Month register
  Year = readRegister(0x0A);    // Read Year register

  // Convert BCD to Decimal considering only the valid bits
  secondsDec = BCDtoDecimal(seconds, 0x7F); // Mask 7 bits for seconds
  minutesDec = BCDtoDecimal(minutes, 0xFF); // Full 8 bits for minutes
  hoursDec = BCDtoDecimal(hours, 0x1F);     // Mask 5 bits for hours
  dateDec = BCDtoDecimal(Date, 0x3F);       // Mask 6 bits for date
  dayDec = BCDtoDecimal(Day, 0x07);         // Mask 3 bits for day
  monthDec = BCDtoDecimal(Month, 0x1F);     // Mask 5 bits for month
  yearDec = BCDtoDecimal(Year, 0xFF);       // Full 8 bits for year

  Serial.println("------------------------------------------------------");
  Serial.println("System awake!!!");

  Serial.print("control1: ");
  Serial.println(control1, BIN);
  Serial.print("seconds: ");
  Serial.println(seconds, BIN);

  // Print time to Serial Monitor
  Serial.print("Current Time: ");
  if (hoursDec < 10) Serial.print('0');
  Serial.print(hoursDec);
  Serial.print(":");
  if (minutesDec < 10) Serial.print('0');
  Serial.print(minutesDec);
  Serial.print(":");
  if (secondsDec < 10) Serial.print('0');
  Serial.println(secondsDec);

  Serial.print("Current Date: ");
  if (dateDec < 10) Serial.print('0');
  Serial.println(dateDec);
  Serial.print("Current Day: ");
  if (dayDec < 10) Serial.print('0');
  Serial.println(dayDec);
  Serial.print("Current Month: ");
  if (monthDec < 10) Serial.print('0');
  Serial.println(monthDec);
  Serial.print("Current Year: ");
  if (yearDec < 10) Serial.print('0');
  Serial.println(yearDec);

  // Wait for TX complete flag to ensure all data is sent
  while (!(UCSR0A & (1 << TXC0)));
}
