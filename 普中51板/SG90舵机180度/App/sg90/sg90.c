# include "sg90.h"
# include "key.h"

//初始化中断时间，周期，占空比
u8 gtim_h = 0;
u8 gtim_l = 0;
u8 gtim_scale = 0;
signed char gduty = 0;

//PWM 初始化
void pwm_init(u8 tim_h, u8 tim_l, u8 tim_scale, signed char duty){

    //初始化中断时间，周期，占空比
    gtim_h = tim_h;
    gtim_l = tim_l;
    gtim_scale = tim_scale;
    gduty = duty;

    //定时器T0 工作模式M1
    TMOD = 0x01;

    //设置中断时间
    TH0 = gtim_h;
    TL0 = gtim_l;

    //中断定时器T0 开启
    ET0 = 1;

    //总中断开启
    EA = 1;

    //定时器T0 开启
    TR0 = 1;
}

//更新占空比
void pwm_set_duty(u8 duty){
    gduty = duty;
}

//中断函数
void pwm() interrupt 1{

    static u8 time = 0;

    TH0 = gtim_h;
    TL0 = gtim_l;

    time++;

    if (time >= gtim_scale) time = 0;

    if (time <= gduty) PWM = 1;
    else PWM = 0;
}