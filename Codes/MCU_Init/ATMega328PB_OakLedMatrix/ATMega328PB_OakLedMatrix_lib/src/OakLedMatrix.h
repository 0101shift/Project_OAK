/* This library is custom built for ProjectOak design. This library maps the LEDs
on ProjectOak Main Board to a Clock function. So, the time parameters extracted 
from RTC sensor is mapped and displayed through on board LEDs using this library
*/

#ifndef OAKLEDMATRIX_H
#define OAKLEDMATRIX_H

#include <avr/io.h>

// Matrix dimensions
#define ROW_COUNT 6
#define COL_COUNT 6

typedef struct {
    volatile uint8_t *port;
    volatile uint8_t *ddr;
    uint8_t pin;
} GPIO;

// Initialization and control functions
void initMatrix(void);
void activateLedMatrix(uint8_t row, uint8_t col);
void deactivateLedMatrix(void);
void activateLedMatrixAll(void);

// Application-specific functions
void LedClockHourTime(uint8_t pattern);
void LedClockMinuteTime(uint8_t pattern);

#endif // OAKLEDMATRIX_H