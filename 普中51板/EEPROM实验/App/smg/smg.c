# include "smg.h"

//显示数码管函数
void ShowLed(){
    static uchar i;
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