#include "Functions.h"
#include "LCD.h"
#include "KPD.h" 

void Case_D()
{
	unsigned char time[4] = { '0' , '0' , '0' , '0' }; 
	int i ;
	
	LCD_cmd(0x01);
	Cursor_Pos(1,2);
	LCD_write_String("Cooking Time?");
	
  Cursor_Pos(2,6);
	Display_Timer(&time[0]);
	
	for(i = 0 ;  i < 4 ; i++ )
	{
		time[i] = get_key();
		GenericDelay(30);
		
		if (time[i] < '0'  ||  time[i] > '9' )
		{			
			LCD_cmd(0x01);
			Cursor_Pos(1,2);		
			LCD_write_String("Invalid input");
			GenericDelay(200);
			LCD_cmd(0x01);
			Case_D();
		}
		
		Cursor_Pos(2,10);
		LCD_write(time[i]);
		
		if ( i == 1){
		Cursor_Pos(2,9);
		LCD_write(time[i-1]);
		LCD_write(time[i]);
		}
		if (i == 2){
		Cursor_Pos(2,7);
		LCD_write(time[i-2]);
		Cursor_Pos(2,9);
		LCD_write(time[i-1]);
		LCD_write(time[i]);
		}
		if (i == 3){
		Cursor_Pos(2,6);
		LCD_write(time[i-3]);
		LCD_write(time[i-2]);
		Cursor_Pos(2,9);
		LCD_write(time[i-1]);
		LCD_write(time[i]);
		}
	}
	
	if (time[0] > '3' || ( time[1] < '1' && time[0] == '0' ) || ( time[0] == '3' && (time[1] > '0' || time[2] > '0' || time[3] > '0' )) )   //Invalid Time 
		{			
			LCD_cmd(0x01);
			Cursor_Pos(1,2);		
			LCD_write_String("Invalid Time");
			GenericDelay(300);
			LCD_cmd(0x01);
			Case_D();
		}
	
		while(1){
		
			if (Check_Switch() == 1) Case_D();						//Reset Time
			if (Check_Switch() == 2) Timer(&time[0]);			//Confirm Time
		
		}
	
}
