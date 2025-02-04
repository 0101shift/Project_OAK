/**********************************************************************************************************
  Simple AVR sketch demonstrate the interface of RTC sensor RV-8263-C7 with ATMega328PB. This code is to
  execute Hour & Minute functions of the RTC sensor and outputs the data using on-board LEDs (visulization).
  Post start-up, MCU reads the RTC time data and sets the on-board LEDs accordingly.

  Sketch uses "OakLedMatrix" lib which takes care of mapping LED pins to their respective Hr/Min positions
  Sketch uses "RV-8263-C7" lib which takes care of interface between MCU and RV-8263-C7 RTC sensor

  |Register|         |Function|      |Bit7|  |Bit6|  |Bit5|  |Bit4|  |Bit3|  |Bit2|  |Bit1|  |Bit0|
  |                                                                                               |
  |  04h   |         |Seconds|       | OS |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  05h   |         |minutes|       | X  |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  06h   |          |Hours|        | X  |  | X  |  |AMPM|  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  07h   |          |Date|         | X  |  | X  |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  08h   |         |Weekday|       | X  |  | X  |  | X  |  | X  |  | X  |  | 4 |   | 2 |   | 1  |
  |  09h   |          |Month|        | X  |  | X  |  | X  |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
  |  0Ah   |          |Year|         | 80 |  | 40 |  | 20 |  | 10 |  | 8  |  | 4 |   | 2 |   | 1  |
**********************************************************************************************************/

#include <avr/io.h>
#include <RV-8263-C7.h>
#include <OakLedMatrix.h>
#include <util/delay.h>
#include <math.h>

void setup() {
  //Serial.begin(9600);
  initMatrix();
  initRTC();
  _delay_ms(1000);

  //  Update RTC with specific values
  //      uint8_t hours_new = 10;
  //      uint8_t minutes_new = 50;
  //      uint8_t seconds_new = 30;
  //      uint8_t date_new = 1;
  //      uint8_t day_new = 6; // Saturday
  //      uint8_t month_new = 2; // Feburary
  //      uint8_t year_new = 25; // Last two digits of the year 2025
  //      const char period_new[3] = "PM";

  // updateTime format: (hours, minutes, second, date, day, month, year, "AM"/"PM")
  // updateTime(8, 17, 30, 22, 3, 1, 25, "AM");

  //  updateTime(hours_new, minutes_new, seconds_new, date_new, day_new, month_new, year_new, period_new);
  //  Serial.println("RTC updated successfully!");
  //  _delay_ms(2500);
}

void loop()
{
  const char period[3];
  uint8_t hours, minutes, seconds, date, day, month, year;

  getTime(hours, minutes, seconds, date, day, month, year, period);

  // Convert minutes to corresponding LED index (2.5 min per LED)
  uint8_t minuteMap = round(minutes / 2.5);

  // Use the values as needed
  Serial.print("Current Time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.print("-");
  Serial.println(period);
  Serial.print("rawhour: ");
  Serial.println(readRegister(0x06), BIN);
  Serial.print("minuteMap: ");
  Serial.println(minuteMap);

  Serial.print("Current Date: ");
  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.println(year);

  Serial.println("---------------------------------------");

  // Show both hour and minute time for 1 second
  uint16_t displayDuration = 1000 / 10;  // 100ms per toggle for 1 second

  for (uint16_t i = 0; i < displayDuration; i++) {
    LedClockHourTime(hours);   // Show hour LED
    _delay_ms(5);              // Small delay
    LedClockMinuteTime(minuteMap); // Show minute LED
    _delay_ms(5);              // Small delay
  }

  // Turn off all LEDs
  deactivateLedMatrix();

  // Wait for the next update
  _delay_ms(4000);  // Maintain a total 5s cycle
}
