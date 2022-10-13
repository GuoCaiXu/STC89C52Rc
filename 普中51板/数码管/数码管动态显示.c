#include "reg52.h"
# define uint unsigned int
# define uchar unsigned char
# define ulong unsigned long

sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

uchar code LedChar[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f };  //数字0~9
uchar LedBuff[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uchar flag = 0;
uint cnt = 0;
uchar i = 0;

void main(){
ulong sec = 0;
	
    EA = 1;
    TMOD = 0x01;
    TH0 = 0xfc;
    TL0 = 0x66;
    ET0 = 1;
    TR0 = 1;

    while(1){

        if (flag == 1){
            flag = 0;
					  sec++;
					
            LedBuff[0] = LedChar[sec%10];
			LedBuff[1] = LedChar[sec/10%10];
			LedBuff[2] = LedChar[sec/100%10]; 
			LedBuff[3] = LedChar[sec/1000%10]; 
			LedBuff[4] = LedChar[sec/10000%10];  
			LedBuff[5] = LedChar[sec/100000%10]; 
			LedBuff[6] = LedChar[sec/1000000%10];  
			LedBuff[7] = LedChar[sec/10000000%10]; 
        }
    }
}

void InterruptTime0() interrupt 1{

    TH0 = 0xfc;
    TL0 = 0x66;

    cnt++;
    if (cnt >= 1000){
        cnt = 0;
        flag = 1;
    }

    P0 = 0x00;
    switch(i){
        case 0: ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[0]; break;
        case 1: ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[1]; break;
        case 2: ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[2]; break;
        case 3: ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[3]; break;
        case 4: ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[4]; break;
        case 5: ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[5]; break;
        case 6: ADDR0 = 0; ADDR1 = 1; ADDR2 = 1; i++; P0 = LedBuff[6]; break;
        case 7: ADDR0 = 1; ADDR1 = 1; ADDR2 = 1; i=0; P0 = LedBuff[7]; break;
        default: break;
    }

}