# ifndef _public_H
# define _public_H

# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int
# define ulong unsigned long
# define ichar signed char

# include "key.h"
# include "smg.h"
# include "at24c02.h"

//返回秒数
ulong ReturnNum();

//初始化num1
void Num_init();

//按键2 数字清0
void Num_0();

//按键1
void Key1();

//按键3
void Key3();

//延时函数
void delay(uchar us);

//中断函数初始化
void T0_init();

//读数据函数
ulong read();

//读数据函数2
uchar read2();

# endif