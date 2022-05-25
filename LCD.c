#include "tm4c123gh6pm.h"
#include "Ports_Init.h"
#include "Functions.h"

void LCD_cmd(unsigned char cmd){				//Configure LCD
	
	GPIO_PORTB_DATA_R=cmd;
	
	GPIO_PORTE_DATA_R=(0<<1)|(0<<2)|(1<<3);
	GenericDelay(1);
	GPIO_PORTE_DATA_R=(0<<1)|(0<<2)|(0<<3);
	GenericDelay(3);
	
}

void LCD_Init (void)                     
{
	 
	LCD_cmd(0x38);								//Function Set 
	GenericDelay(3);
	
	LCD_cmd(0x06);								//Entry Mode Set 
	GenericDelay(3);
	
	LCD_cmd(0x0F);								//Display ON OFF Control 
	GenericDelay(3);
	
	LCD_cmd(0x01);								//Clear Display
	GenericDelay(3);
														
	LCD_cmd(0x02);								//Return Home 
	GenericDelay(3);
	
}

void LCD_write(unsigned char data){				//Display Char
	
	GPIO_PORTB_DATA_R=data;
	
	GPIO_PORTE_DATA_R=(1<<1)|(0<<2)|(1<<3);
	GenericDelay(1);
	GPIO_PORTE_DATA_R=(1<<1)|(0<<2)|(0<<3);
	GenericDelay(3);

}

void LCD_write_String(char *Str)      		//Display String     
{
	while(*Str)
	{
		LCD_write(*Str);
		Str++;
	}
}
	
void Cursor_Pos(unsigned char row , unsigned char pos)   //change position of Cursor
	{
		
	if (row == 1 ) LCD_cmd(0x80 + (pos-1) );   						 //first row 
	else if (row == 2)  LCD_cmd(0xC0 + (pos-1) );          // second row 
	
}
