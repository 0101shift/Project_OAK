#include <Wire.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD3

#define SLAVE_ADDRESS 0x51  // Replace with your I2C slave address
#define REGISTER_ADDRESS_SECOND 0x04  // Replace with the register you want to access
#define REGISTER_ADDRESS_MINUTE 0x05
#define REGISTER_ADDRESS_HOUR 0x06
#define REGISTER_ADDRESS_DATE 0x07
#define REGISTER_ADDRESS_MONTH 0x09
#define REGISTER_ADDRESS_YEAR 0x0A
#define REGISTER_ADDRESS_CTRL1 0x00
#define REGISTER_ADDRESS_CTRL2 0x01
#define REGISTER_ADDRESS_SEC_ALRM 0x0B
#define REGISTER_ADDRESS_TIM_MODE 0x11

void setup() {

  DDRB |= _BV(PB1);
  PORTB &= ~(1 << PB1);
  DDRD &= ~(1 << BUTTON_PIN);

  Wire.begin();  // Initialize I2C
  Serial.begin(9600);  // Initialize Serial for debugging
  while (!Serial);  // Wait for serial port to connect

  Serial.println("I2C Communication Ready");

  // Write to a register
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL1, 0x58); // Example: Writing 0x55 to register 0x00
  delay(2000);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL2, 0xA0);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_TIM_MODE, 0x19);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_YEAR, 0b00100100);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_MONTH, 0b00001001);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_DATE, 0b00000001);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_HOUR, 0b00000010);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_MINUTE, 0b00110011);
}

void loop() {
  setup();

  uint8_t button_state = 0;
  uint8_t last_button_state = 1;  // Assuming button is not pressed at startup

  while (1)
  {
    // Read the current state of the button
    button_state = PIND & (1 << BUTTON_PIN);

    // Check if button was pressed (low state)
    if (button_state == 0 && last_button_state != 0)
    {
      // Check again to confirm the button is still pressed
      if ((PIND & (1 << BUTTON_PIN)) == 0)
      {
        // Toggle the LED
        PORTB ^= (1 << PB1);
        Serial.println("Alarm!");

        /*-------------Code to read the values from registers--------------*/
        Serial.println("-----------------------------------------------------");

        uint8_t data1 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_YEAR);
        Serial.print("YEAR:");
        Serial.println(BCDtoDEC(data1));

        uint8_t data2 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_MONTH);
        Serial.print("MONTH:");
        Serial.println(BCDtoDEC(data2));

        uint8_t data3 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_DATE);
        Serial.print("DATE:");
        Serial.println(BCDtoDEC(data3));

        uint8_t data4 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_HOUR);
        Serial.print("HOUR:");
        Serial.println(BCDtoDEC(data4));

        uint8_t data5 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_MINUTE);
        Serial.print("MINUTE:");
        Serial.println(BCD7ToDEC(BCD8To7(data5)));

        uint8_t data6 = readRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_SECOND);
        Serial.print("SECOND:");
        Serial.println(BCD7ToDEC(BCD8To7(data6)));

        Serial.println("-----------------------------------------------------");
        writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL2, 0xA0);
      }
    }
    // Update the last button state
    last_button_state = button_state;
  }
  return 0;
}

// Function to write to a register
void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
  Wire.beginTransmission(deviceAddress);  // Begin I2C transmission to the slave
  Wire.write(registerAddress);  // Send the register address
  Wire.write(data);  // Send the data to write
  Wire.endTransmission();  // End the transmission
}

// Function to read from a register
uint8_t readRegister(uint8_t deviceAddress, uint8_t registerAddress) {
  uint8_t data = 0;

  Wire.beginTransmission(deviceAddress);  // Begin I2C transmission to the slave
  Wire.write(registerAddress);  // Send the register address
  Wire.endTransmission(false);  // End the transmission with a repeated start

  Wire.requestFrom(deviceAddress, (uint8_t)1);  // Request 1 byte of data
  if (Wire.available()) {
    data = Wire.read();  // Read the received data
  }

  return data;
}

uint8_t BCD8To7(uint8_t bcd8) {
  // Use only the lower 7 bits of the 8-bit BCD value
  return bcd8 & 0x7F;  // Mask to keep only the lower 7 bits
}

uint8_t BCD7ToDEC(uint8_t bcd7) {
  uint8_t tens = (bcd7 >> 4) & 0x07;  // Extract the upper 3 bits
  uint8_t ones = bcd7 & 0x0F;         // Extract the lower 4 bits
  return (tens * 10) + ones;          // Combine to form the decimal number
}

uint8_t BCDtoDEC(uint8_t bcdValue) {
  uint8_t tens = (bcdValue >> 4) & 0x0F;  // Extract the high nibble (tens place)
  uint8_t ones = bcdValue & 0x0F;         // Extract the low nibble (ones place)
  return (tens * 10) + ones;              // Combine to form the decimal number
}
