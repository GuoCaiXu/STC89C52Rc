# ifndef _xpt2046_H
# define _xpt2046_H

# include "public.h"

//xpt2046引脚定义
sbit DIN = P3^4;  //串行数据输入管脚
sbit CS = P3^5;  //片选引脚
sbit DCLK = P3^6;  //外部时钟信号
sbit DOUT = P3^7;  //串行数据输出管脚

//写数据函数
void xpt2046_write_data(u8 dat);

//读函数
u16 xpt2046_read_data();

//读adc数据
u16 xpt2046_read_adc_value(u8 cmd);

# endif