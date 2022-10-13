#include <reg52.h>
# include <intrins.h>
# define uchar unsigned char
# define uint unsigned int


void delay_10us(uint z)
{
	while(z--);	
}

void main()
{	
   	char dir =0;
    uchar LED = 0x01;
	
	while(1)
	{
        P2 = ~LED;
		delay_10us(50000);
		if (dir == 0){
            LED = _crol_(LED,1);
            if (LED == 0x80) dir = 1;
        }
        else {
            LED = _cror_(LED,1);
            if (LED == 0x01) dir = 0;
        }
	}		
}