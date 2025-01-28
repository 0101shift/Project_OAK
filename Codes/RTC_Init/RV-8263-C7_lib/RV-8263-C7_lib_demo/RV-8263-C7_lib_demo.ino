/**********************************************************************************************************
  Simple AVR sketch demonstrate the RV-8263-C7 lib. The sketch updates the RTC time data with the manual 
  data entered in setup and fetches the updated RTC data from RTC in loop

  "RV-8263-C7" library takes care of mapping RTC registers and I2C comms with RTC sensor 
**********************************************************************************************************/

#include <RV-8263-C7.h>
#include <OakLedMatrix.h>
#include <util/delay.h>

void setup()
{
  Serial.begin(9600);
  initMatrix();
  initRTC();
  _delay_ms(1000);

  // Update RTC with specific values
  uint8_t hours_new = 6;
  uint8_t minutes_new = 40;
  uint8_t seconds_new = 30;
  uint8_t date_new = 23;
  uint8_t day_new = 4; // Thursday
  uint8_t month_new = 1; // January
  uint8_t year_new = 25; // Last two digits of the year 2025
  const char period_new[3] = "AM";
  
  // updateTime format: (hours, minutes, second, date, day, month, year, "AM"/"PM")
  //updateTime(8, 17, 30, 22, 3, 1, 25, "AM");
  
  updateTime(hours_new, minutes_new, seconds_new, date_new, day_new, month_new, year_new, period_new);
  Serial.println("RTC updated successfully!");
  _delay_ms(2500);
}

void loop()
{
  const char period[3];
  uint8_t hours, minutes, seconds, date, day, month, year;

  getTime(hours, minutes, seconds, date, day, month, year, period);

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
  Serial.println(readRegister(0x06),BIN);

  Serial.print("Current Date: ");
  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.println(year);

  _delay_ms(5000);
  activateLedMatrixAll();   // Toggle the LED
  _delay_ms(100);
  deactivateLedMatrix();
  Serial.println("---------------------------------------");
}
