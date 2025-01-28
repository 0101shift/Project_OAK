/* This library is a custom built for ProjectOak design. This library doesn't cover entire 
functions of the RV-8263-C7_H RTC sensor. Also, the library is not mature enough to confirm 
data accuracy. The library keeps updating once there is need to utilize other RTC functions
in upcoming revisions.
*/

#include "RV-8263-C7.h"

// Convert BCD to Decimal
static uint8_t BCDtoDecimal(uint8_t bcdValue, uint8_t bitMask) {
    bcdValue &= bitMask; // Apply the bit mask
    return ((bcdValue >> 4) * 10) + (bcdValue & 0x0F); // Convert to decimal
}

// Convert Decimal to BCD
static uint8_t DecimalToBCD(uint8_t decimalValue, uint8_t bitMask) {
    uint8_t bcdValue = ((decimalValue / 10) << 4) | (decimalValue % 10);
    return bcdValue & bitMask; // Mask the result before returning
}

void initRTC() {
    Wire.begin();
	
	// Check if the RTC responds
    Wire.beginTransmission(RTC_ADDRESS);
    uint8_t error = Wire.endTransmission();

    if (error != 0) {
        Serial.println("RTC not detected! Check connection.");
        while (1); // Halt execution if RTC is not detected
    } else {
        Serial.println("RTC detected and active.");
    }
	
    writeRegister(0x00, 0b00000010); // Set control register for 12-hour mode
}

void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(reg); // Set the register pointer
    Wire.write(value); // Write the value to the register
    Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(reg); // Set the register pointer
    Wire.endTransmission();

    Wire.requestFrom(RTC_ADDRESS, 1);
    while (Wire.available() == 0);
    return Wire.read(); // Return the value read
}

void getTime(uint8_t &hours, uint8_t &minutes, uint8_t &seconds, 
             uint8_t &date, uint8_t &day, uint8_t &month, uint8_t &year, char* period) {
    
    uint8_t rawseconds, rawminutes, rawhours, rawdate, rawday, rawmonth, rawyear;

    // Read individual RTC registers in binary
    rawseconds = readRegister(0x04);
    rawminutes = readRegister(0x05);
    rawhours = readRegister(0x06);
    rawdate = readRegister(0x07);
    rawday = readRegister(0x08);
    rawmonth = readRegister(0x09);
    rawyear = readRegister(0x0A);

    // Convert to Decimal
    seconds = BCDtoDecimal(rawseconds, MASK_SECONDS);
    minutes = BCDtoDecimal(rawminutes, MASK_MINUTES);
    hours = BCDtoDecimal(rawhours, MASK_HOURS & 0x1F);
    date = BCDtoDecimal(rawdate, MASK_DATE);
    day = BCDtoDecimal(rawday, MASK_DAY);
    month = BCDtoDecimal(rawmonth, MASK_MONTH);
    year = BCDtoDecimal(rawyear, MASK_YEAR);
	
	// Determine AM/PM based on bit 5 of the raw hour register
    if (hours & 0b00100000) {
        strcpy(period, "PM"); // Set the period to "PM"
    } else {
        strcpy(period, "AM"); // Set the period to "AM"
    }
}

void updateTime(uint8_t hours_new, uint8_t minutes_new, uint8_t seconds_new, 
                uint8_t date_new, uint8_t day_new, uint8_t month_new, uint8_t year_new, char* period_new) {
    
	writeRegister(0x00, 0b00100010); // Stop RTC	
	
	// Convert and apply padding
    uint8_t secondsBCD = DecimalToBCD(seconds_new, MASK_SECONDS);	// Seconds conversion
    uint8_t minutesBCD = DecimalToBCD(minutes_new, MASK_MINUTES);	// Minute conversion
    uint8_t hoursBCD = DecimalToBCD(hours_new, MASK_HOURS);			// Hour conversion

    // Check period (AM/PM) and set bit 5 accordingly
    if (strcmp(period_new, "PM") == 0) {
        hoursBCD |= 0b00100000; // Set the AM/PM bit for PM
    } else if (strcmp(period_new, "AM") == 0) {
        hoursBCD &= ~0b00100000; // Clear the AM/PM bit for AM
    } else {
        Serial.println("Invalid period input! Use 'AM' or 'PM'.");
        return; // Exit if invalid input is given
    }

    uint8_t dateBCD = DecimalToBCD(date_new, MASK_DATE);   // Date conversion
    uint8_t dayBCD = DecimalToBCD(day_new, MASK_DAY);     // Day conversion
    uint8_t monthBCD = DecimalToBCD(month_new, MASK_MONTH); // Month conversion
    uint8_t yearBCD = DecimalToBCD(year_new, MASK_YEAR);   // Year conversion

    // Write values to RTC
    writeRegister(0x04, secondsBCD);
    writeRegister(0x05, minutesBCD);
    writeRegister(0x06, hoursBCD);
    writeRegister(0x07, dateBCD);
    writeRegister(0x08, dayBCD);
    writeRegister(0x09, monthBCD);
    writeRegister(0x0A, yearBCD);

    writeRegister(0x00, 0b00000010); // Restart RTC
}