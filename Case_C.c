#include "tm4c123gh6pm.h"
#include "functions.h"
#include "LCD.h"
#include "KPD.h"

void Case_C()
{
	int weight, min, sec , sec1 ,  sec10 , weight_int ; 
	unsigned char time[] = {'0','0','0','0'};
		LCD_cmd(0x01);
		Cursor_Pos( 1 , 2 );
		LCD_write_String("Chicken Weight?");
		Cursor_Pos( 2 , 7 );
		weight = get_key() ;
	
	if (weight >= '1' && weight <= '9')
{
		
		LCD_write(weight);
	
    weight_int = weight - '0';

		GenericDelay(200);  								//wait 2 seconds
		LCD_cmd(0x01); 											//clear display
		
		Conversion (weight_int*12 , &min , &sec);										// 0 min : sec10 sec1
	
    min = min + '0';   																				//Convert min to it's Ascii equivalent
		
		sec10 = (int)(sec/10) + '0';
		sec1 = sec -((int)(sec/10))*10 + '0';
		
		time[1] = min;
		time[2] = sec10;
		time[3] = sec1;
	
		Cursor_Pos( 1 , 6 );
		LCD_write_String("Time");
		Display_Timer(&time[0]);
		while( (GPIO_PORTF_DATA_R & 0x01) != 0){}	   		//wait untill second switch is pressed
		Timer(&time[0]);
	
	}

		else 
		{			
			LCD_cmd(0x01); 
			Cursor_Pos( 1 , 7 );
			LCD_write_String("Err");
		  GenericDelay(200);
			Case_C();
		}
	}
