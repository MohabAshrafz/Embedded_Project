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
