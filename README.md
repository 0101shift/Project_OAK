**The repository contains all the files related to Project_OAK**

View Project OAK SCH and DSN files on [CADLAB.io](https://cadlab.io/project/28412)

# Short brief about the project:

**An approach in bringing Mechanical complications to Digital timepieces.**

* Designing a normal analog watch with digital parts is basic but, recreating one of the mechanical complications 
  into a digital watch would be interesting. 
* Mechanical complications like Minute Repeater, GMT & moon phase are considered a few cool complications that have ever been designed in mechanical watches.
    * Minute Repeater is a complication where the watch indicates time through chimes.
    * GMT complication helps you to track one more additional time zone along with the current one.
    * Moon-phase complication helps you to keep track of the full moon.
* Though these complications are already available in smartwatches, recreating them locally with little hardware logic is cool. 
* To make it cooler, the whole watch body is going to be made from PCBs with suitable colour and finish to give the analog touch.
* The very initial version will be just a simple watch that features Time display functions. With further learning from the initial version, GMT & Minute repeater complications will be added to the upcoming version.
* Also, there will be a few digital sensors to create some interaction with the user. (future use case)
* The initial variant will be powered by a 3V Coin cell. Later versions may opt for a rechargeable battery.

Initial Mockup of **Project OAK**: 

![Project_OAK](https://github.com/user-attachments/assets/a187dfe7-927f-47bf-b156-ca0d9f44ddec)

(*as work is in progress, the final output may vary from the initial rendering)


**"Project_OAK_MAIN_BRD_V0.1 is just an Engineering Sample. The design is not Mature."**


NOTE: The main purpose of these engineering samples is to test the board in all possible ways using all the available interfaces and controls. Try pushing the MCU to its limit and identify issues and limitations. Also, list out the Hardware changes needed, and any feature to be added to the Main Board so that the upcoming revision will be more feature-rich with fewer failures. This is kind of a playground, apply your creativity and pull some unique creations. 


# To get started:

* Project_OAK_MAIN_BRD_V0.1 embeds all the major interfaces required to execute basic watch functionality.
* The Main Board contains **ATMega328PB** (MCU) and **RV-8263-C7** (RTC) as major component. The board also contains 36 LEDs (12 for hours and 24 for Minute representation), 3 tactile switches, and 3V supply monitoring.
* The MCU used is from the ATmega family, hence the MCU can be programmed through Arduino IDE with some modifications. Refer to this GitHub repo on how to burn Bootloader and how to flash codes through Arduino IDE. Link: https://github.com/MCUdude/MiniCore
* Programming the Main Board needs additional Arduino UNO/MINI/NANO/MEGA (configured as ISP) which is connected to MAIN_BRD through ICSP.
* ICSP pins are exposed as Test Points on the bottom side. Wire up male headers when programming the board.
* MAIN_BRD features a two-way supply to power the circuit. **Note: Make sure that only one option is enalbed at a time to power the Main Board.**
  * One way is through a 3V coin cell
  * Another way is through the EXT_3V3_IN pin present in the ICSP header (TP1) during programming/debugging. To power the board through ICSP, R1 should be mounted. By default, R1 made **DNI**
* When programming the MAIN_BRD, change the ARDUINO IDE settings as shown in the below image
  ![image](https://github.com/user-attachments/assets/9ddba8e6-f67e-4086-b126-84e10bf74e95)
* Since the Main Board is programmed through another Arduino (connected through ICSP), codes from ARDUINO IDE are uploaded by clicking the **Upload Using Programmer (Ctrl+Shift+U)** option. Please don't use the normal **upload** option. Otherwise, the code will be uploaded to the programmer Arduino instead of the Main Board.

* These data should be sufficient for basic code execution on the Main Board. This repo also contains datasheets, schematics, pin-configuration sheet, BOM and other related docs used in designing Project-OAK_MAIN_BRD_V0.1 Make use of it.

* New ideas and features are always welcome!

**Happy Designing!**
