# include "public.h"

//延时函数
void delay(uchar us){
    while(us--);
}

//定时器0 初始化
void T0_init(){

    EA = 1; //总中断使能开启
    TMOD = 0x01; //定时器T0， 工作模式1

    //1 ms
    TH0 = 0xfc;
    TL0 = 0x66;

    ET0 = 1;  //定时器T0 中断开启
    TR0 = 1;  //定时器T0 开启
}

void InterruptTime0() interrupt 1{

    TH0 = 0xfc;
    TL0 = 0x66;

    //消抖按键函数
    ShakeKey();

    //显示数码管函数
    ShowLed();

}