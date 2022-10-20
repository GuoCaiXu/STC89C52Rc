//外部中断0
# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int
# define ulong unsigned long 

sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

uchar code LedChar[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar LedBuff[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uchar flag = 0;

void ShowLed(ulong num);
void main(){

ulong cnt = 0;
    ADDR0 = 0;
    ADDR1 = 0;
    ADDR2 = 0;
    
    EA  = 1;
    TMOD = 0x10;
    TH1 =0xfc;
    TL1 = 0x66;
    ET1 = 1;
    TR1 = 1;
    P0 = 0x00;

    while(1){
        if (flag == 1){
            flag = 0;
            ShowLed(cnt);
            cnt++;
        }
    }
}

void ShowLed(ulong num){
    signed char i;
    uchar a[8];
    for (i = 0; i < 8; i++){
        a[i] = num % 10;
        num /= 10;
    }
    for (i = 7; i >= 1; i--){
        if (a[i] == 0) LedBuff[i] = 0x00;
        else break;
    }
    for (; i >= 0; i--){
        LedBuff[i] = LedChar[a[i]];
    }
}

void InterruptTime1() interrupt 3{
    static uint sec = 0;
    static uchar i = 0;
    
    TH1 = 0xfc;
    TL1 = 0x66;
    sec++;
    if (sec >= 1000){
        sec = 0;
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
    }
}