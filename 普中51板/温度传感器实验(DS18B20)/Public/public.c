# include "public.h"

//中断初始化函数
void public_T0_init(){
    
    //总中断使能开启
    EA = 1;
    //定时器T0工作模式1
    TMOD = 0x01;
    //1 ms
    TH0 = 0xfc;
    TL0 = 0x66;
    //定时器T0 中断开启
    ET0 = 1;
    //定时器T0 开启
    TR0 = 1;
}

//延时函数 us
void public_us_delay(uchar z){
    while(z--);
}