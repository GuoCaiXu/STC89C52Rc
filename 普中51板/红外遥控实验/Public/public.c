# include "public.h"

//T0中断初始化
void T0_init(){
    //总中断使能开启
    EA = 1;

    //定时器T0 工作模式1
    TMOD = 0x01;

    //1 ms
    TH0 = 0xfc;
    TL0 = 0x66;

    //定时器T0 中断开启
    ET0 = 1;
    
    //定时器T0 开启
    TR0 = 1;
}

//延迟函数 us
void delay_us(u8 z){
    while(z --);
}

//中断函数
void InterruptTime0() interrupt 1{

    TH0 = 0xfc;
    TL0 = 0x66;

    smg_ShowLed();
}