#include "tm4c123gh6pm.h"


void SystemInit(){																//initialize Port F
	
		SYSCTL_RCGCGPIO_R |= 0x20;   							  	//Enable Port F clock
		while ((SYSCTL_PRGPIO_R & 0x20) == 0) {}; 		//Check that portF is enabled
		GPIO_PORTF_LOCK_R = 0x4C4F434B;  							//Unlock Port F
		GPIO_PORTF_CR_R |=0x1F; 											//Allow changes in port PF01234
		GPIO_PORTF_PCTL_R &= ~0x000FFFFF;							//Set pins to GPIO
		GPIO_PORTF_DIR_R |= 0x0E;											//Set output pins
		GPIO_PORTF_DIR_R &= ~0x11;										//Set input pins
		GPIO_PORTF_AFSEL_R &= ~0x1F;									//Disable alternate functions
		GPIO_PORTF_AMSEL_R &= ~0x1F;									//Disable analog functions
		GPIO_PORTF_PUR_R |= 0x11;											//Enable Pull up resistor for switches
		GPIO_PORTF_DEN_R |= 0x1F;											//Enable Digital Pins PF01234
		GPIO_PORTF_DATA_R &= ~0x0E;										//Initialize LEDs to be off
		}


		void PortA_Init(){                 					 	// PortA --> Keypad input
			
		SYSCTL_RCGCGPIO_R |= 0x01;   						 	  	//Enable Port A clock
		while ((SYSCTL_PRGPIO_R & 0x01) == 0) {}; 		//Check that portF is enabled
		GPIO_PORTA_LOCK_R = 0x4C4F434B;  							//Unlock Port A
		GPIO_PORTA_CR_R |=0x3C; 									  	//Allow changes in port PA2345
		GPIO_PORTA_PCTL_R &= ~0x00FFFF00;							//Set pins to GPIO
		GPIO_PORTA_DIR_R &= ~0x3C;										//Set input pins
		GPIO_PORTA_AFSEL_R &= ~0x3C;									//Disable alternate functions
		GPIO_PORTA_AMSEL_R &= ~0x3C;									//Disable analog functions
		GPIO_PORTA_PDR_R |= 0x3C;  										//Enable Pulldown Resistors
		GPIO_PORTA_DEN_R |= 0x3C;											//Enable Digital Pins PA2345
		GPIO_PORTA_DATA_R &= ~0x00;										//Initialize Data Register to be 0 
		}