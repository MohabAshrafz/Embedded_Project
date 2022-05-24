#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Functions.h"

void Case_A()
{
		unsigned char time[] = {'0','1','0','0'};				
		LCD_cmd(0x01);
		Cursor_Pos(1,5);

		LCD_write_String("Popcorn"); 
		Display_Timer(&time[0]);
		
		while( (GPIO_PORTF_DATA_R & 0x01) != 0){}		
		Timer(&time[0]);

}

