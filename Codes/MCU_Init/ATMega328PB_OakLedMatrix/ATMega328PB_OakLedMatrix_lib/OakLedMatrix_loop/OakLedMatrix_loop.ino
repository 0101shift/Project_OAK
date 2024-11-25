/**********************************************************************************************************
  Simple AVR sketch demonstrate the OakLedMatrix lib. The sketch just lights up both Hour & Minute in loop

  "OakLedMatrix" library takes care of mapping LED pins to their respective Hr/Min positions 
**********************************************************************************************************/

#include "OakLedMatrix.h"
#include <util/delay.h>

int main() {
  initMatrix();

  while (1) {
    for (uint8_t i = 1; i <= 24; i++) {
      LedClockMinuteTime(i);
      LedClockHourTime(i);
      _delay_ms(50);
    }
  }
}
