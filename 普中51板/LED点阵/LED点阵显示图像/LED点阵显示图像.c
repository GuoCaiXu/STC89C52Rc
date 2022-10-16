# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int

sbit SER = P3^4;    //串行数据输入
sbit _RCLK = P3^5;  //存储寄存器时钟输入
sbit SRCLK = P3^6;  //移位寄存器时钟输入

uchar arrange[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};  //列数据
uchar line[] = {0x38,0x7C,0x7E,0x3F,0x3F,0x7E,0x7C,0x38}; //显示图像行数据 爱心
uchar flag = 0;

void ShowLine(uchar dte){
    uchar i;

    for (i = 0; i < 8; i++){
    SER = dte >> 7;
    dte <<= 1;
    SRCLK = 0;
    SRCLK = 1;
    }
    _RCLK = 1;
    _RCLK = 0;
}

void main(){
    uchar i;

    EA = 1;  //使能总中断开关
    TMOD = 0x01;  //工作模式1
    TH0 = 0xfc;
    TL0 = 0x66;  //时间1毫秒 0.001秒
    ET0  =1; //定时器T0中断开启
    TR0 = 1;  //定时器T0开启

    while(1){
        for (i = 0; i < 8; i++){
            P0 = arrange[i];
            ShowLine(line[i]);
            if (flag = 1){
                flag = 0;
                ShowLine(0x00);
            }
        }
    }
}

void InterruotTime0() interrupt 1{

    static uint cnt = 0;

    TH0 = 0xfc;
    TL0 = 0x66;
    cnt++;
    if (cnt >= 50){
        cnt = 0;
        flag = 1;
    }
}