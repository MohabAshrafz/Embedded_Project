#include "tm4c123gh6pm.h"
#include "Ports_Init.h"
#include "Functions.h"

unsigned char symbol[4][4] = 	{{ '1', '2',  '3', 'A'},      //Simulate Keypad
															 { '4', '5',  '6', 'B'},      
															 { '7', '8',  '9', 'C'},      
															 { '*', '0',  '#', 'D'}};



char get_key()
{
	int i,j;
  while(1)
  {
    for(i = 0; i < 4; i++)    //Scan columns loop
    {
      GPIO_PORTC_DATA_R = (1 << (i+4));
      GenericDelay(1);
      for(j = 0; j < 4; j++)  //Scan rows loop
      {
        if((GPIO_PORTA_DATA_R & 0x3C) & (1 << (j+2)))
          return symbol[j][i];
      }
    }
  }
}