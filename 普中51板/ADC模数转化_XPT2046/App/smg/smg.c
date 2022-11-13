# include "smg.h"

//共阴数码管 数字0~9
u8 code LedChar[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f };  //数字0~9

//数码管缓冲区
u8 LedBuff[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//显示数码管
void smg_ShowLed(){
    static u8 i = 0;

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

//显示有效位
void smg_ShowNum(u16 num){

    signed char i;
    u8 arr[8];

    for (i = 1; i < 8; i++){
        arr[i] = num % 10;
        num /= 10;
    }
    for (i = 7; i >= 2; i--){
        if (arr[i] == 0) LedBuff[i] = 0x00;
        else break;
    }
    for (; i >= 1; i--){
        LedBuff[i] = LedChar[arr[i]];
    }
    LedBuff[0] = 0x3e;
    LedBuff[2] |= 0x80;
}