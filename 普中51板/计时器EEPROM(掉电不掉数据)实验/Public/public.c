# include "public.h"

ulong num1 = 0;
uchar flag = 0;
uchar jia = 0;

//返回秒数
ulong ReturnNum(){

    return num1;
}

//初始化num1
void Num_init(){
    num1 = read();
    jia = read2();
    flag = 0;
}

//按键2 数字清0
void Num_0(){
    num1 = 0;
}

//按键1
void Key1(){
    flag = !flag;
}

//按键3
void Key3(){
    jia = !jia;
    at24c02_write_byte(1,jia);
}

//延时函数
void delay(uchar us){
    while(us--);
}

//中断函数初始化
void T0_init(){
    EA = 1; //中断使能开关
    TMOD = 0x01; //定时器T0 工作模式1

    //1 ms
    TH0 = 0xfc;
    TL0 = 0x66;
    ET0 = 1;  //定时器T0 中断开启
    TR0 = 1;  //定时器T0 开启

}

//读数据函数1
ulong read(){
    ulong temp = 0;
    temp = at24c02_read_byte(0);

    return temp;
}

//读数据函数2
uchar read2(){
    uchar temp = 0;
    temp = at24c02_read_byte(1);

    return temp;
}

//中断函数T0
void InterruptTime0() interrupt 1{

    static uint cnt = 0;

    TH0 = 0xfc;
    TL0 = 0x66;

    //数码管显示
    smg_ShowLed();

    if (flag == 0){
    cnt++;
    if (cnt >= 1000){
        cnt = 0;
        if (jia == 0){
        num1++;
        }
        else {
            num1--;
            if (num1 == 0){
                jia = !jia;
                at24c02_write_byte(1,jia);
            }
        }
        at24c02_write_byte(0,num1);
    }
    }

    //按键消抖
    key_Vanish();
}