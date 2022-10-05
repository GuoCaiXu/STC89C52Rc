# include <reg52.h>
# include <intrins.h>
# define uint unsigned int
# define uchar unsigned char

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

uchar temp;

void delay(uint z);
void main(){
	
	ADDR0 = 0;
	ENLED = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	ADDR3 = 1;
	
	temp = 0xfe;
	P0 = temp;
	
	while(1){
		
		temp = _crol_(temp, 1);
		delay(20000);
		P0 = temp;
	}
}

void delay(uint z){
	
	uint i;
	
	for (i = 0; i < z; i++);
}