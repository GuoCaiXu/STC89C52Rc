# include <reg52.h>
//typedef unsigned int uint;
# define uint unsigned int

sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;
sbit LED8 = P0^7;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void Delay();
void main(){
		ADDR3 = 1;
		ENLED = 0;
		ADDR0 = 0;
		ADDR1 = 1;
		ADDR2 = 1;
		while(1)
		{
			
			LED1 = 0;
			Delay();
			LED2 = 0;
			LED1 = 1;
			Delay();
			
			LED3 = 0;
			LED2 = 1;
			Delay();
			
			LED4 = 0;
			LED3 = 1;
			Delay();
			
			LED5 = 0;
			LED4 = 1;
			Delay();
			
			LED6 = 0;
			LED5 = 1;
			Delay();
			
			LED7 = 0;
			LED6 = 1;
			Delay();
			
			LED8 = 0;
			LED7 = 1;
			Delay();
			
			LED7 = 0;
			LED8 = 1;
			Delay();
			
			LED6 = 0;
			LED7 = 1;
			Delay();
			
			LED5 = 0;
			LED6 = 1;
			Delay();
			
			LED4 = 0;
			LED5 = 1;
			Delay();
			
			LED3 = 0;
			LED4 = 1;
			Delay();
			
			LED2 = 0;
			LED3 = 1;
			Delay();
			
			LED1 = 0;
			LED2 = 1;
			Delay();
			
		}
}

void Delay(){
	
	uint i;
	
	for (i = 0; i < 30000; i++);
}