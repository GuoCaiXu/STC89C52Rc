# include "public.h"

//初始化定时器T0 
void T0_init(){
    //总中断使能开启
    EA = 1;

    //T0 工作模式1
    TMOD = 0x01;
    
    //0.5ms
    TH0 = 0xfe;
    TL0 = 0x33;

    //中断定时器T0 开启
    ET0 = 1;

    //定时器T0 开启
    TR0 = 1;
}

//T0 中断函数
void InterruptTime0() interrupt 1{

    TH0 = 0xf3;
    TL0 = 0x33;
    
    time_cnt ++;
    if (time_cnt >= 40) time_cnt = 0;

    if (time_cnt <= time) PWM = 1;
    else PWM = 0;
}
