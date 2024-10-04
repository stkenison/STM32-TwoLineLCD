#include "LCD.h"
#include "stm32l476xx.h"

//waits for ms milliseconds. 
void delay_ms(unsigned int ms) {
	//Configure SysTick
	SysTick->LOAD = 16000 - 1;// Load with number of clocks per millisecond (16 MHz / 1000)
	SysTick->VAL = 0;// Clear current value register
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;  // Enable SysTick timer
	
	//Loop until proper delay is achieved
	for (unsigned int i = 0; i < ms; i++) {
		while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));// Wait until the COUNTFLAG is set
    }
	//Disable SysTick timer
}


//writes the command in com to the LCD. 
void LCD_WriteCom(unsigned char com) {
	unsigned char com1 = com&0xf0; //get four high bits
	unsigned char com2 = (com<<4)&0xf0; //get four low bits
	E_Clear(); //set E to 0
	RS_Clear(); //set RS to 0
	
	//Set first four high bits
	GPIOA->ODR &= ~(0xF << 4);  // Clear bits PA4–PA7 
	GPIOA->ODR |= com1;  // Set the value on PA4–PA7
	
	E_Set(); //set E to 1 to grab command
	delay_ms(10); //wait for command to be grabbed
	E_Clear(); //set E to 0
	RS_Clear(); //set RS to 0
	
	//Set last four low bits
	GPIOA->ODR &= ~(0xF << 4);  // Clear bits PA4–PA7 
	GPIOA->ODR |= com2;  // Set the value on PA4–PA7
	
	E_Set(); //set E to 1 to grab command
	delay_ms(10); //wait for command to be grabbed
	E_Clear(); //set E to 0
	RS_Clear(); //set RS bit to 0
}

//writes the data in dat to the LCD. 
void LCD_WriteData(unsigned char dat) {
	unsigned char dat1 = dat&0xf0; //get four high bits
	unsigned char dat2 = (dat<<4)&0xf0; //get four low bits
	E_Clear(); //set E to 0
	RS_Set(); //set RS to 0
	
	//Set first four high bits
	GPIOA->ODR &= ~(0xF << 4);  // Clear bits PA4–PA7 
	GPIOA->ODR |= dat1;  // Set the value on PA4–PA7
	
	E_Set(); //set E to 1 to grab command
	delay_ms(10); //wait for command to be grabbed
	E_Clear(); //set E to 0
	RS_Set(); //set RS to 0
	
	//Set last four low bits
	GPIOA->ODR &= ~(0xF << 4);  // Clear bits PA4–PA7 
	GPIOA->ODR |= dat2;  // Set the value on PA4–PA7
	
	E_Set(); //set E to 1 to grab command
	delay_ms(10); //wait for command to be grabbed
	E_Clear(); //set E to 0
}

void LCD_Init(void){
	RCC->CR |= RCC_CR_HSION; //Enable HSI by setting HSION bit in RCC_CR register
	while (!(RCC->CR & RCC_CR_HSIRDY)); //Wait until HSI is ready
	//Set HSI as the system clock source using the RCC_CFGR register
	RCC->CFGR &= ~RCC_CFGR_SW;        // Clear system clock switch bits
  RCC->CFGR |= RCC_CFGR_SW_HSI;     // Select HSI as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); //Wait until HSI is actually being used
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable GPIO A clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //Enable GPIO C clock
	//Configure GPIO A as output (for LCD)
	GPIOA->MODER &= ~0x0000FFFF; //GPIOA->MODER &= ~(GPIO_MODER_MODE5);   // Clear mode for GPIO A
  GPIOA->MODER |= 0x00005555; //GPIOA->MODER |= GPIO_MODER_MODE5_0;    // Set GPIO A as output (01)
	
	delay_ms(100); //delay in case of sudden reset
	LCD_WriteCom(0x28); //set LCD to 4 bit mode and 2 line configuration
	delay_ms(100); //wait to end next command for stability
	LCD_WriteCom(0x0c); //turns on the display and turns off cursor
	delay_ms(100); //wait to end next command for stability
	LCD_WriteCom(0x06); //sets the increment to right moving and disables display shift
	delay_ms(100); //wait to end next command for stability
	LCD_WriteCom(0x01);// clear screen
	delay_ms(5); //wait to end next command for stability
}

//clears the LCD screen
void LCD_Clear(void){
  LCD_WriteCom(0x1); //clear screen
	delay_ms(5); //delay between commands for stability
}

/*displays text on the LCD, where line is the line number (0 or 1) and 
ptr is a pointer to a C-style string (i.e. null-character terminated)*/
void LCD_DisplayString(unsigned int line, unsigned char *ptr) {
	
	if(line==1){ //check if line 2 is desired
	LCD_WriteCom(0xC0);}//select line 1
	else{LCD_WriteCom(0x80);} //select line 2
	
	//loop to step through pointer string
	for (int ii=0;ii<15;ii++){
		if(ptr[ii]==0x00) //check if character is null
			break; //break if null
		LCD_WriteData(ptr[ii]); //write letter to LCD
	}
}
