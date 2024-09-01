void setup() {
  // Initialize UART0 at 9600 baud
  Serial.begin(2400);
  DDRB |= _BV(PB1);
  PORTB &= ~(1 << PB1);
}

void loop() {
  // Check if data is available on UART0
  if (Serial.available() > 0) {
    // Read the incoming byte from UART0
    //char received = Serial.read();

    // Echo the received character back on UART0
    //Serial.write(received);
  }

  // Send a character on UART0 every second
  Serial.print("Checking... 328PB UART CH0 is up!");
  Serial.println("");
  Serial.flush();
  PORTB ^= (1 << PB1);

  // Add a small delay to avoid flooding the serial monitor
  delay(2500);
}
