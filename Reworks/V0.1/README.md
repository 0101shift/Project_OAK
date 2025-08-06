# 🔧 Project OAK MAIN BRD V0.1 Rework

This document outlines the necessary fixes, design limitations, and manual rework instructions for **Version 0.1** of the main board.

## 📋 Includes:
- Design errors identified during testing
- Workarounds and hardware patches
- Recommended changes for future revisions

> ⚠️ These instructions are critical if you're testing or building with `Project_OAK_MAIN_BRD_V0.1`.

---

## ❌ Design Errors

- The **BC547 transistor** symbol used in the design (V0 / V0.1) was of **TO-92 type**, while the actual **PCB footprint was for SOT-type**. This caused pin mismatch and made the footprint incompatible.
  
- The **push-button connection** was incorrect. It was connected between **pin 1 & pin 2** in the schematic, whereas the correct connection should be **between pin 1 & pin 3**. This made the switch unresponsive as pin 2 was shorted between GND and VCC via the 10k resistor.

---

## 🔶 Workaround for Transistor

- Since the BC547 pinout issue can't be resolved easily on the PCB, better to:
  - **Remove the transistor**, and  
  - **Short the Base and Emitter pins**.  
    This gives direct control of the LEDs to the MCU, and the firmware has been adjusted accordingly.

> 🔧 Additionally:
> - Remove the **resistor connected to the Collector pin**, as it will be left floating after the transistor is removed.
> - Reduce the **Base resistor value to 560Ω or less**, allowing sufficient current flow from the LEDs to the MCU.

---

## 🔶 Workaround for Push-Button

To make the push-button functional:
- Remove the **external pull-up resistor** (the internal pull-up is sufficient).
- Carefully **cut the trace between pin 2 and GND** to isolate pin 2. *(This can be tricky but is necessary.)*
- Connect **pin 3 to GND** using a short jumper wire.

---

## ✔️ V0.1 Rework Instructions

![Project_OAK_MAIN_BRD_V0.1_Rework](https://github.com/0101shift/Project_OAK/blob/f5fa7a730082febc1837f688a552a8a41a81e351/Reworks/V0.1/Project_OAK_MAIN_BRD_V0.1_Rework_Instruction.png)

---

## 📌 Recommendations for Future Revisions

- **Remove the transistors** in the LED section entirely:
  - The LED matrix draws low current and can be driven directly by the MCU.
  - This also helps reduce BOM cost and simplifies the layout.
  
- **Double-check all component footprints and connections** to avoid similar pin mismatch issues.

---
