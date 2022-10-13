#include "reg52.h"
# define uint unsigned int
# define uchar unsigned char
# define ulong unsigned long

sbit Key1 = P3^1;
sbit Key2 = P3^0;
sbit Key3 = P3^2;
sbit Key4 = P3^3;

//小灯
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;

void main(){

    while(1){
        LED1 = Key1;
        LED2 = Key2;
        LED3 = Key3;
        LED4 = Key4;
    }
}