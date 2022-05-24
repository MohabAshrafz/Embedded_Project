#include "tm4c123gh6pm.h"
#include "Ports_Init.h"
#include "Functions.h"

void LCD_cmd(unsigned char cmd){
	
	GPIO_PORTB_DATA_R=cmd;
	
	GPIO_PORTE_DATA_R=(0<<1)|(0<<2)|(1<<3);
	GenericDelay(1);
	GPIO_PORTE_DATA_R=(0<<1)|(0<<2)|(0<<3);
	GenericDelay(3);
	
}

void LCD_Init (void)                     
{
	// Function Set  
	LCD_cmd(0x38);
	GenericDelay(3);
	
	// Entry Mode Set  
	LCD_cmd(0x06);
	GenericDelay(3);
	
	// Display ON OFF Control 
	LCD_cmd(0x0F);
	GenericDelay(3);
	
	// Clear Display
	LCD_cmd(0x01);
	GenericDelay(3);
	
	// Return Home 
	LCD_cmd(0x02);
	GenericDelay(3);
	
}

void LCD_write(unsigned char data){
	
	GPIO_PORTB_DATA_R=data;
	
	GPIO_PORTE_DATA_R=(1<<1)|(0<<2)|(1<<3);
	GenericDelay(1);
	GPIO_PORTE_DATA_R=(1<<1)|(0<<2)|(0<<3);
	GenericDelay(3);

}

void LCD_write_String(char *Str)           
{
	while(*Str)
	{
		LCD_write(*Str);
		Str++;
	}
}
	
void Cursor_Pos(unsigned char row , unsigned char pos)
	{
		
	if (row == 1 ) LCD_cmd(0x80 + (pos-1) );   						 //first row 
	else if (row == 2)  LCD_cmd(0xC0 + (pos-1) );          // second row 
	
}
