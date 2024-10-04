# STM32-TwoLineLCD

## Introduction

A repository containing the C code necessary to write characters to a 2-line LCD from an STM32L476 Nucleo Microcontroller. This code was created by Spencer Kenison and Jeremy Croft from the ECE 3710 Microcontrollers class at Utah State University. 

This C code was originally written in Keil uVision5. The 2-Line LCD used was an "MD21605G12W3-BNMLW-VE" LCD. It requires the core_cm4.h C header file to run, in addition to the files in the repository. 

## Running program

The program will automatically write the desired text onto the two line LCD when the microcontroller is powered on. This includes initializing the microcontroller clocks & GPIO in addition to the LCD. The text to be written can be varied. 

The following functions from the LCD.C file are built to be used in other situations as desired.
- LCD_Write Com() //writes the command in the com variable to the LCD.
- LCD_WriteData() //writes the data in the dat variable to the LCD screen.
- LCD_Init() //initializes microcontroller clocks, GPIO, and LCD screen
- LCD_Clear() //clears all text on LCD screen
- LCD_DisplayString() //writes a string of up to 16 characters to LCD screen.
- delay_ms() //forces a delay of variable "ms" milliseconds (using 16 MHz MSI clock)





