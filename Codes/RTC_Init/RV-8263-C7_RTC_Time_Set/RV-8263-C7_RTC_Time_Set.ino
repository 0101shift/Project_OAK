/**********************************************************************************************************
  Simple AVR sketch demonstrate the interface of RTC sensor RV-8263-C7 with ATMega328PB. This code is to
  execute Hour, Minute & Seconds, date, day, month & year functions of the RTC sensor. During the start-up,
  the intended time values are updated to their respective registers. Post that, RTC keeps updating the
  registers and sends the data to the MCU at 1s interval. The data from MCU is then sent out through serial
  interface. The LEDs on the main baord blinks for 100ms on every successful data sent out through serial
  interface.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions

  |Register|         |Function|      |Bit7|  |Bit6|  |Bit5|  |Bit4|  |Bit3|  |Bit2|  |Bit1|  |Bit0|
  |                                                                                               |
  |  00h   |         |Control1|      |Test|  | SR |  |STOP|  | SR |  | SR |  |CIE|   |12_24| | CAP|
  |  04h   |         |Seconds|       | OS |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  05h   |         |minutes|       | X  |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  06h   |          |Hours|        | X  |  | X  |  |AMPM|  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  07h   |          |Date|         | X  |  | X  |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  08h   |         |Weekday|       | X  |  | X  |  | X  |  | X  |  | X  |  | 4 |   | 2 |   | 1  |
  |  09h   |          |Month|        | X  |  | X  |  | X  |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  0Ah   |          |Year|         | 80 |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
**********************************************************************************************************/

#include <Wire.h>
#include "OakLedMatrix.h"
#define RTC_ADDRESS 0x51  // I2C address of the RTC

// Function to write a value to a specific RTC register in binary
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

// ISR for Transmit Complete Interrupt
ISR(USART_TX_vect) {
  activateLedMatrixAll(); // Toggle the LED
  _delay_ms(100);
  deactivateLedMatrix();
}

void setup() {
  Wire.begin();             // Initialize I2C
  Serial.begin(9600);       // Initialize Serial Communication

  // Initialize OakLedMatrix
  initMatrix();

  // Set RTC registers with binary values
  writeRegister(0x00, 0b00000010); // 12 hour mode

  // Update the Hour, Minute & Seconds value once
    writeRegister(0x04, 0b10110000); // Seconds: 30 (binary)
    writeRegister(0x05, 0b00110000); // Minutes: 30 (binary)
    writeRegister(0x06, 0b00101000); // Hours: 8 (binary, 8 PM)
    writeRegister(0x07, 0b00011001); // Date: 19
    writeRegister(0x08, 0b00000111); // Weekday: 6
    writeRegister(0x09, 0b00000001); // Month: 1
    writeRegister(0x0A, 0b00100101); // Year: 25

  //Serial.println("RTC registers set individually in binary.");

  // Enable TX Complete Interrupt
  UCSR0B |= (1 << TXCIE0);

  // Enable global interrupts
  sei();
}

void loop() {
  uint8_t seconds, minutes, hours, Date, Day, Month, Year;
  uint8_t secondsDec, minutesDec, hoursDec, dateDec, dayDec, monthDec, yearDec;

  // Read individual RTC registers in binary
  seconds = readRegister(0x04); // Read seconds register
  minutes = readRegister(0x05); // Read minutes register
  hours = readRegister(0x06);   // Read hours register
  Date = readRegister(0x07);    // Read Date register
  Day = readRegister(0x08);    // Read Day register
  Month = readRegister(0x09);  // Read Month register
  Year = readRegister(0x0A);   // Read Year register

  // Convert BCD to Decimal considering only the valid bits
  secondsDec = BCDtoDecimal(seconds, 0x7F); // Mask 7 bits for seconds
  minutesDec = BCDtoDecimal(minutes, 0xFF); // Full 8 bits for minutes
  hoursDec = BCDtoDecimal(hours, 0x1F);     // Mask 5 bits for hours
  dateDec = BCDtoDecimal(Date, 0x3F);       // Mask 6 bits for hours
  dayDec = BCDtoDecimal(Day, 0x07);         // Mask 3 bits for hours
  monthDec = BCDtoDecimal(Month, 0x1F);     // Mask 5 bits for month
  yearDec = BCDtoDecimal(Year, 0xFF);       // Full 8 bits for year

  Serial.println("------------------------------------------------------");

  // Print binary data to Serial Monitor
  Serial.print("Current Time (Binary): ");
  Serial.print("Hours: ");
  Serial.print(hours, BIN);
  Serial.print(", Minutes: ");
  Serial.print(minutes, BIN);
  Serial.print(", Seconds: ");
  Serial.print(seconds, BIN);
  Serial.print(", Date: ");
  Serial.print(Date, BIN);
  Serial.print(", Day: ");
  Serial.print(Day, BIN);
  Serial.print(", Month: ");
  Serial.print(Month, BIN);
  Serial.print(", Year: ");
  Serial.println(Year, BIN);

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
  Serial.println("------------------------------------------------------");

  delay(1000);  // Wait for 1 second before reading again
}
