# include "key.h"

uchar KeySta[] = {1,1,1,1};

//判断按键是否按下
uchar key_JudKey(){
    uchar KeyBac[] = {1,1,1,1};
    uchar i;
    uchar n;
    for (i = 0; i < 4; i++){
        if (KeyBac[i] != KeySta[i]){
            if (KeyBac[i] != 0){
                n = i+1;
            }
            KeyBac[i] = KeySta[i];
        }
    }
    return n;
}

//按键消抖
void key_Vanish(){

    uchar KeyBuf[] = {1,1,1,1};
    uchar i;
    
    KeyBuf[0] = KEY1;
    KeyBuf[1] = KEY2;
    KeyBuf[2] = KEY3;
    KeyBuf[3] = KEY4;

    for (i = 0; i < 4; i++){
        if (KeyBuf[i] == 0){
            KeySta[i] = 0;
        }
        else if (KeyBuf[i] == 1){
            KeySta[i] = 1;
        }
    }
}