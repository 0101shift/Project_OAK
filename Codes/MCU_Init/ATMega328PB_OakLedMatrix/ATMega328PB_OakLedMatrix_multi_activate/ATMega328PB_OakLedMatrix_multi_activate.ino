/**********************************************************************
  Simple AVR sketch to activate both Hour & Minute LEDs simultaneously.
  For Clock LED mapping, check the Project_OAK_MCU_Pinouts.xlsx excel
**********************************************************************/

#include <avr/io.h>
#include <util/delay.h>

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

// Function to activate multiple LEDs
void activateMultipleLEDs(uint8_t activeLEDs[][2], uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    uint8_t row = activeLEDs[i][0];
    uint8_t col = activeLEDs[i][1];

    // Turn off all rows and columns first
    for (uint8_t j = 0; j < ROW_COUNT; j++) {
      *(rows[j].port) &= ~(1 << rows[j].pin); // All rows low
    }
    for (uint8_t j = 0; j < COL_COUNT; j++) {
      *(cols[j].port) |= (1 << cols[j].pin); // All columns high
    }

    // Activate one LED at a time
    *(rows[row].port) |= (1 << rows[row].pin);  // Set the specific row high
    *(cols[col].port) &= ~(1 << cols[col].pin); // Set the specific column low

    // Small delay to prevent ghosting and allow persistence of vision
    _delay_ms(5);
  }
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

  // Example: Activate LEDs at (0, 0), (1, 1), and (2, 2)
  uint8_t activeLEDs[][2] = {
    {0, 0}, // Row 0, Column 0
    {3, 2}, // Row 1, Column 1
    {5, 4}, // Row 2, Column 2
  };


  uint8_t ledCount = sizeof(activeLEDs) / sizeof(activeLEDs[0]);

  while (1) {
    // Activate the selected LEDs with multiplexing
    activateMultipleLEDs(activeLEDs, ledCount);
  }
}
