# include <reg52.h>
# define uint unsigned int
# define uchar unsigned char

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LEDChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};

unsigned char LEDBuff[6] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};

	uint cnt = 0;  
	uint i = 0;
  uchar flagls = 0;

void main(){
	
	unsigned long sec = 1000000;
	
	ADDR3 = 1;
	ENLED = 0;
	
	EA = 1;
	TMOD = 0x01;  
	TH0 = 0xFC; 
	TL0 = 0x00;
	
	ET0 = 1;
	TR0 = 1; 
	
	while(1){
		
		if (flagls == 1){ 
			
			flagls = 0; 
			sec--; 
			
			LEDBuff[0] = LEDChar[sec%10];  //0???
			LEDBuff[1] = LEDChar[sec/10%10]; //1???
			LEDBuff[2] = LEDChar[sec/100%10];  //2???
			LEDBuff[3] = LEDChar[sec/1000%10];  //3???
			LEDBuff[4] = LEDChar[sec/10000%10];  //4???
			LEDBuff[5] = LEDChar[sec/100000%10];  //5???
		}
  }
}

void InterruptTimer0() interrupt 1{  //x * 8 + 3 = 11  0x
	
	TH0 = 0xfc;
	TL0 = 0x00;
	cnt++;
	
	if (cnt >= 1000){
		cnt = 0;
		flagls = 1;
	}
	
	P0 = 0xff;
	switch(i){
	
		  case 0: ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LEDBuff[0]; break;
			case 1: if (LEDBuff[1] != 0xC0){ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; P0 = LEDBuff[1];} i++; break;
			case 2: if (LEDBuff[2] != 0xC0){ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; P0 = LEDBuff[2];} i++; break;
			case 3: if (LEDBuff[3] != 0xC0){ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; P0 = LEDBuff[3];} i++; break;
			case 4: if (LEDBuff[4] != 0xC0){ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; P0 = LEDBuff[4];} i++; break;
			case 5: if (LEDBuff[5] != 0xC0){ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; P0 = LEDBuff[5];} i=0; break;
			default: break;
	}
}