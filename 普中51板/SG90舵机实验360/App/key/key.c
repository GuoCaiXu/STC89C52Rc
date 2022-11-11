# include "key.h"

u8 sta[2] = {1,1};
u8 bac[2] = {1,1};

//判断函数是否按下
void key_Judgement(){
    u8 buf[2] = {1,1};
    u8 i = 0;

    buf[0] = KEY1;
    buf[1] = KEY2;

    for (i = 0; i < 2; i++){
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
        if (time <= 3){
            time += 2;
        }
    }
    else if(key == 2){
        if (time >= 2){
            time -= 2;
        }
    }
}