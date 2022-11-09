# include "smg.h"

//共阴数码管数字0~9
u8 code LedChar[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f };

//数码管缓存区
u8 LedBuff[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//ds1302 时间数据
u8 time[7];

//显示数码管
void smg_ShowLed(){
    u8 i = 0;

    for (i = 0;i < 8;){
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
}

//返回时间初始化数字
void smg_turn(){
    u8 i = 0;

    for (i = 0; i < 7; i++){
        time[i] = ds1302_turn();
    }
}

//运行时间
void smg_run(){

    time[0]++;

    if (time[0] == 0x59)    {
        time[0] = 0;
        time[1]++;
    }
    if (time[1] == 0x59){
        time[1] = 0;
        time[2]++;
    }
    if (time[2] == 0x24){
        time[2] = 0;
    }
}

//显示时间数字
void smg_ShowNum(){

        LedBuff[7] = LedChar[time[2]/16];
        LedBuff[6] = LedChar[time[2]%16];
        LedBuff[5] = 0x40;
        LedBuff[4] = LedChar[time[1]/16];
        LedBuff[3] = LedChar[time[1]%16];
        LedBuff[2] = 0x40;
        LedBuff[1] = LedChar[time[0]/16];
        LedBuff[0] = LedChar[time[0]%16];
}