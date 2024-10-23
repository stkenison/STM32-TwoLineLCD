#include "stm32l476xx.h"
#include "LCD.h"

int main(void){
	
	
	LCD_Init(); //Initialize LCD
	LCD_Clear(); //Clear LCD
	LCD_DisplayString(0, (unsigned char*)"Avoid pressing"); //Write ECE 3710 to LCD
	LCD_DisplayString(1, (unsigned char*)"2 buttons"); //Write Utah State to LCD
	delay_ms(2000);
	LCD_Clear();
	Keypad_Init();
	
	unsigned char key;
	char str[50];
	unsigned char len = 0;
	unsigned char max_len = 33;
	
	
	
	while(1){
		key = Keypad_Scan(); //Set key to key pressed
		
		switch (key){
			
			//if * is pressed, clear screen
			case '*':
				LCD_Clear(); //clear LCD
				str[0] = '\0';
				str[16] = '\0';
				len = 0;
				break;
			
			//if # is pressed, switch lines
			case '#':
				str[len] = ' ';
				str[len+1] = 0; //Null string terminator
				len++;
				if (len >= max_len) {
					len = 0;
				}
				break;
			
			//if no key is pressed, do nothing
			case 0xFF:
				break;
			
			//add key pressed to string
			default:
				str[len] = key;
				str[len+1] = 0; //Null string terminator
				len++;
				if (len >= max_len) {
					len = 0;
				}
		}
		
		if (len<17) LCD_DisplayString(0, (uint8_t *)str);
		if (len>=17) LCD_DisplayString(1, (uint8_t *)(str + 16));  // Shift the pointer to the 17th character
		
	}
}


