# include "smg.h"

//共阴数码管数字0~9
uchar code LedChar[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f };

//数码管缓存区
uchar LedBuff[]  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//显示数码管
void smg_ShowLed(){
    static uchar i = 0;

    //消去重影
    P0 = 0x00;
    switch(i){
        case 0 : ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[0]; break;
        case 1 : ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[1]; break;
        case 2 : ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[2]; break;
        case 3 : ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[3]; break;
        case 4 : ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[4]; break;
        case 5 : ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[5]; break;
        case 6 : ADDR0 = 0; ADDR1 = 1; ADDR2 = 1; i++; P0 = LedBuff[6]; break;
        case 7 : ADDR0 = 1; ADDR1 = 1; ADDR2 = 1; i=0; P0 = LedBuff[7]; break;
    }
}

//计算数码管的显示内容和显示有效位
void smg_CopLed(ulong num){
    ichar i;
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