#include "stm32l476xx.h"
#include "LCD.h"

int main(void){
	
	LCD_Init(); //Initialize LCD
	LCD_Clear(); //Clear LCD
	LCD_DisplayString(0, (unsigned char*)"ECE 3710"); //Write ECE 3710 to LCD
	LCD_DisplayString(1, (unsigned char*)"Utah State"); //Write Utah State to LCD
	
	while(1);
}


