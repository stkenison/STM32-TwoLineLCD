#ifndef __STM32L476R_NUCLEO_LCD_H
#define __STM32L476R_NUCLEO_LCD_H

void delay_ms(unsigned int ms); //delay function in ms
void LCD_WriteCom(unsigned char com); //function to write commands to LCD
void LCD_WriteData(unsigned char dat); //function to write data to LCD
void LCD_Init(void); //function to initialize LCD
void LCD_Clear(void); //function to clear LCD
void LCD_DisplayString(unsigned int line, unsigned char *ptr); //fuction to display string on LCD

#define RS_Set()   (GPIOA->BSRR = GPIO_BSRR_BS0)   // Set PA0 to 1
#define RS_Clear() (GPIOA->BSRR = GPIO_BSRR_BR0)   // Clear PA0 to 0
#define E_Set()   (GPIOA->BSRR = GPIO_BSRR_BS1)   // Set PA1 to 1
#define E_Clear() (GPIOA->BSRR = GPIO_BSRR_BR1)   // Clear PA1 to 0
 

#endif
