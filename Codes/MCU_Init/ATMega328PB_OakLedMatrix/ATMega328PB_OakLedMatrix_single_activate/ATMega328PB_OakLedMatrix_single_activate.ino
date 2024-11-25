/**********************************************************************
  Simple AVR sketch to activate either Hour or Minute LEDs.
  For Clock LED mapping, check the Project_OAK_MCU_Pinouts.xlsx excel
**********************************************************************/

#include <avr/io.h>

// Pin configuration for the rows and columns of the LED matrix
#define ROW_COUNT 6
#define COL_COUNT 6

typedef struct {
  volatile uint8_t *port;
  volatile uint8_t *ddr;
  uint8_t pin;
} GPIO;

GPIO rows[ROW_COUNT] = {
  { &PORTB, &DDRB, PB0 },    //[0]
  { &PORTB, &DDRB, PB1 },    //[1]
  { &PORTB, &DDRB, PB2 },    //[2]
  { &PORTC, &DDRC, PC0 },    //[3]
  { &PORTC, &DDRC, PC1 },    //[4]
  { &PORTC, &DDRC, PC2 }     //[5]
};

GPIO cols[COL_COUNT] = {
  { &PORTC, &DDRC, PC3 },   //[6]
  { &PORTD, &DDRD, PD0 },   //[7]
  { &PORTD, &DDRD, PD1 },   //[8]
  { &PORTD, &DDRD, PD6 },   //[9]
  { &PORTD, &DDRD, PD7 },   //[10]
  { &PORTE, &DDRE, PE3 }    //[11]
};

// Function to initialize the GPIO pins
void initMatrix() {
  // Configure row pins as outputs and set them low
  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    *(rows[i].ddr) |= (1 << rows[i].pin);
    *(rows[i].port) &= ~(1 << rows[i].pin); // Initially low
  }

  // Configure column pins as outputs and set them high
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    *(cols[i].ddr) |= (1 << cols[i].pin);
    *(cols[i].port) |= (1 << cols[i].pin); // Initially high
  }
}

// Function to activate a specific LED
void activateLED(uint8_t row, uint8_t col) {
  // Turn off all rows and columns
  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    *(rows[i].port) &= ~(1 << rows[i].pin); // Set all rows low
  }
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    *(cols[i].port) |= (1 << cols[i].pin); // Set all columns high
  }

  // Activate the specific LED
  *(rows[row].port) |= (1 << rows[row].pin);  // Set the desired row high
  *(cols[col].port) &= ~(1 << cols[col].pin); // Set the desired column low
}

// Function to deactivate the matrix (turn off all LEDs)
void deactivateMatrix() {
  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    *(rows[i].port) &= ~(1 << rows[i].pin); // All rows low
  }
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    *(cols[i].port) |= (1 << cols[i].pin); // All columns high
  }
}

int main() {
  initMatrix();

  while (1) {
    // Example: Activate the LED at row 1, column 2
    activateLED(0, 1); // Indices are zero-based
    _delay_ms(500);

    // Example: Activate the LED at row 3, column 3
    activateLED(2, 2);
    _delay_ms(500);

    // Turn off all LEDs
    deactivateMatrix();
    _delay_ms(500);
  }
}
