# include "key.h"

u8 key_gtim_h = 0;
u8 key_gtim_l = 0;
u8 KeySta[2] = {1,1};
u8 KeyBac[2] = {1,1};

//判断按键是否按下
u8 key_Judgement(){
    u8 i = 0;
    u8 key = 0;

    for (i = 0; i < 2; i++){
        if (KeySta[i] != KeyBac[i]){
            if (KeyBac[i] != 0){
                key = i+1;
            }
            KeyBac[i] = KeySta[i];
        }
    }
    return key;
}

//中断函数
void key_pick() {
    u8 KeyBuf[2] = {1,1};
    u8 i = 0;
    
    KeyBuf[0] = KEY1;
    KeyBuf[1] = KEY2;

    for (i = 0; i < 2; i++){
        if (KeyBuf[i] == 0) KeySta[i] = 0;
        else if (KeyBuf[i] == 1) KeySta[i] = 1;
    }
}