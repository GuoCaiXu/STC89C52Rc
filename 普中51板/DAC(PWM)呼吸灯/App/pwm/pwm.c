# include "pwm.h"

//中断时间
u8 gtim_h = 0;
u8 gtim_l = 0;

//周期
u8 gtim_scale = 0;

//占空比
u8 gduty = 0;

//pwm 初始化
void pwm_init(u8 tim_h, u8 tim_l, u8 tim_scale, u8 duty){

    //初始化中断时间和周期占空比
    gtim_h = tim_h;
    gtim_l = tim_l;
    gtim_scale = tim_scale;
    gduty = duty;

    //定时器0 工作模式M1
    TMOD |= 0x01;

    //中断时间
    TH0 = gtim_h;
    TL0 = gtim_l;

    //定时器T0 开启
    ET0 = 1;

    //总中断开启
    EA = 1;

    //定时器T0 开启
    TR0  = 1;
}

//传入占空比
void pwm_set_duty_cycle(u8 duty){
    gduty = duty;
}

//中断函数
void pwm() interrupt 1{

    //记录时间
    static u8 time = 0;

    TH0 = gtim_h;
    TL0 = gtim_l; 

    time ++;  

    if (time >= gtim_scale) time = 0;

    if (time <= gduty) PWM = 1;
    else PWM = 0;
}