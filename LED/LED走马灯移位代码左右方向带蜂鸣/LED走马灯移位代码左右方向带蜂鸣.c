# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit BUZZ = P1^6;

void delay(uint z);
void main(){
	
	uchar temp = 0x01;
	uchar dir = 0;
	
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	BUZZ = 0;
	
	while(1){
		
		P0 = ~temp;
		delay(20000);
		
		if (dir == 0){
			
			temp = temp << 1;
			if (temp == 0x80){
				
				dir = 1;
			}
		}
		else{
			
			temp = temp >> 1;
			if (temp == 0x01){
				
				dir = 0;
			}
		}
	}	
}

void delay(uint z){
	
	uint i;
	
	for (i = 0; i < z; i++);
}