#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Wire.h>
#include <util/delay.h>

#define SLAVE_ADDRESS 0x51  // Replace with your I2C slave address
#define REGISTER_ADDRESS_CTRL1 0x00
#define REGISTER_ADDRESS_CTRL2 0x01
#define REGISTER_ADDRESS_SEC_ALRM 0x0B
#define REGISTER_ADDRESS_TIM_MODE 0x11

volatile unsigned long last_interrupt_time = 0;  // To store the last interrupt time
unsigned long debounce_delay = 500;  // 500ms debounce delay

void setup()
{
  comms();

  DDRD &= ~(1 << DDD2);  // Clear PD2 to make it an input
  DDRD &= ~(1 << DDD3);  // Clear PD3 to make it an input

  // Enable pull-up resistor on PD2 (optional, depends on external circuit)
  PORTD |= (1 << PORTD2);

  // Configure INT1 to trigger on falling edge
  EICRA |= (1 << ISC01);  // ISC01 = 1, ISC00 = 0: Falling edge
  EICRA &= ~(1 << ISC00);

  // Configure INT1 to trigger on falling edge
  EICRA |= (1 << ISC11);  // ISC11 = 1, ISC10 = 0: Falling edge
  EICRA &= ~(1 << ISC10);

  // Enable INT0 interrupt
  EIMSK |= (1 << INT0);

  // Enable INT1 interrupt
  EIMSK |= (1 << INT1);

  // Enable global interrupts
  sei();
}

ISR(INT0_vect)
{
  unsigned long current_time = millis();  // Get the current time (in ms)

  // Check if enough time has passed since the last interrupt
  if (current_time - last_interrupt_time > debounce_delay) {
    PORTB ^= (1 << PB1);

    // Update the last interrupt time
    last_interrupt_time = current_time;
  }
}

ISR(INT1_vect)
{
  PORTB ^= (1 << PB1);
}

void loop()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sleep_cpu();                         // Enter sleep mode
  sleep_disable();                     // Disable sleep mode on wake-up
  comms();
}

/////////////////////////////////////////////////
/*------------------Functions------------------*/
/////////////////////////////////////////////////

// Serial and I2C Init
void comms()
{
  DDRB |= _BV(PB1);
  PORTB &= ~(1 << PB1);

  Wire.begin();
  Serial.begin(9600);  // Initialize Serial for debugging
  while (!Serial);  // Wait for serial port to connect

  Serial.println("MCU woke up!");

  // Write to a register
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL1, 0x58); // Example: Writing 0x55 to register 0x00
  delay(100);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_CTRL2, 0xA0);
  writeRegister(SLAVE_ADDRESS, REGISTER_ADDRESS_TIM_MODE, 0x19);
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
