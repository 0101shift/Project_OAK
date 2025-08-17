# ⌚️ Project OAK (Open Art Work)

![Project OAK](CAD_Design/Mockup_Images/Project_OAK_Front.jpg)
> *An approach to mimic analogue watch complications in a digital timepiece. One LED at a time.*

---

## 📁 Repository Overview

This repository contains all files related to **Project OAK**, including:

- Design (DSN) files
- Datasheets
- Pin configuration sheet
- BOM (Bill of Materials)
- Source code and libraries

📎 **Project OAK SCH and DSN files can be viewed on [CADLAB.io](https://cadlab.io/project/28412)** (or) **can be viewed on [Kicanvas.org](https://github.com/0101shift/Project_OAK/tree/main/Design/LLD_Design/V0.1/Project_OAK_MAIN_BRD_V0.1_RTC_Change)**

---

## 📖 Project Overview

**Project_OAK** explores a different approach to designing digital timepieces that mimic the beauty and intricacy of **[mechanical watch complications](https://teddybaldassarre.com/blogs/watches/watch-complications?srsltid=AfmBOoqZpyDy6AT5w2ClBAenimUXbEy8DH4jYCP8Jfb1IKT3pajwjdwo)**.

While building a digitalised analogue-style watch is fairly common, recreating some of the mechanical features in a purely digital watch is both challenging and exciting.

### 💭 Key Mechanical Complications Reimagined:
- **[Minute Repeater](https://www.jaeger-lecoultre.com/in-en/our-maison/masters-of-complications/minute-repeater-calibres#:~:text=The%20minute%20repeater%20chimes%20different,Master%20Hybris%20Mechanica%20calibre%20184.)**: Indicates time using chimes.
- **[GMT](https://www.longines.com/en-gr/universe/blog/what-is-a-gmt-watch)**: Tracks a second time zone in addition to the local time.
- **And more** ...

> Although current smartwatches offer these functions via complex hardware, my goal is to **implement them using simple hardware** with minimal processing power.

- To add to its uniqueness, the **entire watch will be constructed using stacked PCBs**, which is aimed to be modular and reconfigurable based on our needs.
- The watch is designed with multiple colours and solder finishes, giving it a true electronics-nerd feel.

---

## ⛳️ Version History

### V0.2 (Engineering Sample2 - Planned)
- Button circuit connectivity update
- Remove transistor configuration from the LED matrix directly. Direct connection is simple.
- Battery monitoring circuit implementation.
- Push button components to be moved towards the inner circle to avoid mechanical collision.
- Top Silk graphics to be removed from main board.
- Main board & BOT cavity PCB dimension to be increased in Y-direction, to match it equal to the STARP V0 board dimension
- 0E to be replaced with solder-jumpers in LED matrix section
- DNPed MCU UART resistors
  
### V0.1 (Engineering Sample - WIP)
- RTC changed from RX8130CE to RV-8263-C7.
- Addressed design issues with rework on the main board. Rework is documented in: [Project_OAK_MAIN_BRD_V0.1_Rework](Reworks/V0.1/README.md). 
- Cell voltage monitoring (along with LED indication) is not implemented in V0.1. Planned for V0.2
- Final testing in progress.

### V0 (Initial Design - Unreleased)
- Initial board design consists of ATmega328PB MCU, RX8130CE RTC, 36 LEDs (12H + 24M) & 2032 coin cell holder  
- The design was not released for fabrication due to change of RTC module.

---

## 🎯 Down the line

The **initial version** of Project_OAK (V0.1 / V0.2) is just a simple watch featuring a **time display** using dual-tone LEDs.

> Future versions may include:
> - GMT & Minute Repeater functionality
> - Interactive sensors (Light, IMU, Temp, Step tracking, Buzzer, etc.)
> - Higher density LED matrix for complex visuals.
> - Position tracking using GPS, LoRa, etc. (ambitious!)
> - Exploring Low-power MCUs for long-life operation.
> - Rechargeable battery option.
> - Solar panel integration energy harvesting.

---

## 💎 Mechanical Integration

![Initial Mockup](CAD_Design/Mockup_Images/Project_OAK_Full_ASSY.jpeg)

![Cross-section View](CAD_Design/Mockup_Images/Project_OAK_ASSY_Cross-section.jpeg)

![Exploded View](CAD_Design/Mockup_Images/Project_OAK_Exploded_view_1.jpg)

![Exploded View](CAD_Design/Mockup_Images/Project_OAK_Drawing.jpg)

> *(These are the outputs from V0.1 variant. Design changes are expected in V0.2)*

---

## 🔧 Prototyping

📌 **[Project_OAK_MAIN_BRD_V0.1 / V0.2](Design/LLD_Design/V0.1/Project_OAK_MAIN_BRD_V0.1_RTC_Change/Project_OAK_MAIN_BRD_V0.1.pdf) is an engineering sample.**

The primary goal of these variants is to **test all available interfaces, validate MCU performance, identify design flaws, and iterate for improvements**.

Consider this board a creative playground, push its limits and explore unique feature additions for the upcoming revision.

---

## ⚙️ Getting Started

### 🔌 Programming the Board

The board can be programmed using the **Arduino IDE** via the ISP function. 

#### 📝 Requirements:
- Arduino UNO/MINI/NANO/MEGA as ISP programmer
- ICSP connection to the Main Board (test points on the bottom side)

#### 💡 ICSP Programming Notes:
- ICSP pins are exposed via **Test Points** arranged in 2.4mm pitch 2x3 connector style
- Either mount **male headers** or directly solder wires for programming
- Board supports **two power options**:
  - `3V Coin Cell (default)`
  - `EXT_3V3_IN` via ICSP (requires mounting resistor R1, which is **DNI by default**)

---

### ⚡ Arduino IDE Settings

> - Refer to this GitHub repo on how to burn the Bootloader and how to flash code through Arduino IDE [MiniCore](https://github.com/MCUdude/MiniCore)
> - When programming the MAIN_BRD, update the ARDUINO IDE settings as shown below.

![Arduino IDE settings](Reference_docs/Project_OAK_Arduino_Programming_Settings.png)

#### ❤️‍🔥 Let me know what you think of this project. I'd love to hear your thoughts!

### ✨ Happy Designing!

---
