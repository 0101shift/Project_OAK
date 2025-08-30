# 📚 Version History

## 🔮 V0.2 (Engineering Sample2 - Planned)
- Button circuit connectivity update
- Remove the transistor configuration from the LED matrix directly. Direct connection is simple.
- Battery monitoring circuit implementation (possibly).
- Push button components to be moved towards the inner circle to avoid mechanical collision.
- Top Silk graphics to be removed from the main board.
- Main board & BOT cavity PCB dimension to be increased in Y-direction, to match the STARP V0 board dimension
- 0E to be replaced with solder-jumpers in the LED matrix section
- DNPed MCU UART resistors
  
## 🔰 V0.1 (Engineering Sample - WIP)
- RTC changed from RX8130CE to RV-8263-C7.
- Addressed design issues with rework on the main board. Rework is documented in: [Project_OAK_MAIN_BRD_V0.1_Rework](Reworks/V0.1/README.md). 
- Cell voltage monitoring (along with LED indication) is not implemented in V0.1. Planned for V0.2
- Final testing in progress.

## 🚫 V0 (Initial Design - Unreleased)
- Initial board design consists of ATmega328PB MCU, RX8130CE RTC, 36 LEDs (12H + 24M) & 2032 coin cell holder  
- The design was not released for fabrication due to a change in the RTC module.

---
