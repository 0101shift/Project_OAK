# 📚 Version History

## ⛳️ V1.0 (xxx - WIP)
- Scaling down the overall thickness from 11.4 mm to 8.4 mm (except for the bottom cavity & strap PCB; the thickness of all other PCBs is reduced).
- Planning to change the coin cell from CR2032 to CR2025 and the coin cell holder to BC-2018-TR, reducing the overall battery thickness from 3.2 mm to 2.5 mm.
- Planning to move the push buttons from the top to the bottom side of the main board, since the top cavity PCB height is reduced from 1.6 mm to 1 mm.
- Planning to use a common LED color throughout the design to minimise uneven color diffusion through the PCB dials.
- Planning to increase the pull-up resistor values to reduce leakage.
- Exploring options to include an IMU (LIS2DW12) for future enhancements and upgrading the RTC to RV-3028-C7 for improved performance.
- SW optimisation to reduce current consumption for longer battery life.
- Along with the above changes, all V0.2 updates are also implemented in V1.0.

## 🔮 V0.2 (Engineering Sample2 - merging with V1.0)
- Button circuit connectivity update
- Remove the transistor configuration from the LED matrix directly. Direct connection is simple.
- Battery monitoring circuit implementation (possibly).
- Push button components to be moved towards the inner circle to avoid mechanical collision.
- Top Silk graphics to be removed from the main board.
- Main board & BOT cavity PCB dimension to be increased in the Y-direction, to match the STARP V0 board dimension
- 0E to be replaced with solder-jumpers in the LED matrix section
- DNPed MCU UART resistors
  
## 🔰 V0.1 (Engineering Sample)
- RTC changed from RX8130CE to RV-8263-C7.
- Addressed design issues with rework on the main board. Rework is documented in: [Project_OAK_MAIN_BRD_V0.1_Rework](https://github.com/0101shift/Project_OAK/blob/9e24250cb21920fe7c5c715ad4de5ba70b185401/Reworks/V0.1/README.md). 
- Cell voltage monitoring (along with LED indication) is not implemented in V0.1. Planned for V0.2
- Final testing in progress.

 <div style="background-color:#ffe6e6; padding:10px; border-radius:6px;">
⚠️ <b>Caution:</b> Other layers, except the Main Board, are reused from V0
</div>

## 🚫 V0 (Initial Design - Unreleased)
- Initial board design consists of ATmega328PB MCU, RX8130CE RTC, 36 LEDs (12H + 24M) & 2032 coin cell holder  
- The design was not released for fabrication due to a change in the RTC module.

---
