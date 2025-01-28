/* This library is a custom built for ProjectOak design. This library doesn't cover entire 
functions of the RV-8263-C7_H RTC sensor. Also, the library is not mature enough to confirm 
data accuracy. The library keeps updating once there is need to utilize other RTC functions
in upcoming revisions.
*/

#ifndef RV-8263-C7_H
#define RV-8263-C7_H

#include <Wire.h>

#define RTC_ADDRESS 0x51

// Masking values for RTC registers
#define MASK_SECONDS 0x7F
#define MASK_MINUTES 0xFF
#define MASK_HOURS   0x1F
#define MASK_DATE    0x3F
#define MASK_DAY     0x07
#define MASK_MONTH   0x1F
#define MASK_YEAR    0xFF

// Function to initialize the RTC
void initRTC();

// Function to write a value to a specific RTC register
void writeRegister(uint8_t reg, uint8_t value);

// Function to read a value from a specific RTC register
uint8_t readRegister(uint8_t reg);

// Function to get the current time and date from RTC
void getTime(uint8_t &hours, uint8_t &minutes, uint8_t &seconds, 
             uint8_t &date, uint8_t &day, uint8_t &month, uint8_t &year, char* period);

// Function to update the RTC time and date
void updateTime(uint8_t hours_new, uint8_t minutes_new, uint8_t seconds_new, 
                uint8_t date_new, uint8_t day_new, uint8_t month_new, uint8_t year_new, char* period_new);

#endif // RV-8263-C7_H