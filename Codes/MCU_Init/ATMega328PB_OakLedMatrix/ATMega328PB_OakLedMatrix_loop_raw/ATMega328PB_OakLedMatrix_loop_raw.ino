/**********************************************************************
  Simple AVR sketch to light up both Hour & Minute LEDs in a loop.
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
void activateLedMatrix(uint8_t row, uint8_t col) {
  // Turn off all rows and columns first
  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    *(rows[i].port) &= ~(1 << rows[i].pin); // All rows low
  }
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    *(cols[i].port) |= (1 << cols[i].pin); // All columns high
  }

  // Activate the specific LED
  *(rows[row].port) |= (1 << rows[row].pin);  // Set the specific row high
  *(cols[col].port) &= ~(1 << cols[col].pin); // Set the specific column low

  // Small delay for persistence of vision
  _delay_ms(5);
}

// Function to deactivate the matrix (turn off all LEDs)
void deactivateLedMatrix() {
  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    *(rows[i].port) &= ~(1 << rows[i].pin); // All rows low
  }
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    *(cols[i].port) |= (1 << cols[i].pin); // All columns high
  }
}

void LedClockHourTime(uint8_t pattern) {
  switch (pattern) {
    case 1:
      activateLedMatrix(0, 0);
      break;

    case 2:
      activateLedMatrix(0, 1);
      break;

    case 3:
      activateLedMatrix(0, 2);
      break;

    case 4:
      activateLedMatrix(0, 3);
      break;

    case 5:
      activateLedMatrix(0, 4);
      break;

    case 6:
      activateLedMatrix(0, 5);
      break;

    case 7:
      activateLedMatrix(1, 5);
      break;

    case 8:
      activateLedMatrix(1, 4);
      break;

    case 9:
      activateLedMatrix(1, 3);
      break;

    case 10:
      activateLedMatrix(1, 2);
      break;

    case 11:
      activateLedMatrix(1, 1);
      break;

    case 12:
      activateLedMatrix(1, 0);
      break;

    default:
      deactivateLedMatrix();
      break;
  }
}

void LedClockMinuteTime(uint8_t pattern) {
  switch (pattern) {
    case 1:
      activateLedMatrix(5, 0);
      break;

    case 2:
      activateLedMatrix(2, 0);
      break;

    case 3:
      activateLedMatrix(2, 1);
      break;

    case 4:
      activateLedMatrix(2, 2);
      break;

    case 5:
      activateLedMatrix(2, 3);
      break;

    case 6:
      activateLedMatrix(2, 4);
      break;

    case 7:
      activateLedMatrix(2, 5);
      break;

    case 8:
      activateLedMatrix(3, 5);
      break;

    case 9:
      activateLedMatrix(3, 4);
      break;

    case 10:
      activateLedMatrix(3, 3);
      break;

    case 11:
      activateLedMatrix(3, 2);
      break;

    case 12:
      activateLedMatrix(3, 1);
      break;

    case 13:
      activateLedMatrix(3, 0);
      break;

    case 14:
      activateLedMatrix(4, 0);
      break;

    case 15:
      activateLedMatrix(4, 1);
      break;

    case 16:
      activateLedMatrix(4, 2);
      break;

    case 17:
      activateLedMatrix(4, 3);
      break;

    case 18:
      activateLedMatrix(4, 4);
      break;

    case 19:
      activateLedMatrix(4, 5);
      break;

    case 20:
      activateLedMatrix(5, 5);
      break;

    case 21:
      activateLedMatrix(5, 4);
      break;

    case 22:
      activateLedMatrix(5, 3);
      break;

    case 23:
      activateLedMatrix(5, 2);
      break;

    case 24:
      activateLedMatrix(5, 1);
      break;

    default:
      deactivateLedMatrix();
      break;
  }
}

int main() {
  initMatrix();

  while (1) {
    for (uint8_t i = 1; i <= 24; i++) {
      LedClockHourTime(i); // Display each pattern
      LedClockMinuteTime(i);
      _delay_ms(50);    // Wait 50ms before switching to the next pattern
    }
  }
}
