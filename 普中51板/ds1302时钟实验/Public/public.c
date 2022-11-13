# include "public.h"

//延时函数
void delay_us(u8 z){
    while(z--);
}

//延时函数 ms
void delay_ms(u8 z){
    u8 i;
    while(z--){
    for (i = 0; i < 120; i++);
    }
}

//中断函数初始化
void T0_init(){
    //总中断使能开关
    EA = 1;
    //T0工作模式1
    TMOD = 0x01;
    //1 ms 溢出
    TH0 = 0xfc;
    TL0 = 0x66;

    //定时器T0 中断使能开启
    ET0 = 1;
    //定时器T0 开启
    TR0 = 1;
}

void InterruptTime0() interrupt 1{

    static u8 i = 0;
    i++;

    TH0 = 0xfc;
    TL0 = 0x66;


    if (i >= 10){
        i = 0;
        smg_ShowLed();
    }

}