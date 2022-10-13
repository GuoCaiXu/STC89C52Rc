# include <reg52.h>
# define uint unsigned int

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LEDChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90  //数字0~9
};

unsigned char LEDBuff[6] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  //6个数码管
};

void main(){
	
	uint cnt = 0;  //0.1s的次数
	uint i = 0;  //点亮数码管
	uint sec = 0; //秒数
	
	ADDR3 = 1;
	ENLED = 0;
	
	TMOD = 0x01;  //模式1
	TH0 = 0xfc;  //0.01s
	TL0 = 0x67;  //也可以为0x00 无差别
	
	TR0 = 1; //定时器开启
	
	while(1){
		
		if(TF0 == 1){  //溢出把TF0值0
			
			TF0 = 0;
			TH0 = 0xfc;
			TL0 = 0x67;
			cnt++;
		}
		
		if (cnt >= 1000){ //到达一秒
			
			cnt = 0; //cnt置0
			sec++; //增加一秒
			
			LEDBuff[0] = LEDChar[sec%10];  //0管赋值
			LEDBuff[1] = LEDChar[sec/10%10]; //1管赋值
			LEDBuff[2] = LEDChar[sec/100%10];  //2管赋值
			LEDBuff[3] = LEDChar[sec/1000%10];  //3管赋值
			LEDBuff[4] = LEDChar[sec/10000%10];  //4管赋值
			LEDBuff[5] = LEDChar[sec/100000%10];  //5管赋值
		}
		
		//点亮六个数码管 0.01s间隔
		if (i = 0) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LEDBuff[0];}
		else if (i == 1) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; i++; P0 = LEDBuff[1];}
		else if (i == 2) {ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; i++; P0 = LEDBuff[2];}
		else if (i == 3) {ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; i++; P0 = LEDBuff[3];}
		else if (i == 4) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; i++; P0 = LEDBuff[4];}
		else if (i == 5) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; i = 0; P0 = LEDBuff[5];}
	}
}