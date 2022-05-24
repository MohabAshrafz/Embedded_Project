#include "tm4c123gh6pm.h"
#include "Ports_Init.h"
#include "KPD.h"
#include "LCD.h"
#include "Functions.h"
#include "Cases.h"

char Case;

int main(){
	
		SystemInit(); 			//portf initialization
	  PortA_Init();
		PortC_Init();
		PortB_Init();
		PortE_Init();
	  LCD_Init ();
	
	while(1){
		
		LCD_write_String("Insert Key: ");			
		Case = get_key();
		Cursor_Pos(1,13);
		LCD_write(Case);
		
		switch (Case){
			
			case 'A':
				Case_A();
				break;
			
			case 'B':
				Case_B();
				break;
			
			case 'C':
				Case_C();
				break;
			
			case 'D':
				Case_D();
			
				break;
			
			default:
				LCD_cmd(0x01);	
				LCD_write_String("Incorrect Option");
				GenericDelay(100);
				LCD_cmd(0x01);
				break;
			
		}
		
	}

}
