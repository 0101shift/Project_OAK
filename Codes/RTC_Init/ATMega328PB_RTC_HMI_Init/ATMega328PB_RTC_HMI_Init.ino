#include <Wire.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD3

#define SLAVE_ADDRESS 0x51  // Replace with your I2C slave address
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
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL2, 0x90);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_TIM_MODE, 0x19);
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
        writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL2, 0x90);
        Serial.println("Alarm!");
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
