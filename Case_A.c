#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Functions.h"

void Case_A()
{
		unsigned char time[] = {'0','1','0','0'};				
		LCD_cmd(0x01);															//Clear Display
		Cursor_Pos(1,5);

		LCD_write_String("Popcorn"); 
		Display_Timer(&time[0]);										//Display Timer
		
		while( (GPIO_PORTF_DATA_R & 0x01) != 0){}			//wait untill second switch is pressed
		Timer(&time[0]);

}

