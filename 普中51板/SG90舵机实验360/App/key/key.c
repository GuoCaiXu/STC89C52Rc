# include "key.h"

u8 sta[3] = {1,1,1};
u8 bac[3] = {1,1,1};

//判断函数是否按下
void key_Judgement(){
    u8 buf[3] = {1,1,1};
    u8 i = 0;

    buf[0] = KEY1;
    buf[1] = KEY2;
    buf[2] = KEY3;

    for (i = 0; i < 3; i++){
        if (buf[i] == 0){
            sta[i] = 0;
        }
        else if (buf[i] == 1){
            sta[i] = 1;
        }
    }
}

//按键功能
void key_fun(u8 key){
    if (key == 1){
        time = 5;
    }
    else if (key == 2){
        time = 15;
    }
    else if (key == 3){
        time = 25;
    }
}