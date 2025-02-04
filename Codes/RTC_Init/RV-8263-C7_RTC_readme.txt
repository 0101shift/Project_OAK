This document goes through all the register availability in RV-8263-C7 RTC for better understanding on it's functionality.


NOTE: RV-8263-C7 RTC has total of 18 register starting from 0x00h to 0x18h which holds all the functionality. 
1. The register at address 02h is an Offset register allowing the compensation of time deviation.
2. The register at address 03h is a free User RAM byte.
3. The addresses 04h through 0Ah are used as counters for the clock function (seconds up to year counters).
4. Address locations 0Bh through 0Fh contain alarm registers which define the conditions for an alarm.
5. The registers at 10h and 11h are for the timer function
The Seconds, Minutes, Hours, Date, Month and Year as well as the corresponding alarm registers are all coded in
Binary Coded Decimal (BCD) format. Other registers are coded normally.

Register Map:

/**********************************************************************************************************

|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  00h	 |				|Control1|			|Test|	| SR |	|STOP|	| SR |	| SR |	|CIE|	|12_24|	| CAP|

On reset, "00h = 00000000" -----> 00h = 00h

Major functions with this register are:

1. SW reset, 00h = 01011000 -----> 00h = 58h

2. 12 hr mode select, 00h = 00000010 -----> 00h = 02h

3. STOP, 00h = 00100000 -----> 00h = 20h

NOTE 1: post SW reset, reinitialize the I2C interface
NOTE 2: STOP function is used to update RTC timing data in the register so that there won't be any corruption of the data. Before updating the RTC time, 
first STOP the RTC clock, update the RTC registers and then clear the STOP to continue the normal operation.

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  01h	 |				|Control2|			|AIE|	| AF |	| MI |	|HMI |	| TF |	| FD |	| FD |	| FD |

On reset, "01h = 00000000" -----> 01h = 00h

Major functions with this register are:

1. AIE is enabled + AF is enabled and in read mode, 01h = 11000000 -----> 01h = C0h (write)
2. AIE is enabled + AF status is cleared post INT, 	01h = 10000000 -----> 01h = 80h (write)
3. MI is enabled, 									01h = 00100000 -----> 01h = 20h (write)
4. HMI is enabled, 									01h = 00010000 -----> 01h = 10h (write)
5. TF flag is set due to MI,						01h = 00101000 -----> 01h = 28h (read)
6. TF flag is set due to HMI,						01h = 00011000 -----> 01h = 18h (read)
7. TF flag is cleared post interrupt,				01h = 00xx0000 -----> 01h = 20h / 10h (write)	 

NOTE 3: The generation of interrupts from the Alarm Function is controlled via bit Alarm Interrupt Enable. If bit AIE is enabled, the INT pin follows the condition of bit AF. 
AF remains set until cleared by command. Once AF has been cleared, it will only be set again when the time increments to match the alarm condition once more. 
Alarm registers which have their AE_x bit at logic 1 are ignored.

NOTE 4: By clearing the alarm enable bit (AE_x) of one or more of the alarm registers, the corresponding alarm condition(s) are active. 
When an alarm occurs, AF is set logic 1. The asserted AF can be used to generate an interrupt (INT). The AF is cleared by command.

NOTE 5: The Minute Interrupt (bit MI) and Half Minute Interrupt (bit HMI) are pre-defined timers for generating interrupt pulses on pin INT. 
The minute and half minute interrupts must only be used when the frequency offset is set to normal mode. In normal mode, the interrupt pulses on pin INT are 15.625 ms wide.

NOTE 6: When starting MI, the first interrupt will be generated after 1 second to 59 seconds. When starting HMI, the first interrupt will be generated after 1 second to 29 seconds. 
Subsequent periods do not have such a delay. The timers can be enabled independently from one another.
However, a Minute Interrupt enabled on top of a Half Minute Interrupt is not distinguishable.

NOTE 7: The Timer Flag (bit TF) is set logic 1 on the first trigger of the Countdown Timer or the MI and HMI Interrupt. 
The purpose of the flag is to allow the controlling system to interrogate what caused the interrupt: Timer/MI/HMI or Alarm. 
The flag can be read and cleared by command. See Timer Register 11h for more details. 

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  02h	 |		     |offset register|	 	|MODE|	| 					OFFSET 							 |

On reset, "02h = 00000000" -----> 02h = 00h

Major functions with this register are:

This register holds the OFFSET value to digitally compensate the initial frequency deviation of the 32.768 kHz oscillator or for aging adjustment. Since CLKOUT signal is not connected to the MCU, implementing this function is not possible as the compensation needs feedback by watching CLKOUT pin. Maybe need to add this function in next version.

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  03h	 |		     	|User RAM|	 		| 						RAM DATA 							 |

On reset, "03h = 00000000" -----> 03h = 00h

Free RAM byte, which can be used for any purpose, for example, status byte of the system. NOT USED IN THIS DESIGN.

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  04h	 |				|Seconds|			| OS |	| 40 |	| 20 |	| 10 |	| 8 |	| 4 |	| 2 |	| 1  |

On reset, "04h = 10000000" -----> 04h = 80h

This register holds the count of seconds, in two binary coded decimal (BCD) digits. Values will be from 00 to 59.

1. To represent 45 sec, "04h = 01000101" -----> 04h = 45h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  05h	 |				|Minutes|			| X  |	| 40 |	| 20 |	| 10 |	| 8 |	| 4 |	| 2 |	| 1  |

On reset, "05h = 00000000" -----> 05h = 00h

This register holds the count of minutes, in two binary coded decimal (BCD) digits. Values will be from 00 to 59.

1. To represent 07 min, "05h = 00000111" -----> 05h = 07h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  06h	 |				 |Hours|			| X  |	| X  |  |AMPM|	| 10 |	| 8 |	| 4 |	| 2 |	| 1  |

On reset, "06h = 00000000" -----> 06h = 00h

This register holds the count of hours, in two binary coded decimal (BCD) digits. Values will be from 00 to 59.

1. If 12_24 bit is 1, then the hour is expressed in 12hr format. If not, 24hr format.
2. To represent 07 hr in 12hr format, "06h = 00000111" -----> 06h = 07h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  07h	 |				 |Date|				| X  |	| X  |  | 20 |	| 10 |	| 8 |	| 4 |	| 2 |	| 1  |

On reset, "07h = 00000000" -----> 07h = 00h

This register holds the current date of the month, in two binary coded decimal (BCD) digits. Values will range from 01 to 31. Leap years are correctly handled from 2000 to 2099.

1. To represent date 13, "07h = 00010011" -----> 07h = 13h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  08h	 |				|Weekday|			| X  |	| X  |  | X  |	| X  |	| X |	| 4 |	| 2 |	| 1  |

On reset, "08h = 00000110" -----> 08h = 06h

This register holds the current day of the week. Each value represents one weekday that is assigned by the user. Values will range from 0 to 6.

1. To represent WEEKDAY1, "08h = 00000000" -----> 08h = 00h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  09h	 |				 |Month|			| X  |	| X  |  | X  |	| 10 |	| 8  |	| 4  |	| 2  |	| 1  |

On reset, "09h = 00000001" -----> 09h = 01h

This register holds the current month, in two binary coded decimal (BCD) digits. Values will range from 01 to 12.

1. To represent JANUARY, "09h = 00000001" -----> 09h = 01h

***********************************************************************************************************/

/**********************************************************************************************************
|Register| 				|Function|			|Bit7|	|Bit6|	|Bit5|	|Bit4|	|Bit3|	|Bit2|	|Bit1|	|Bit0|
|																										 |	
|  0Ah	 |				  |Year|			| 80 |	| 40 |  | 20 |	| 10 |	| 8  |	| 4  |	| 2  |	| 1  |

On reset, "0Ah = 00000000" -----> 0Ah = 00h

This register holds the current year, in two binary coded decimal (BCD) digits. Values will range from 00 to 99. Leap years are correctly handled from 2000 to 2099

1. To represent 2025, "0Ah = 00100101" -----> 0Ah = 25h

***********************************************************************************************************/