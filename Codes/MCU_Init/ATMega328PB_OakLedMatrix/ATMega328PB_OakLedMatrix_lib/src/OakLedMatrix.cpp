/* This library is custom built for ProjectOak design. This library maps the LEDs
on ProjectOak Main Board to a Clock function. So, the time parameters extracted 
from RTC sensor is mapped and displayed through on board LEDs using this library
*/

#include "OakLedMatrix.h"
#include <util/delay.h>

// Since the OakLedMatrix GPIO connectivity is fixed, the GPIO configurations are defined in the library itself 
GPIO rows[ROW_COUNT] = {
    {&PORTB, &DDRB, PB0}, 
	{&PORTB, &DDRB, PB1}, 
	{&PORTB, &DDRB, PB2},
    {&PORTC, &DDRC, PC0}, 
	{&PORTC, &DDRC, PC1}, 
	{&PORTC, &DDRC, PC2}
};

GPIO cols[COL_COUNT] = {
    {&PORTC, &DDRC, PC3}, 
	{&PORTD, &DDRD, PD0}, 
	{&PORTD, &DDRD, PD1},
    {&PORTD, &DDRD, PD6}, 
	{&PORTD, &DDRD, PD7}, 
	{&PORTE, &DDRE, PE3}
};

// Initialize the OakLedMatrix
void initMatrix() {
    for (uint8_t i = 0; i < ROW_COUNT; i++) {
        *(rows[i].ddr) |= (1 << rows[i].pin);
        *(rows[i].port) &= ~(1 << rows[i].pin);
    }
    for (uint8_t i = 0; i < COL_COUNT; i++) {
        *(cols[i].ddr) |= (1 << cols[i].pin);
        *(cols[i].port) |= (1 << cols[i].pin);
    }
}

// Activate a specific LED in the OakLedMatrix 
void activateLedMatrix(uint8_t row, uint8_t col) {
    for (uint8_t i = 0; i < ROW_COUNT; i++) {
        *(rows[i].port) &= ~(1 << rows[i].pin);
    }
    for (uint8_t i = 0; i < COL_COUNT; i++) {
        *(cols[i].port) |= (1 << cols[i].pin);
    }

    *(rows[row].port) |= (1 << rows[row].pin);
    *(cols[col].port) &= ~(1 << cols[col].pin);

    _delay_ms(5);
}

// Deactivate all LEDs in the OakLedMatrix
void deactivateLedMatrix() {
    for (uint8_t i = 0; i < ROW_COUNT; i++) {
        *(rows[i].port) &= ~(1 << rows[i].pin);
    }
    for (uint8_t i = 0; i < COL_COUNT; i++) {
        *(cols[i].port) |= (1 << cols[i].pin);
    }
}

// Activate all LEDs in the OakLedMatrix
void activateLedMatrixAll() {
    for (uint8_t i = 0; i < ROW_COUNT; i++) {
        *(rows[i].port) |= (1 << rows[i].pin);
    }
    for (uint8_t i = 0; i < COL_COUNT; i++) {
        *(cols[i].port) &= ~(1 << cols[i].pin);
    }
}

// LED patterns for hour display
void LedClockHourTime(uint8_t pattern) {
    switch (pattern) {
        case 1: activateLedMatrix(0, 0); break;		//12'o Clock
        case 2: activateLedMatrix(0, 1); break;		//1'o Clock
        case 3: activateLedMatrix(0, 2); break;		//2'o Clock
        case 4: activateLedMatrix(0, 3); break;		//3'o Clock
        case 5: activateLedMatrix(0, 4); break;		//4'o Clock
        case 6: activateLedMatrix(0, 5); break;		//5'o Clock
        case 7: activateLedMatrix(1, 5); break;		//6'o Clock
        case 8: activateLedMatrix(1, 4); break;		//7'o Clock
        case 9: activateLedMatrix(1, 3); break;		//8'o Clock
        case 10: activateLedMatrix(1, 2); break;	//9'o Clock
        case 11: activateLedMatrix(1, 1); break;	//10'o Clock
        case 12: activateLedMatrix(1, 0); break;	//11'o Clock
        default: deactivateLedMatrix(); break;
    }
}

// LED patterns for minute display
void LedClockMinuteTime(uint8_t pattern) {
    switch (pattern) {
        case 1: activateLedMatrix(5, 0); break;		//0.0 Minute
        case 2: activateLedMatrix(2, 0); break;		//2.5 Minute
        case 3: activateLedMatrix(2, 1); break;		//5.0 Minute
        case 4: activateLedMatrix(2, 2); break;		//7.5 Minute
        case 5: activateLedMatrix(2, 3); break;		//10 Minute
        case 6: activateLedMatrix(2, 4); break;		//12.5 Minute
        case 7: activateLedMatrix(2, 5); break;		//15 Minute
        case 8: activateLedMatrix(3, 5); break;		//17.5 Minute
        case 9: activateLedMatrix(3, 4); break;		//20 Minute
        case 10: activateLedMatrix(3, 3); break;	//22.5 Minute	
        case 11: activateLedMatrix(3, 2); break;	//25 Minute	
        case 12: activateLedMatrix(3, 1); break;	//27.5 Minute
        case 13: activateLedMatrix(3, 0); break;	//30 Minute
        case 14: activateLedMatrix(4, 0); break;	//32.5 Minute
        case 15: activateLedMatrix(4, 1); break;	//35 Minute
        case 16: activateLedMatrix(4, 2); break;	//37.5 Minute
        case 17: activateLedMatrix(4, 3); break;	//40 Minute
        case 18: activateLedMatrix(4, 4); break;	//42.5 Minute
        case 19: activateLedMatrix(4, 5); break;	//45 Minute
        case 20: activateLedMatrix(5, 5); break;	//47.5 Minute
        case 21: activateLedMatrix(5, 4); break;	//50 Minute
        case 22: activateLedMatrix(5, 3); break;	//52.5 Minute
        case 23: activateLedMatrix(5, 2); break;	//55 Minute
        case 24: activateLedMatrix(5, 1); break;	//57.5 Minute
        default: deactivateLedMatrix(); break;
    }
}