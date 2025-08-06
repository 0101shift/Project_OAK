# ⌚️ Project OAK (Open Art Work)

![Project OAK](CAD_Design/Mockup_Images/Project_OAK_Front.jpeg)
> *An approach to mimic analogue watch complications in a digital timepiece. One LED at a time.*

---

## 📚 Table of Contents

- [Repository Overview](#-repository-overview)
- [Project Overview](#-project-overview)
- [Version History](#-version-history)
- [Current Status](#-current-status)
- [Project OAK Layers](#-project-oak-layers)
- [Prototyping](#-prototyping)
- [Getting Started](#-getting-started)
  - [Programming the Board](#-programming-the-board)
  - [Arduino IDE Settings](#-arduino-ide-settings)

---

## 📁 Repository Overview

This repository contains all files related to **Project_OAK**, including:
- Design (DSN) files
- Datasheets
- Pin configuration sheet
- BOM (Bill of Materials)
- Source code and libraries

📎 **Project OAK SCH and DSN files can be viewed on [CADLAB.io](https://cadlab.io/project/28412)**

---

## 📖 Project Overview

**Project_OAK** explores a different approach to designing digital timepieces that mimic the beauty and intricacy of **[mechanical watch complications](https://teddybaldassarre.com/blogs/watches/watch-complications?srsltid=AfmBOoqZpyDy6AT5w2ClBAenimUXbEy8DH4jYCP8Jfb1IKT3pajwjdwo)**.

While building a digitalised analogue-style watch is fairly common, recreating some of the mechanical features in a purely digital watch is both challenging and exciting.

### 💭 Key Mechanical Complications Reimagined:
- **[Minute Repeater](https://www.jaeger-lecoultre.com/in-en/our-maison/masters-of-complications/minute-repeater-calibres#:~:text=The%20minute%20repeater%20chimes%20different,Master%20Hybris%20Mechanica%20calibre%20184.)**: Indicates time using chimes.
- **[GMT](https://www.longines.com/en-gr/universe/blog/what-is-a-gmt-watch)**: Tracks a second time zone in addition to the local time.
- **And more** ...

> Although smartwatches offer these functions via software, my goal is to **implement them locally using hardware logic** with minimal processing power.

To add to its uniqueness, the **entire watch will be made using stacked PCBs**, designed with multiple colours and selective finishes, giving it a true electronics-nerd feel.

---

## 🚩 Version History

### V0.1 (Engineering Sample - Field test WIP)
- Changed RTC from RX8130CE to RV-8263-C7 due to component unavailability
- Performed several rework on the main board to resolve design issues. Rework instructions are documented in the [Project_OAK_MAIN_BRD_V0.1_Rework](Reworks/Project_OAK_MAIN_BRD_V0.1_Rework.md).
- Cell voltage monitoring with LED indication is not implemented in V0.1. It will either be upgraded or completely removed in V0.2.
- With minimal rework, V0.1 functions as expected. Field testing is on going to evaluate circuit behavior.


### V0 (Initial Design - Unreleased)
- Initial board design consists of ATmega328PB MCU, RX8130CE RTC, 36 LEDs (12H + 24M) & 2032 coin cell holder  
- The design was not released for fabrication as the RTC module was out of stock. A different RTC module was used in the final release.

---

## ⏳ Current Status

The **initial version** of Project_OAK (V0.1) is just a simple digital watch featuring a **time display** using dual-tone LEDs.

> Future versions may include:
> - GMT & Minute Repeater functionality
> - Interactive sensors (Light, IMU, Temp, Step tracking, Buzzer, etc.)
> - Position tracking using GPS, LoRa, etc. (ambitious goal)
> - Low-power MCUs for long-life operation.
> - Explore the possibility of using a rechargable battery.
> - Solar panel integration for battery charging.

---

## 💎 Project OAK Layers

![Initial Mockup](CAD_Design/Mockup_Images/Project_OAK_Full_ASSY.jpeg)

![Complete Assembly](CAD_Design/Mockup_Images/Project_OAK_Full_ASSY_1.jpeg)

![Cross-section View](CAD_Design/Mockup_Images/Project_OAK_ASSY_Cross-section.jpeg)

![Exploded View](CAD_Design/Mockup_Images/Project_OAK_Exploded_view.jpeg)

> *(These are the outputs from V0.1 variant. Design changes are expected in V0.2)*

---

## 🔧 Prototyping

📌 **[Project_OAK_MAIN_BRD_V0.1](Design/LLD_Design/V0.1/Project_OAK_MAIN_BRD_V0.1_RTC_Change/Project_OAK_MAIN_BRD_V0.1.pdf) is an engineering sample. The design is not mature enough for mass production.**

The primary goal of this variant is to **test all available interfaces, validate MCU performance, identify design flaws, and iterate for improvements**.

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

> - Refer to this GitHub repo on how to burn Bootloader and how to flash code through Arduino IDE [MiniCore](https://github.com/MCUdude/MiniCore)
> - When programming the MAIN_BRD, update the ARDUINO IDE settings as shown below.

![Arduino IDE settings](Reference_docs/Project_OAK_Arduino_Programming_Settings.png)

#### ❤️‍🔥 Let me know what you think of this project, I'd love to hear your thoughts!

### ✨ Happy Designing!

---
