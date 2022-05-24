#include "tm4c123gh6pm.h"
#include "functions.h"
#include "LCD.h"
#include "KPD.h"


void Case_B()
{
	 int weight, min , weight_int , sec ;
	 unsigned char time[4] = {'0','0','0','0'};
	 
	 LCD_cmd(0x01);
	 Cursor_Pos( 1 , 3 );
	 LCD_write_String("Beef Weight?");
	 Cursor_Pos( 2 , 8);
	
	 weight = get_key() ;
	
	if (weight >= '1' && weight <= '9')
	{
		
		LCD_write(weight);
	
    weight_int = weight - '0';      // convert weight to integer value	
	
		GenericDelay(200);	 	// Wait 2 seconds
		LCD_cmd(0x01); 		  	//clear display
	
		Conversion (weight_int*30 , &min , &sec);

		min = min + '0';   															//Convert min to it's Ascii equivalent
		sec = sec + '0';																//Convert sec to it's Ascii equivalent	
		
		time[1] = min;
		time[2] = sec;	

		Cursor_Pos( 1 , 6 );
		LCD_write_String("Time");
		Timer(&time[0]);
    		
	}
	else 
	{
			LCD_cmd(0x01); 
			Cursor_Pos( 1 , 7 );
			LCD_write_String("Err");
		  GenericDelay(200);
			LCD_cmd(0x01);
			Case_B();
	}
}