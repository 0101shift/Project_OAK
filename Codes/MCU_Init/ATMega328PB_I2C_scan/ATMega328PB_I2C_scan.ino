#include <Wire.h>

void setup() {
  // Start the I2C bus as master
  Wire.begin();
  DDRB |= _BV(PB1);
  PORTB &= ~(1 << PB1);

  // Start serial communication to display the results
  Serial.begin(9600);
  while (!Serial); // Wait for the serial port to connect (useful for native USB)

  Serial.println("I2C Scanner Ready. Scanning...");

  scanI2CDevices();
}

void loop() {
  // Optionally, you can rescan periodically by calling scanI2CDevices() again
  delay(5000); // Wait for 5 seconds before scanning again
  scanI2CDevices();
}

void scanI2CDevices() {
  int nDevices = 0;

  for (byte address = 1; address < 127; address++) {
    // Begin transmission to the I2C device at 'address'
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    // If a device responds, print its address
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
      PORTB ^= (1 << PB1);
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("Scan completed.");
  }
}
