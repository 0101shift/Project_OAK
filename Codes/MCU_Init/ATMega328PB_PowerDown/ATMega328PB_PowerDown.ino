/*********************************************************
  This sketch puts MCU to power-down mode and wakaesup once every minute.
  This sketch uses internal 8MHz oscillator.
  Once MCU wake, it blinks the LEDs for half a second and goes back to power-down
 ********************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

volatile uint8_t wdt_interrupt_counter = 0;

void setup_wdt(void)
{
  // Disable interrupts
  cli();

  // Reset watchdog
  wdt_reset();

  // Set up WDT interrupt mode (not reset mode)
  WDTCSR |= (1 << WDCE) | (1 << WDE); // Enable configuration mode
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // 8s timeout (prescaler = 1024K)

  // Enable interrupts
  sei();
}

ISR(WDT_vect)
{
  wdt_interrupt_counter++;
}

void enter_power_down_mode(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power-down
  sleep_enable();                      // Enable sleep mode
  sleep_cpu();                         // Enter sleep mode

  // MCU wakes up here after WDT interrupt
  sleep_disable();                     // Disable sleep mode on wake-up
}

int main(void)
{
  // Set PB0 as output for example action (e.g., LED)
  DDRB |= _BV(PB1);  // Set PB0 as output, ignore the rest
  DDRC |= _BV(PC3);
  DDRD |= _BV(PD0);
  DDRD |= _BV(PD1);
  DDRD |= _BV(PD6);
  DDRD |= _BV(PD7);
  DDRE |= _BV(PE3);

  PORTB &= ~(1 << PB1);
  PORTC |= (1 << PC3);
  PORTD |= (1 << PD0);
  PORTD |= (1 << PD1);
  PORTD |= (1 << PD6);
  PORTD |= (1 << PD7);
  PORTE |= (1 << PE3);
  
  // Setup Watchdog Timer
  setup_wdt();

  while (1)
  {
    // Enter power-down mode
    enter_power_down_mode();

    // Wake-up and check if 1 minute has passed
    if (wdt_interrupt_counter >= 7) // 7 * 8s = 56s + 4s (approx. 60s)
    {
      wdt_interrupt_counter = 0;  // Reset the counter
      // Perform the 1-second action (toggle PB0)
      PORTB |= (1 << PB1);
      PORTC &= ~(1 << PC3);
      PORTD &= ~(1 << PD0);
      PORTD &= ~(1 << PD1);
      PORTD &= ~(1 << PD6);
      PORTD &= ~(1 << PD7);
      PORTE &= ~(1 << PE3);
      _delay_ms(100);            // Delay for 0.5 second
      PORTB &= ~(1 << PB1);
      PORTC |= (1 << PC3);
      PORTD |= (1 << PD0);
      PORTD |= (1 << PD1);
      PORTD |= (1 << PD6);
      PORTD |= (1 << PD7);
      PORTE |= (1 << PE3);
    }
  }

  return 0;
}
