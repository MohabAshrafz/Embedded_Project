#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Functions.h"


void Systick_10ms()
{
		NVIC_ST_CTRL_R  = 0x00;												// Disable Systick
		NVIC_ST_RELOAD_R = 160000-1;									// Set reload to wait 10 ms
		NVIC_ST_CURRENT_R = 0;												// Reset Current register
		NVIC_ST_CTRL_R = 0x05;												// Enable timer and set clock
		while((NVIC_ST_CTRL_R & 0x00010000) == 0) {} 	// Wait 10 ms
}

void GenericDelay(unsigned long delay)
{	
		int i;
		for (i=0 ; i < delay ; i++)
		{									// Used to wait more than 10 ms
			Systick_10ms();
		}
}

void Conversion(unsigned int time , int* min , int* sec){
	
	int hour ;
	
	hour = (time/3600);                    						 //calculate hours
		
	*min = (time -(3600 * hour))/60;									//calculate minutes
	
	if ((time-(12*((int)(time/12))))==0 && time!=60) {*sec = (time -(3600 * hour)-(*min * 60));}  // Case C
	
	else {*sec = (time -(3600 * hour)-(*min * 60))/10;}		// ( min : sec)  // Case B
	
}

void Blinking_Buzzer()
{
	int i ;
	for(i = 0 ; i < 6 ; i++)
	{
		GPIO_PORTF_DATA_R ^= 0x0E ;     	 // Toggle LEDs
    GPIO_PORTE_DATA_R ^= 0x10 ;		  	//Toggle buzzer pin4
	  GenericDelay(100);						  	// wait 1 second
	}
	GPIO_PORTF_DATA_R &= ~0x0E;       	//Turn Leds OFF
}

void Display_Timer(unsigned char *timerr){
	
	int i;
	Cursor_Pos(2,6);
	
	for(i=0 ; i<4 ; i++){	
		LCD_write(*timerr);
		GenericDelay(1);
		timerr++;
		if (i == 1) LCD_write(':');     
		}																	
}