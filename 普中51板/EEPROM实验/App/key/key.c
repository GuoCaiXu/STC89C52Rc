# include "key.h"

//判断按键
uchar KeySta[] = {1,1,1,1};

//判断按键是否按下函数
uchar JudKey(){

    static uchar KeyBac[] = {1,1,1,1};
    uchar i;
    uchar n;
    for (i = 0; i < 4; i++){
    if (KeyBac[i] != KeySta[i]){
        if (KeyBac[i] != 0){
            n = i;
        }
        KeyBac[i] = KeySta[i];
    }
    }
    return n+1;
}

//消抖按键函数
void ShakeKey(){

    uchar LedBuf[] = {1,1,1,1};
    uchar i;

    LedBuf[0] = KEY1;
    LedBuf[1] = KEY2;
    LedBuf[2] = KEY3;
    LedBuf[3] = KEY4;

    for (i = 0; i < 4; i++){
        if (LedBuf[i] == 0){
            KeySta[i] = 0;
        }
        else if (LedBuf[i] == 1){
            KeySta[i] = 1;
        }
    }
}