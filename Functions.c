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


int Check_Switch(){
					
		int SW12_in;
	
		SW12_in =  GPIO_PORTF_DATA_R & 0x11; 	//Read Input from Switches 1&2
	
				switch (SW12_in){
						
					case 0x01:						//SW1 is pressed		
								return 1;					      																
					case 0x10:						//SW2 is pressed
								return 2;				   
					default:
						return 0;									
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



void Timer(unsigned char *timerr)
{
	unsigned char time[4];           //Array of time
	int i , j, k, check = 5;
		
	for(i=0 ; i<4; i++)							//get the array of time to display
	{			
		time[i] = *timerr;						
		timerr++; 	
	}
		
	
	
	if((GPIO_PORTE_DATA_R & 0x20) == 0)			// Check if the door is open
	{	
		LCD_cmd(0x01);												//Clear LCD
		Cursor_Pos(1,2);
		LCD_write_String("Door is Open");
		Display_Timer(&time[0]);
	}
	
	while ((GPIO_PORTE_DATA_R & 0x20) == 0)  // wait until the door is closed After SW2 is pressed
	{
		
	}			
		
	LCD_cmd(0x01);												//Clear LCD
	Cursor_Pos(1,4);
	LCD_write_String("Cooking...");
	GPIO_PORTF_DATA_R |= 0x0E;						// Turn On LEDs
	
	for (; time[0] >= '0'; time[0]--)
	{
		Cursor_Pos(2,6);
		LCD_write(time[0]);												//Display Min10				
		
		for(; time[1] >= '0'; time[1]--)					
		{
			Cursor_Pos(2,7);
			LCD_write(time[1]);											//Display Min1
			if(check == 5) LCD_write(':');
				
			for(; time[2] >= '0'; time[2]--)
			{		
				Cursor_Pos(2,9);
				LCD_write(time[2]);										//Display Sec10
					
				for(; time[3] >= '0'; time[3]--)
				{										
					Cursor_Pos(2,10);					
					LCD_write(time[3]);									//Display Sec1	
									
					for(j = 0 ; j < 100 ; j++)					// to wait 1 sec
					{		
						GenericDelay(1);
						check = Check_Switch();
						
						if ( (GPIO_PORTE_DATA_R & 0x20) == 0)				// Check the door in open or closed
						{
							LCD_cmd(0x01);														// Clear LCD
							Cursor_Pos(1,2);
							LCD_write_String("Door is Open");					// Warning that the door is open
							Display_Timer(&time[0]);									// Display the Remaining Time
							while(1)
								{	
									for (k = 0 ; k < 75; k++ ){						
										GenericDelay(1);												
										if ((GPIO_PORTE_DATA_R & 0x20) != 0)					// the door is closed
											{
												LCD_cmd(0x01);														// Clear LCD
												Cursor_Pos(1,4);
												LCD_write_String("Cooking...");						// Cooking is Resumed
												Display_Timer(&time[0]);
												GPIO_PORTF_DATA_R |= 0x0E;								//Turn ON LEDs
												break;																					
											}											 
										}		
									if ((GPIO_PORTE_DATA_R & 0x20) != 0 ) break ;										
									GPIO_PORTF_DATA_R ^= 0x0E;											// Blinkking LEDs
								}
						}
							
						if (check == 1)             								// Check if SW1 is Pressed for first time
						{	
							LCD_cmd(0x01);													// Clear LCD
							Cursor_Pos(1,6);	
							LCD_write_String("Paused");						//Pause Cooking
							Display_Timer(&time[0]);					   //Display the Remaining Time
							GenericDelay(25);
							
							while(1)
							{
								for (k = 0 ; k < 75; k++ )
								{
									GenericDelay(1);						
									check = Check_Switch();
					
									if (check == 1 )													 		// Check if SW1 is Pressed for second time
									{
										GPIO_PORTF_DATA_R &= ~0x0E;						 	 	// Turn OFF LEDs
										LCD_cmd(0x01);													 // Clear LCD
										main();																 	// Back to start again
									}						
									else if ( check == 2) break; 							// Check if SW2 is Pressed after SW1 is Pressed first time
								}
							
								if (check == 2)															// Check if SW2 is Pressed after SW1 is Pressed first time
								{ 
									LCD_cmd(0x01);													// Clear LCD
									Cursor_Pos(1,4);
									LCD_write_String("Cooking...");				/// Resume Cooking
									Display_Timer(&time[0]);
									GPIO_PORTF_DATA_R |= 0x0E;							// Turn ON LEDs
									break;
								}
								GPIO_PORTF_DATA_R ^= 0x0E;								// Blinkking LEDs
							}
						}
					}					
				}			
					time[3] = '9';		
			}
				time[2] = '5';
		}
		  time[1] = '9';
	}
		LCD_cmd(0x01); 												// Clear LCD after timer has counted down to zero
		Cursor_Pos(1,5);
		LCD_write_String("Finished");
		Blinking_Buzzer();								 // Flash LEDs and Buzzer 3 times
		LCD_cmd(0x01); 
		
}
