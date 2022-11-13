# include "public.h"

//定时器T0 中断初始化
void T0_init(){
    //总中断开启
    EA = 1;

    //定时器T0 工作模式M1
    TMOD = 0x01;

    //1ms 溢出
    TH0 = 0xfc;
    TL0 = 0x66;

    //定时器T0 中断开启
    ET0 = 1;

    //定时器T0 开启
    TR0 = 1;
}

//中断函数
void InterruptTime0() interrupt 1{

    TH0 = 0xfc;
    TL0 = 0x66;

    smg_ShowLed();
}