# include "hs0038.h"

u8 gired[4];

//红外遥控初始化
void hs0038_ired_init(){

    //外部中断0 中断开启
    IT0 = 1;

    //开启外部中断0
    EX0 = 1;

    //IRED 拉高电平 初始化端口
    IRED = 1;
}

//ired初始化函数
void ired() interrupt 0{
    u16 time_cnt = 0;
    u8 i = 0, j = 0;
    u8 ired_high_time = 0;

    if (IRED == 0){
        //10ms 限制条件
        time_cnt = 1000;

        while((!IRED) && (time_cnt)){
            //延时10 us
            delay_us(1);
            time_cnt --;
            if (time_cnt == 0) return;
            //cnt 减一次延迟10us 当cnt = 0 时， 也就是10ms 超过9ms 低电平 认为是一个错误信号
        }

        //判断 ired 拉高电平4.5ms
        if (IRED){
            time_cnt = 500;
            while(IRED && time_cnt){
                delay_us(1);
                time_cnt --;
                if (time_cnt == 0) return;
            }

            //开始读取数据
            for (i = 0; i < 4; i++){
                for (j = 0; j < 8; j++){

                    //先拉低0.56ms 低电平
                    time_cnt =60;
                    while((!IRED) && time_cnt){

                        //减一次耗时10 us
                        delay_us(1);
                        time_cnt--;
                        if (time_cnt == 0) return;
                    }

                    time_cnt = 20;
                    while(IRED){
                        //一次延迟100 us
                        delay_us(10);
                        ired_high_time++;
                        if (ired_high_time >= 20) return;
                    }
                    gired[i] >>= 1;
                    if (ired_high_time >= 8)
                    gired[i] |= 0x80;
                }
            }
        }
        if (gired[2] != ~gired[3]){
            for (i = 0; i < 4; i++)
            gired[i] = 0;
            return;
        }
    }
}