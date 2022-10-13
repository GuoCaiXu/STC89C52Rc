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
uchar i;
uchar arr[8];
	
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
        case 0: if (LedBuff[0] != 0x3f) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; P0 = LedBuff[0];} i++; break;
        case 1: if (LedBuff[1] != 0x3f) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; P0 = LedBuff[1];} i++; break;
        case 2: if (LedBuff[2] != 0x3f) {ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; P0 = LedBuff[2];} i++; break;
        case 3: if (LedBuff[3] != 0x3f) {ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; P0 = LedBuff[3];} i++; break;
        case 4: if (LedBuff[4] != 0x3f) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; P0 = LedBuff[4];} i++; break;
        case 5: if (LedBuff[5] != 0x3f) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; P0 = LedBuff[5];} i++; break;
        case 6: if (LedBuff[6] != 0x3f) {ADDR0 = 0; ADDR1 = 1; ADDR2 = 1; P0 = LedBuff[6];} i++; break;
        case 7: if (LedBuff[7] != 0x3f) {ADDR0 = 1; ADDR1 = 1; ADDR2 = 1; P0 = LedBuff[7];} i=0; break;
        default: break;
    }

}