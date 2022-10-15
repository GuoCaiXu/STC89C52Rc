#include "reg52.h"
# define uint unsigned int
# define uchar unsigned char
# define ulong unsigned long

sbit Key1 = P3^1;

sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

uchar code LedChar[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //数字0~9
uchar LedBuff[] =      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //数码管缓冲区
uchar KeySta = 1;

void KeyAction(ulong num);
void main(){

   uchar KeyBac = 1;
   ulong num = 0;

    EA = 1; //打开使能总中断 1开启
    TMOD = 0x01;  //工作模式1
    TH0 = 0xfc;  //0.001s 也就是1毫秒 fc66也就是1毫秒
    TL0 = 0x66;
    ET0 = 1;  //T0使能中断开启
    TR0 = 1;  //定时器T0开启
    LedBuff[0] = LedChar[0];
    while(1){

        //判断按键是否按下
    if (KeyBac != KeySta){
    if (KeyBac == 0){
        num++;
        //给数码管取个位值函数
        KeyAction(num);
    }
    KeyBac = KeySta;
   }
   }

}

void KeyAction(ulong num){

   signed char i;
   uchar arr[8];
    for (i = 0; i < 8; i++){
        arr[i] = num % 10;
        num /= 10;
    }
    for (i = 7; i >= 1; i--){
        if (arr[i] == 0) LedBuff[i] = 0x00;
        else break;
    }
    for (; i >= 0; i--){
        LedBuff[i] = LedChar[arr[i]];
    }
}

//中断函数
void InterruptTime0() interrupt 1{
    static uchar KeyBuf = 0xff;

    static uchar i = 0;

    TH0 = 0xfc;
    TL0 = 0x66; 
    
     if (Key1 == 0x00){
        KeySta = 0;
    }
     else if (Key1 == 0x0f){
        KeySta = 1;
     }
     
     P0 = 0x00;  //消抖

     //显示数码管
     switch (i){
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