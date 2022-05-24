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
		
		void PortC_Init(){														// PortC --> Keypad output
			
		SYSCTL_RCGCGPIO_R |= 0x04;   						 	  	//Enable Port C clock
		while ((SYSCTL_PRGPIO_R & 0x04) == 0) {}; 		//Check that portC is enabled
		GPIO_PORTC_LOCK_R = 0x4C4F434B;  							//Unlock Port C
		GPIO_PORTC_CR_R |=0xF0; 									  	//Allow changes in port PC4567
		GPIO_PORTC_PCTL_R &= ~0xFFFF0000;							//Set pins to GPIO
		GPIO_PORTC_DIR_R |= 0xF0;								  		//Set output pins
		GPIO_PORTC_AFSEL_R &= ~0xF0;									//Disable alternate functions
		GPIO_PORTC_AMSEL_R &= ~0xF0;									//Disable analog functions
		GPIO_PORTC_DEN_R |= 0xF0;											//Enable Digital Pins PC4567
		}
		
		void PortB_Init(){    												//PortB --> LCD Data
			
		SYSCTL_RCGCGPIO_R |= 0x00000002;							//Enable Port B clock
  while ((SYSCTL_PRGPIO_R&0x02) == 0){};					//Wait untill portB is enabled
	GPIO_PORTB_LOCK_R = 0x4C4F434B;									//Unlock Port B
	GPIO_PORTB_CR_R |= 0xFF;												//Allow changes in port PB01234567
	GPIO_PORTB_DIR_R = 0xFF;												//Set output pins
	GPIO_PORTB_DEN_R = 0xFF;												//Enable Digital Pins PB01234567
	GPIO_PORTB_AMSEL_R = 0x00;											//Disable analog functions
	GPIO_PORTB_AFSEL_R = 0x00; 											//Disable alternate functions
	GPIO_PORTB_PCTL_R = 0x00000000;									//Set pins to GPIO
  GPIO_PORTB_PUR_R = 0x00;												//Disable Pull up resistor 

		}		
		
		void PortE_Init(){		    									//PortE --> LCD Control (123) / Buzzer (4) / SW3 (5)
			
		SYSCTL_RCGCGPIO_R |= 0x00000010;						//Enable Port E clock
  while ((SYSCTL_PRGPIO_R&0x10) == 0){};				//Wait untill portE is enabled
	GPIO_PORTE_LOCK_R = 0x4C4F434B;								//Unlock Port E
	GPIO_PORTE_CR_R |= 0x3E;											//Allow changes in port PE12345
	GPIO_PORTE_DIR_R = 0x1E;											//Set output pins PE1234
	GPIO_PORTE_DEN_R = 0x3E;											//Enable Digital Pins PE12345
	GPIO_PORTE_AMSEL_R = 0x00;										//Disable analog functions
	GPIO_PORTE_AFSEL_R = 0x00;										//Disable alternate functions
	GPIO_PORTE_PCTL_R = 0x00000000;								//Set pins to GPIO
  GPIO_PORTE_PUR_R = 0x20; 											//Enable Pull up resistor for SW3
		
		}
